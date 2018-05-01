// Author: Evgenii Kazakov. Github: @evgenstf
#include "logger.h"

namespace latte {

Logger::Logger():
    min_print_level_(LogLevel::Trace) {
  start_logging();
}

Logger::~Logger() {
  finish_logging();
  logging_thread_.join();
}

void Logger::set_min_print_level(LogLevel level) {
  std::lock_guard<std::mutex> lock(mutex_);
  min_print_level_ = level;
}

void Logger::finish_logging() {
  is_logging_ = false;
  logging_thread_wake_up_.notify_one();
}

void Logger::print_log(Log log) {
  std::lock_guard<std::mutex> lock(mutex_);
  logs_to_print_.push(log);
  logging_thread_wake_up_.notify_one();
}

void Logger::print_log_internal(const Log& log) const {
  if (log.level < min_print_level_) {
    return;
  }
  switch (log.level) {
    case LogLevel::Trace:
      std::clog << "TRACE :: ";
      break;
    case LogLevel::Debug:
      std::clog << "DEBUG :: ";
      break;
    case LogLevel::Info:
      std::clog << "INFO :: ";
      break;
    case LogLevel::Warning:
      std::clog << "WARNING :: ";
      break;
    case LogLevel::Error:
      std::clog << "ERROR :: ";
      break;
    case LogLevel::Fatal:
      std::clog << "FATAL :: ";
      break;
  }
  std::clog << log.message << std::endl;
}

void Logger::start_logging() {
  is_logging_ = true;
  logging_thread_ = std::thread([this]() {
    while (is_logging_ || !logs_to_print_.empty()) {
      std::unique_lock<std::mutex> lock(mutex_);
      logging_thread_wake_up_.wait(lock, [this]() {
          return !logs_to_print_.empty() || !is_logging_;
      });
      if (!logs_to_print_.empty()) {
        print_log_internal(logs_to_print_.front());
        logs_to_print_.pop();
      }
    }
  });
}

}  // namespace latte
