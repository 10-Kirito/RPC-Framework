#pragma once
#include <google/protobuf/service.h>
#include <string>
class MprpcController : public google::protobuf::RpcController {
public:
  MprpcController();
  ~MprpcController();

  // ==> client side functions
  void Reset() override;
  bool Failed() const override;
  std::string ErrorText() const override;
  void StartCancel() override;

  // ==> server side functions
  void SetFailed(const std::string &reason) override;
  bool IsCanceled() const override;
  void NotifyOnCancel(google::protobuf::Closure *callback) override;

private:
  bool _failed;
  std::string _errorText;
};