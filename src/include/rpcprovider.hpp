#pragma once
#include <google/protobuf/service.h>
#include <muduo/net/Callbacks.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/InetAddress.h>
#include <muduo/net/TcpServer.h>

class RpcProvider {
public:
  // register the rpc service
  void NotifyService(google::protobuf::Service *service);

  // run the rpc server
  void Start();

private:
  muduo::net::EventLoop event;
  void onConnection(const muduo::net::TcpConnectionPtr &);
  void onMessage(const muduo::net::TcpConnectionPtr &, muduo::net::Buffer *,
                 muduo::Timestamp);
};