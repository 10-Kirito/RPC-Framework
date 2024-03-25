#include "mprpccontroller.hpp"
MprpcController::MprpcController() {
  _failed = false;
  _errorText = "";
}
MprpcController::~MprpcController() {}

void MprpcController::Reset() {
  _failed = false;
  _errorText = "";
}

bool MprpcController::Failed() const { return _failed; }

std::string MprpcController::ErrorText() const { return _errorText; }

void MprpcController::SetFailed(const std::string &reason) {
  _failed = true;
  _errorText = reason;
}

void MprpcController::StartCancel() {}
bool MprpcController::IsCanceled() const { return false; }
void MprpcController::NotifyOnCancel(google::protobuf::Closure *callback) {}