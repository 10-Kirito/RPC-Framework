#pragma once
#include <cstdint>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/service.h>
#include <google/protobuf/stubs/callback.h>
#include <memory>
#include <spdlog/logger.h>


using google::protobuf::Closure;
using google::protobuf::Message;
using google::protobuf::MethodDescriptor;
using google::protobuf::RpcChannel;
using google::protobuf::RpcController;

class MprpcChannel : public google::protobuf::RpcChannel{
public:
  std::shared_ptr<int> Connect(RpcController *, std::string, uint16_t);
  int SendBuffer(std::shared_ptr<int>, const std::string &);
  std::string ReceiveBuffer(RpcController *, std::shared_ptr<int>);
  // override the CallMethod, and all the rpc call in the client end will go
  // through this function
  // ==> important!!! <==
  void CallMethod(const MethodDescriptor *method, RpcController *controller,
                  const Message *request, Message *response,
                  Closure *done) override;

private:
};