// Author: Evgenii Kazakov. Github: @evgenstf
#pragma once
#include <string>

namespace latte {

class File {
public:
  File(std::string path): path_(std::move(path)) {}

  const std::string& name() const { return name_; }
  const std::string& name_without_extention const { return name_; }
  const std::string& extention() const { return extention_; }
  const std::string& path() const { return path_; }

  bool exists() const { return true; }

private:
  const std::string path_;
  const std::string name_;
};

}  // namespace latte
