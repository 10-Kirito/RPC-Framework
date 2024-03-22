#include "mprpcconfig.hpp"

namespace pt = boost::property_tree;
// parse and load the configuration file
// load the configuration file
void configFile::load(const std::string &filename) {
  pt::ptree tree;
  pt::read_json(filename, tree);
  serverIP = tree.get<std::string>("server.ip");
  serverPort = tree.get<int>("server.port");
  zookeeperIP = tree.get<std::string>("zookeeper.ip");
  zookeeperPort = tree.get<int>("zookeeper.port");
}

void configFile::save(const std::string &filename) {
  pt::ptree tree;
  tree.put("server.ip", serverIP);
  tree.put("server.port", serverPort);
  tree.put("zookeeper.ip", zookeeperIP);
  tree.put("zookeeper.port", zookeeperPort);
  pt::write_json(filename, tree);
}
// overwrite the << function
std::ostream &operator<<(std::ostream &os, const configFile &cf) {
  os << "serverIP: " << cf.serverIP << std::endl;
  os << "serverPort: " << cf.serverPort << std::endl;
  os << "zookeeperIP: " << cf.zookeeperIP << std::endl;
  os << "zookeeperPort: " << cf.zookeeperPort << std::endl;
  return os;
}

