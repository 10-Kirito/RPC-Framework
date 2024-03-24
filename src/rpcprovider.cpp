#include "rpcprovider.hpp"
#include "mprpcapplication.hpp"
#include <cstdint>
#include <functional>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/stubs/callback.h>
#include <iomanip>
#include <iostream>
#include <muduo/net/InetAddress.h>
#include <muduo/net/TcpServer.h>

#include "rpcheader.pb.h"

// register the rpc service
void RpcProvider::NotifyService(google::protobuf::Service *service) {
  ServiceInfo serviceInfo;
  // get the service descriptor, and then we can get the service name and all
  // functions in it
  const google::protobuf::ServiceDescriptor *serviceDes =
      service->GetDescriptor();
  // get the name of the service
  std::string serviceName = serviceDes->name();

  std::cout << std::setw(30)
            << "------begin to register service and functions int it------"
            << std::endl;
  std::cout << "service name:" << serviceName << std::endl;
  // get the number of methods in the service
  int methodCount = serviceDes->method_count();

  for (int i = 0; i < methodCount; ++i) {
    // get the method des of the service
    const google::protobuf::MethodDescriptor *methodDes = serviceDes->method(i);
    serviceInfo.methodMap.insert({methodDes->name(), methodDes});
    std::cout << "method name:" << methodDes->name() << std::endl;
  }

  // store all details of the service, including the service and all methods
  // So when the client call a RPC, we can find the specified service and method
  // and call it in the RpcProvider and finally return the response to the
  // caller
  serviceInfo.service = service;
  _serviceMap.insert({serviceName, serviceInfo});

  std::cout << std::setw(30)
            << "---------------------end register--------------------"
            << std::endl
            << std::endl;
}

// run the rpc server
void RpcProvider::Start() {
  std::string ip = MprpcApplication::getInstance().GetConfig().serverIP;
  uint16_t port = MprpcApplication::getInstance().GetConfig().serverPort;
  muduo::net::InetAddress address(ip, port);

  // create the tcp server
  muduo::net::TcpServer server(&_event, address, "RpcProvider");

  // bind the callback functions
  server.setConnectionCallback(
      std::bind(&RpcProvider::onConnection, this, std::placeholders::_1));
  server.setMessageCallback(
      std::bind(&RpcProvider::onMessage, this, std::placeholders::_1,
                std::placeholders::_2, std::placeholders::_3));

  // set the number of threads in muduo
  server.setThreadNum(8);

  // start the server
  server.start();
  _event.loop();
}

// handle the connection from clients
void RpcProvider::onConnection(const muduo::net::TcpConnectionPtr &connection) {
  if (!connection->connected()) {
    connection->shutdown();
  }
}

// handle the message from clients:
// 1. get the service name and method name from the message
// 2. find the service and method in the _serviceMap
// 3. call the method and get the response
// 4. send the response to the client
void RpcProvider::onMessage(const muduo::net::TcpConnectionPtr &connection,
                            muduo::net::Buffer *buffer, muduo::Timestamp time) {
  // 1. get the message from the client
  // Attention what we want from the client, we just are the rpc framework
  std::string recvBuf = buffer->retrieveAllAsString();

  // header_size + service_name method_name args_size + args
  // ----size-----|------------RpcHeader--------------|--arguments-
  // RpcHeader:                    |
  //      bytes service_name=1;  <-|
  //      bytes method_name=2;
  //      uint32 args_size=3;

  uint32_t header_size = 0;
  recvBuf.copy((char *)&header_size, 4, 0);

  // get the RpcHeader and parse it
  std::string rpc_header_str = recvBuf.substr(4, header_size);
  mprpc::RpcHeader rpcHeader;

  std::string service_name;
  std::string method_name;
  uint32_t args_size;

  if (rpcHeader.ParseFromString(rpc_header_str)) {
    // get the service name and method name
    service_name = rpcHeader.service_name();
    method_name = rpcHeader.method_name();
    args_size = rpcHeader.args_size();
  } else {
    // parse the RpcHeader failed
    std::cout << "rpcHeader.ParseFromString failed" << std::endl;
    return;
  }

  // get the arguments of the RPC functions:
  std::string arguments = recvBuf.substr(4 + header_size, args_size);

  // log the info
  std::cout << "header size:" << header_size << std::endl;
  std::cout << "service_name:" << service_name << std::endl
            << "method_name:" << method_name << std::endl
            << "args_size:" << args_size << std::endl
            << "arguments:" << arguments << std::endl;

  // check if the service and method exists
  auto it = _serviceMap.find(service_name);
  if (it == _serviceMap.end()) {
    std::cerr << "Can't find the service:" << service_name << std::endl;
    return;
  }
  auto methodit = it->second.methodMap.find(method_name);
  if (methodit == it->second.methodMap.end()) {
    std::cerr << "Can't find the method:" << method_name << std::endl;
    return;
  }

  // get the registered service
  google::protobuf::Service *service = it->second.service;
  // get the target method
  const google::protobuf::MethodDescriptor *method = methodit->second;

  // generate the request and response(the request and the response is created by us in the RPC server and client)
  google::protobuf::Message *request =
      service->GetRequestPrototype(method).New();
  // the arguments send from the client
  if (!request->ParseFromString(arguments)) {
    std::cout << "request parse failed" << std::endl;
    return;
  }
  google::protobuf::Message *response =
      service->GetResponsePrototype(method).New();

  // this will create a Closure object and bind the callback function
  google::protobuf::Closure *callback = google::protobuf::NewCallback(
      this, &RpcProvider::sendRpcResponse, connection, response);

  // call the method and set the callback function
  // when the method is finished, the callback function will be called and pass
  // the response to the method
  service->CallMethod(method, nullptr, request, response, callback);
}

void RpcProvider::sendRpcResponse(const muduo::net::TcpConnectionPtr conn,
                                  google::protobuf::Message *response) {
  std::string response_str;
  if (response->SerializeToString(&response_str)) {
    conn->send(response_str);
  } else {
    std::cout << "serialize response failed" << std::endl;
  }
}