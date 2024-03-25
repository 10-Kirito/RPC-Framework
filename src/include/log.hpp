#pragma once
#include "help.hpp"
#include "singletontemplate.hpp"
#include "spdlog/async.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/spdlog.h"
#include <iostream>
#include <memory>
#include <spdlog/common.h>
#include <spdlog/logger.h>
class Logger : public SingletonTemplate<Logger> {
  friend class SingletonTemplate<Logger>;
public:
  Logger() {
    try {
      std::string logfilename = "logs/" + Time();
      spdlog::init_thread_pool(8192,10);
      _logger = spdlog::rotating_logger_mt<spdlog::async_factory>(
          "MPRPC", logfilename, 1024 * 1024 * 20, 10);
      spdlog::flush_every(std::chrono::seconds(3));
    } catch (const spdlog::spdlog_ex &ex) {
      std::cout << "Log init failed: " << ex.what() << std::endl;
    }
  }

  ~Logger() {}

  inline std::shared_ptr<spdlog::logger> getLogger() { return _logger; }

private:
  std::shared_ptr<spdlog::logger> _logger;
};

#define LOG_INFO(...) Logger::getInstance().getLogger()->info(__VA_ARGS__)
#define LOG_WARN(...) Logger::getInstance().getLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...) Logger::getInstance().getLogger()->error(__VA_ARGS__)