#include "mprpcapplication.hpp"
#include "rpcprovider.hpp"
#include "user.pb.h"
#include <google/protobuf/port_def.inc>
#include <iostream>
#include <string>

// the service implement, callee
class UserService : public kirito::LoginServiceRPC {
public:
  bool Login(std::string name, std::string pwd) {
    std::cout << "Login" << std::endl;
    std::cout << "name" << name << "pwd:" << pwd << std::endl;
    return true;
  }
  /*
    These function all is called by the rpc framework, so we need to implement
    them. When we finish the implement, we can call the done->Run() to notify
    the rpc framework. Finally, the rpc framework will send the response to the
    caller.
  */
  // override from LoginServiceRPC
  void Login(::PROTOBUF_NAMESPACE_ID::RpcController *controller,
             const ::kirito::LoginRequest *request,
             ::kirito::LoginResponse *response,
             ::google::protobuf::Closure *done) {
    /*
      The rpc framework already process the data from caller and put them into
      the request. So we can get the data from the request directly.
    */
    std::string name = request->name();
    std::string pwd = request->password();

    // call the real implement
    bool login_result = Login(name, pwd);

    // write the response to the response
    response->set_success(login_result);

    kirito::Result *result = response->mutable_result();
    result->set_errorcode(200);
    result->set_errormessage("Login successfully");

    // notify the rpc framework, execute the serilization and send the response
    // to the caller
    done->Run();
  }
};

int main(int argc, char **argv) {
  // the rpc framework initialize
  MprpcApplication::Initialize(argc, argv);

  // register the service
  RpcProvider provider;
  provider.NotifyService(new UserService());

  // run the rpc server and block the server 
  provider.Start();

  return 0;
}