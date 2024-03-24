#pragma once
#include <google/protobuf/descriptor.h>
#include <google/protobuf/service.h>
#include <muduo/net/Callbacks.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/InetAddress.h>
#include <muduo/net/TcpConnection.h>
#include <muduo/net/TcpServer.h>
#include <string>
#include <unordered_map>

class RpcProvider {
public:
  // register the rpc service
  void NotifyService(google::protobuf::Service *service);

  // run the rpc server
  void Start();

private:
  // define the serviceinfo, so we can get the service and method
  struct ServiceInfo {
    google::protobuf::Service *service;
    std::unordered_map<std::string, const google::protobuf::MethodDescriptor *>
        methodMap;
  };
  // the map to store the service
  std::unordered_map<std::string, ServiceInfo> _serviceMap;

  muduo::net::EventLoop _event;
  void onConnection(const muduo::net::TcpConnectionPtr &);
  void onMessage(const muduo::net::TcpConnectionPtr &, muduo::net::Buffer *,
                 muduo::Timestamp);

  void sendRpcResponse(const muduo::net::TcpConnectionPtr conn,
                       google::protobuf::Message *response);
};