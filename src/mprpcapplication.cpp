#include "mprpcapplication.hpp"
#include <cstdlib>
#include <iostream>
#include <string>
#include <unistd.h>
#include "mprpcconfig.hpp"



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
  std::cout << "loading config file <" << configfile << "> ..." << std::endl;
  // loading the config file using boost.property_tree
  _config.load(configfile);


  // print the configuration
  std::cout << _config << std::endl;

}

configFile& MprpcApplication::GetConfig(){
  return _config;
}