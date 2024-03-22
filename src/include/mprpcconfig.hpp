#pragma once
#include <boost/foreach.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <string>

// store the configuration of mprpc:
// 1. rpcserver ip;
// 2. rpcserver port;
// 3. zookeeper ip;
// 4. zookeeper port;
struct configFile {
  std::string serverIP;
  int serverPort;
  std::string zookeeperIP;
  int zookeeperPort;

  void load(const std::string &filename);
  void save(const std::string &filename);
};

// overwrite the << function
std::ostream &operator<<(std::ostream &os, const configFile &cf);