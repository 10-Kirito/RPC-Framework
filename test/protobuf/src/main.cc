#include "test.pb.h"
#include <iostream>
#include <string>

int main(int argc, char **argv) {
  kirito::LoginRequest request;

  request.set_name("kirito");
  request.set_pwd("123456");

  std::string send_str;

  kirito::LoginResponse response;
  kirito::Result *result = response.mutable_result();
  result->set_errcode(1);
  result->set_errmsg("login failed");

  kirito::GetFriendListsResponse response2;
  kirito::Result *result1 = response2.mutable_result();
  result1->set_errcode(0);

  kirito::User *user = response2.add_friends();

  user->set_name("kirito");
  user->set_age(12);
  user->set_sex(kirito::User::MAN);
  kirito::User *user1 = response2.add_friends();

  user1->set_name("kirito");
  user1->set_age(12);
  user1->set_sex(kirito::User::MAN);

  std::cout << response2.friends_size() << std::endl;

  if (request.SerializeToString(&send_str)) {
    std::cout << "send_str: " << send_str << std::endl;
  } else {
    std::cout << "SerializeToString failed" << std::endl;
  }

  kirito::LoginRequest request2;
  if (request2.ParseFromString(send_str)) {
    std::cout << request2.name() << std::endl;
    std::cout << request2.pwd() << std::endl;
  }

  return 0;
};