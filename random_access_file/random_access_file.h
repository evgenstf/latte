#pragma once

#include <cstdio>
#include <string>
#include <vector>
#include <optional>

class RandomAccessFile {
public:
  RandomAccessFile();
  RandomAccessFile(const std::string& filename);
  ~RandomAccessFile();

  std::optional<uint8_t> read(size_t position) const;
  std::vector<uint8_t> read(size_t position, size_t length) const;
  void write(size_t position, const std::vector<uint8_t>& data);

  size_t size() const;

private:
  FILE* file_;
};
