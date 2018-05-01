// Author: Evgenii Kazakov. Github: @evgenstf
#include "logger.h"
#include <iostream>

using namespace latte;

int main(int arguments_count, char* arguments[]) {
  SET_LOG_LEVEL(Info);
  TRACE("trace log message");
  DEBUG("debug log message");
  INFO("info log message");
  WARNING("warning log message");
  ERROR("error log message");
  FATAL("fatal log message");
  return 0;
}
