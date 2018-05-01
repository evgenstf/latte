// Author: Evgenii Kazakov. Github: @evgenstf
#include "logger.h"
#include <iostream>

using namespace latte;

int main(int arguments_count, char* arguments[]) {
  SET_LOG_LEVEL(Info);
  TRACE("count of rabbits " << 5);
  DEBUG("the ship successfully docked");
  INFO("a paper airplane flew out the window");
  WARNING("bitcoin fell");
  ERROR("wrong pyramid volume: " << -25);
  FATAL("the meteorite is approaching");
  return 0;
}
