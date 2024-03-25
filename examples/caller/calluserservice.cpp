#include "log.hpp"
#include "mprpcapplication.hpp"
#include "mprpcchannel.hpp"
#include "user.pb.h"
#include "mprpccontroller.hpp"

int main(int argc, char **argv) {
  // Initialize the config
  MprpcApplication::getInstance().Initialize(argc, argv);

  kirito::UserServiceRPC_Stub stub(new MprpcChannel());

  kirito::LoginRequest request;
  request.set_name("kirito");
  request.set_password("123456");

  kirito::LoginResponse response;

  LOG_INFO("==>begin test the RPC login()");

  MprpcController controller;
  // call the RPC function
  stub.Login(&controller, &request, &response, nullptr);

  // check the RPC status
  if (controller.Failed()) {
    std::cout << controller.ErrorText() << std::endl;
    return 0;
  }

  if (0 == response.result().errorcode()) {
    std::cout << "rpc login response error: "
              << response.result().errormessage() << std::endl;
  } else {
    std::cout << "rpc login response successfully: "
              << response.result().errormessage() << std::endl;
  }

  std::cout << "==>begin test the RPC getUserInfo()" << std::endl;
  kirito::UserInforRequest request2;
  kirito::UserInfoResponse response2;
  request2.set_userid(2002);

  stub.GetUserInfo(nullptr, &request2, &response2, nullptr);

  if (200 == response2.result().errorcode()) {
    kirito::UserInfo userinfo = response2.userinfo();
    std::cout << userinfo.name() << std::endl;
    std::cout << userinfo.password() << std::endl;
    std::cout << userinfo.email() << std::endl;
    std::cout << userinfo.phone() << std::endl;
  }else {
    std::cout << "rpc getuserinfo response error: "
              << response2.result().errormessage() << std::endl;
  }
}