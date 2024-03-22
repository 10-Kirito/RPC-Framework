#include "rpcprovider.hpp"
#include "mprpcapplication.hpp"
#include <functional>
#include <muduo/net/InetAddress.h>
#include <muduo/net/TcpServer.h>

void RpcProvider::NotifyService(google::protobuf::Service *service) {}

void RpcProvider::Start() {
  std::string ip = MprpcApplication::getInstance().GetConfig().serverIP;
  uint16_t port = MprpcApplication::getInstance().GetConfig().serverPort;
  muduo::net::InetAddress address(ip, port);

  // create the tcp server
  muduo::net::TcpServer server(&event, address, "RpcProvider");

  // bind the callback functions
  server.setConnectionCallback(
      std::bind(&RpcProvider::onConnection, this, std::placeholders::_1));
  server.setMessageCallback(
      std::bind(&RpcProvider::onMessage, this, std::placeholders::_1,
                std::placeholders::_2, std::placeholders::_3));

  // set the number of threads in muduo
  server.setThreadNum(8);

  std::cout << "RpcProvider::Start() server.start()" << std::endl;

  // start the server
  server.start();
  event.loop();
}

void RpcProvider::onConnection(const muduo::net::TcpConnectionPtr &connection) {

}

void RpcProvider::onMessage(const muduo::net::TcpConnectionPtr &connection,
                            muduo::net::Buffer *buffer, muduo::Timestamp time) {
}