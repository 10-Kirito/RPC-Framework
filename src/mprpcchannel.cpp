#include "mprpcchannel.hpp"
#include "mprpcapplication.hpp"
#include "mprpcconfig.hpp"
#include "rpcheader.pb.h"
#include <arpa/inet.h>
#include <cerrno>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <google/protobuf/message.h>
#include <google/protobuf/stubs/callback.h>
#include <iostream>
#include <memory>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

// override the CallMethod, and all the rpc call in the client end will go
// through this function
void MprpcChannel::CallMethod(const MethodDescriptor *method,
                              RpcController *controller, const Message *request,
                              Message *response, Closure *done) {
  // 1. header_size + service_name method_name args_size + args
  // ----size-----|------------RpcHeader--------------|--arguments-
  // RpcHeader:                    |
  //      bytes service_name=1;  <-|
  //      bytes method_name=2;
  //      uint32 args_size=3;
  // set header_size and the RpcHeader and arguments

  const google::protobuf::ServiceDescriptor *sd = method->service();
  std::string service_name = sd->name();
  std::string method_name = method->name();

  int arguments_size = 0;
  std::string arguments_str;
  // 2. serialize the request using protobuf and send it to the server
  if (request->SerializeToString(&arguments_str)) {
    arguments_size = arguments_str.size();
  } else {
    std::cout << "SerializeToString failed" << std::endl;
    return;
  }

  // 2.1 add the rpcheader
  mprpc::RpcHeader rpcheader;
  rpcheader.set_service_name(service_name);
  rpcheader.set_method_name(method_name);
  rpcheader.set_args_size(arguments_size);

  uint32_t header_size = 0;
  std::string rpcheaderstr;
  if (rpcheader.SerializePartialToString(&rpcheaderstr)) {
    header_size = rpcheaderstr.size();
  } else {
    std::cout << "SerializePartialToString failed" << std::endl;
    return;
  }

  // 2.2 assemble the send buffer
  std::string sendbuffer;
  sendbuffer.insert(0, (char *)&header_size, 4);
  sendbuffer += rpcheaderstr;
  sendbuffer += arguments_str;

  std::cout << "header size:" << header_size << std::endl;
  std::cout << "service_name:" << service_name << std::endl
            << ": method_name:" << method_name << std::endl
            << " args_size:" << arguments_size << std::endl
            << "arguments:" << arguments_str << std::endl;

  // 3. create a clientfd and connnect the rpc server
  std::shared_ptr<int> clientfdPtr = Connect();
  std::cout << "connect server success" << std::endl;
  // 4. send the buffer to the RPC server
  if (-1 == SendBuffer(clientfdPtr, sendbuffer)) {
    std::cout << "send data to server failed" << std::endl;
    exit(EXIT_FAILURE);
  }

  // 5. receive the data from the RPC server
  std::string receivebuffer = ReceiveBuffer(clientfdPtr);

  if (!response->ParseFromString(receivebuffer)) {
    std::cout << "ParseFromString failed" << std::endl;
    return;
  }
}

// define the deleter to close the fd
void Closefd(int *fd) {
  if (-1 != *fd) {
    close(*fd);
  }
}

std::shared_ptr<int> MprpcChannel::Connect() {
  // create a clientfd
  std::shared_ptr<int> clientfdPtr(new int(socket(AF_INET, SOCK_STREAM, 0)),
                                   std::function<void(int *)>(&Closefd));
  // int client = socket(AF_INET, SOCK_STREAM, 0);
  if (-1 == *clientfdPtr) {
    std::cout << "create socket failed" << std::endl;
    exit(EXIT_FAILURE);
  }
  // create the addr
  std::string ip = MprpcApplication::getInstance().GetConfig().serverIP;
  uint16_t port = MprpcApplication::getInstance().GetConfig().serverPort;
  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(port);
  server_addr.sin_addr.s_addr = inet_addr(ip.c_str());

  // connect the RPC server
  if (-1 == connect(*clientfdPtr, (struct sockaddr *)&server_addr,
                    sizeof(server_addr))) {
    std::cout << "connect server failed" << std::endl;
    exit(EXIT_FAILURE);
  }

  return clientfdPtr;
}

int MprpcChannel::SendBuffer(std::shared_ptr<int> clientPtr,
                             const std::string &buffer) {
  // send the buffer to the RPC server
  if (-1 == send(*clientPtr, buffer.c_str(), buffer.size(), 0)) {
    std::cout << "send data to server failed" << std::endl;
    exit(EXIT_FAILURE);
  }
  return 1;
}

std::string MprpcChannel::ReceiveBuffer(std::shared_ptr<int> clientPtr) {
  // receive the data from the RPC server
  char buffer[1024] = {0};
  std::string receiveData;

  while (true) {
    int receiveLen = recv(*clientPtr, buffer, sizeof(buffer), 0);
    if (receiveLen < 0) {
      std::cerr << "recv() failed" << strerror(errno) << std::endl;
      break;
    } else if (receiveLen == 0) {
      std::cerr << "Connection closed by server" << std::endl;
      break;
    } else {
      // Data receive successfully
      receiveData.append(buffer, receiveLen);
      if (receiveLen < sizeof(buffer))
        // Received less than buffer size, so we received the last part of the
        // data
        break;
    }
  }

  return receiveData;
}