#include "mprpcapplication.hpp"
#include "log.hpp"
#include "mprpcconfig.hpp"
#include <cstdlib>
#include <iostream>
#include <spdlog/logger.h>
#include <string>
#include <unistd.h>

// the static member variable of MprpcConfig
configFile MprpcApplication::_config;

void showHelp() {
  std::cout << "format: command -i <configfile>" << std::endl;
  exit(EXIT_FAILURE);
}

void MprpcApplication::Initialize(int argc, char **argv) {
  if (argc < 2) {
    showHelp();
  }

  MprpcApplication &app = MprpcApplication::getInstance();

  // get the config file user input in the command line
  int c = 0;
  std::string configfile;
  if ((c = getopt(argc, argv, "i:")) != -1) {
    switch (c) {
    case 'i':
      configfile = optarg;
      break;
    case '?':
      showHelp();
    case ':':
      showHelp();
    default:
      break;
    }
  } else {
    showHelp();
  }
  LOG_INFO("loading config file <{}> ...", configfile);
  _config.load(configfile);
}

configFile &MprpcApplication::GetConfig() { return _config; }