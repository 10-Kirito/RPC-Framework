#pragma once
#include <cstdio>
#include <ctime>
#include <spdlog/common.h>
#include <spdlog/logger.h>
#include <string>

inline std::string Time() {
  std::time_t now = std::time(nullptr);
  std::tm *nowtm = std::localtime(&now);

  char file_name[1024];
  sprintf(file_name, "%d-%d-%d-log.txt", nowtm->tm_year + 1900,
          nowtm->tm_mon + 1, nowtm->tm_mday);
  return std::string(file_name);
}