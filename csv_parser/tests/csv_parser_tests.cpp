// Author: Evgenii Kazakov. Github: @evgenstf
#include "../csv_parser.h"
#include <gtest/gtest.h>
#include <unordered_set>

using namespace latte::csv_parser;

TEST(CsvParser, EmptyFile) {
  
}

int main(int argc, char** argv) {
   ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

