// Author: Evgenii Kazakov. Github: @evgenstf
#include "command_parser.h"
#include <iostream>

using namespace latte;

const std::unordered_set<std::string>
    commands{"new", "make", "test", "read", "write", "init", "help", "try", "clear", "destroy"};

int main(int arguments_count, char* arguments[]) {
  std::cout << "Avaliable commands:";
  for (const auto& command : commands) {
    std::cout << " \"" << command << "\"";
  }
  std::cout << std::endl << std::endl;

  CommandParser command_parser(commands);
  auto parsed_commands = command_parser.parse(arguments_count, arguments);

  std::cout << "Parsed commands:" << std::endl;
  for (auto command : parsed_commands) {
    std::cout << "  command: \"" << command.first << "\" arguments:";
    for (auto argument : command.second) {
      std::cout << " \"" << argument << "\"";
    }
    std::cout << std::endl;
  }
  return 0;
}
