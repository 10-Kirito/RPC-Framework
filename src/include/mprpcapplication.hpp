#pragma once
#include "mprpcconfig.hpp"
#include "singletontemplate.hpp"

class MprpcApplication : public SingletonTemplate<MprpcApplication> {
public:
  friend class SingletonTemplate<MprpcApplication>;
  static void Initialize(int argc, char **argv);
  static configFile &GetConfig();

private:
  static configFile _config;
};
