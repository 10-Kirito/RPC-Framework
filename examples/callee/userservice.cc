#include "mprpcapplication.hpp"
#include "rpcprovider.hpp"
#include "user.pb.h"
#include <google/protobuf/port_def.inc>
#include <iostream>
#include <string>

// the service implement, callee
class UserService : public kirito::UserServiceRPC {
public:
  bool Login(std::string name, std::string pwd) {
    std::cout << "You login successfully!" << std::endl;
    std::cout << "name: " << name << std::endl
              << "password:" << pwd << std::endl;
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
             ::google::protobuf::Closure *done) override {
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

  // test get the user info:
  // the local service:
  kirito::UserInfo getUserInfo(const int &userid) {
    kirito::UserInfo userinfo;

    userinfo.set_name("kirito");
    userinfo.set_password("123456");
    userinfo.set_email("2875786463@qq.com");
    userinfo.set_phone("17698266260");
    return userinfo;
  }

  // overide the GetUserInfo function from the UserServiceRPC
  void GetUserInfo(::PROTOBUF_NAMESPACE_ID::RpcController *controller,
                   const ::kirito::UserInforRequest *request,
                   ::kirito::UserInfoResponse *response,
                   ::google::protobuf::Closure *done) override {
    int userid = request->userid();
    kirito::UserInfo userinfo = getUserInfo(userid);
    std::cout << "the userid is " << userid << std::endl;

    response->mutable_userinfo()->CopyFrom(userinfo);
    response->mutable_result()->set_errorcode(200);
    response->mutable_result()->set_errormessage(
        "get the User message successfully");

    done->Run();
  }
};

int main(int argc, char **argv) {
  // 0. the rpc framework initialize(just simple load a config file)
  MprpcApplication::Initialize(argc, argv);

  // 1. register the service
  RpcProvider provider;
  provider.NotifyService(new UserService());
  // 2. run the rpc server and block the server
  provider.Start();
  return 0;
}