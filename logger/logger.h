// Author: Evgenii Kazakov. Github: @evgenstf
#pragma once
#include <atomic>
#include <iostream>
#include <string>
#include <queue>
#include <condition_variable>
#include <thread>
#include <sstream>

namespace latte {

enum class LogLevel {
  Trace = 0,
  Debug = 1,
  Info = 2,
  Warning = 3,
  Error = 4,
  Fatal = 5,
  Unknown
};

struct Log {
  LogLevel level;
  std::string message;
};

class Logger {
public:
  Logger();
  ~Logger();

  void set_min_print_level(LogLevel level);
  void start_logging();
  void finish_logging();
  void print_log(Log log);

private:
  void print_log_internal(const Log& log) const;

  LogLevel min_print_level_;
  std::mutex mutex_;
  std::thread logging_thread_;
  std::atomic<bool> is_logging_;
  std::queue<Log> logs_to_print_;
  std::condition_variable logging_thread_wake_up_;
};

static Logger ___logger___;

#define TRACE(message) {\
  std::stringstream log_stream;\
  log_stream << message;\
  ___logger___.print_log({LogLevel::Trace, log_stream.str()});\
}

#define DEBUG(message) {\
  std::stringstream log_stream;\
  log_stream << message;\
  ___logger___.print_log({LogLevel::Debug, log_stream.str()});\
}

#define INFO(message) {\
  std::stringstream log_stream;\
  log_stream << message;\
  ___logger___.print_log({LogLevel::Info, log_stream.str()});\
}

#define WARNING(message) {\
  std::stringstream log_stream;\
  log_stream << message;\
  ___logger___.print_log({LogLevel::Warning, log_stream.str()});\
}

#define ERROR(message) {\
  std::stringstream log_stream;\
  log_stream << message;\
  ___logger___.print_log({LogLevel::Error, log_stream.str()});\
}

#define FATAL(message) {\
  std::stringstream log_stream;\
  log_stream << message;\
  ___logger___.print_log({LogLevel::Fatal, log_stream.str()});\
}

#define SET_LOG_LEVEL(level) { ___logger___.set_min_print_level(LogLevel::level); }

}  // namespace latte
