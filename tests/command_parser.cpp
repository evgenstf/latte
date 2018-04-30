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
      strcpy(arguments[arguments_count++], argument.c_str());
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
  ASSERT_EQ(parsed_commands.front().first, "command1");
  auto expected_args = std::vector<std::string>({"argument1"});
  ASSERT_EQ(parsed_commands.front().second, expected_args);

  free_arguments_array(arguments, kMaxArgumentsCount, kMaxArgumentLength);
}

TEST(CommandParser, OneCommandThreeParameters) {
  CommandParser parser{"command1"};

  auto arguments = build_arguments_array(kMaxArgumentsCount, kMaxArgumentLength);
  auto arguments_count =
      build_main_input_arguments("program_name command1 argument1 argument2 argument3", arguments);
  auto parsed_commands = parser.parse(arguments_count, arguments);

  ASSERT_EQ(parsed_commands.size(), 1);
  ASSERT_EQ(parsed_commands.front().first, "command1");
  auto expected_args = std::vector<std::string>({"argument1", "argument2", "argument3"});
  ASSERT_EQ(parsed_commands.front().second, expected_args);

  free_arguments_array(arguments, kMaxArgumentsCount, kMaxArgumentLength);
}

TEST(CommandParser, ThreeCommandsOneParameter) {
  CommandParser parser{"command1", "command2", "command3"};

  auto arguments = build_arguments_array(kMaxArgumentsCount, kMaxArgumentLength);
  auto arguments_count = build_main_input_arguments("program_name command1 argument1 "
      "command2 argument1 command3 argument1", arguments);
  auto parsed_commands = parser.parse(arguments_count, arguments);
  auto expected_args = std::vector<std::string>({"argument1"});

  ASSERT_EQ(parsed_commands.size(), 3);
  ASSERT_EQ(parsed_commands[0].first, "command1");
  ASSERT_EQ(parsed_commands[0].second, expected_args);
  ASSERT_EQ(parsed_commands[1].first, "command2");
  ASSERT_EQ(parsed_commands[1].second, expected_args);
  ASSERT_EQ(parsed_commands[2].first, "command3");
  ASSERT_EQ(parsed_commands[2].second, expected_args);

  free_arguments_array(arguments, kMaxArgumentsCount, kMaxArgumentLength);
}


TEST(CommandParser, ThreeCommandsThreeParameters) {
  CommandParser parser{"command1", "command2", "command3"};

  auto arguments = build_arguments_array(kMaxArgumentsCount, kMaxArgumentLength);
  auto arguments_count = build_main_input_arguments("program_name command1 argument1 "
      "command2 argument2 command3 argument3", arguments);
  auto parsed_commands = parser.parse(arguments_count, arguments);

  ASSERT_EQ(parsed_commands.size(), 3);
  ASSERT_EQ(parsed_commands[0].first, "command1");
  ASSERT_EQ(parsed_commands[0].second, std::vector<std::string>({"argument1"}));
  ASSERT_EQ(parsed_commands[1].first, "command2");
  ASSERT_EQ(parsed_commands[1].second, std::vector<std::string>({"argument2"}));
  ASSERT_EQ(parsed_commands[2].first, "command3");
  ASSERT_EQ(parsed_commands[2].second, std::vector<std::string>({"argument3"}));

  free_arguments_array(arguments, kMaxArgumentsCount, kMaxArgumentLength);
}

