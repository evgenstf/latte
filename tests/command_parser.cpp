#include "../command_parser/command_parser.h"
#include <gtest/gtest.h>
#include <unordered_set>

using namespace latte;

namespace {

char** build_arguments_array(size_t max_arguments_count, size_t max_argument_length) {
  char** arguments = static_cast<char**>(malloc(max_arguments_count * sizeof(char*)));
  for (size_t i = 0; i < max_arguments_count; ++i) {
    arguments[i] = static_cast<char*>(malloc(max_argument_length * sizeof(char)));
  }
  return arguments;
}

void free_arguments_array(char** arguments,
    size_t max_arguments_count, size_t max_argument_length) {
  for (size_t i = 0; i < max_arguments_count; ++i) {
    free(arguments[i]);
  }
  free(arguments);
}

size_t build_main_input_arguments(const std::string& command_line, char* arguments[]) {
  size_t arguments_count = 0;
  size_t index = 0;
  while (index < command_line.size()) {
    while (index < command_line.size() && command_line[index] == ' ') {
      ++index;
    }
    std::string argument;
    while (index < command_line.size() && command_line[index] != ' ') {
      argument.push_back(command_line[index]);
      ++index;
    }
    if (!argument.empty()) {
      std::clog << "argument: " << argument << std::endl;
      std::clog << "first byte: " << arguments[arguments_count][0] << std::endl;
      strcpy(arguments[arguments_count++], argument.c_str());
      std::clog << "argument: " << argument << std::endl;
    }
  }
  return arguments_count;
}

}  // namespace

const size_t kMaxArgumentsCount = 100;
const size_t kMaxArgumentLength = 1000;

TEST(CommandParser, OneCommandOneParameter) {
  CommandParser parser{"command1"};

  auto arguments = build_arguments_array(kMaxArgumentsCount, kMaxArgumentLength);
  auto arguments_count = build_main_input_arguments("program_name command1 argument1", arguments);
  auto parsed_commands = parser.parse(arguments_count, arguments);

  ASSERT_EQ(parsed_commands.size(), 1);
  auto expected_args = std::vector<std::string>({"argument1"});
  ASSERT_EQ(parsed_commands.front().first, "command1");

  free_arguments_array(arguments, kMaxArgumentsCount, kMaxArgumentLength);
}

