#include "random_access_file.h"

#include <cstdlib>

RandomAccessFile::RandomAccessFile():
    file_(std::tmpfile()) {}

RandomAccessFile::RandomAccessFile(const std::string& filename) {
  file_ = std::fopen(filename.c_str(), "r+");
  if (!file_) {
    file_ = std::fopen(filename.c_str(), "w+");
  }
}

RandomAccessFile::~RandomAccessFile() {
  std::fclose(file_);
}

void RandomAccessFile::write(size_t position, const std::vector<uint8_t>& data) {
  std::fseek(file_, position, SEEK_SET);
  std::fwrite(data.data(), sizeof(uint8_t), data.size(), file_);
}

std::vector<uint8_t> RandomAccessFile::read(size_t position, size_t length) const {
  std::vector<uint8_t> data(length);
  std::fseek(file_, position, SEEK_SET);
  size_t result_size = std::fread(data.data(), sizeof(uint8_t), length, file_);
  data.resize(result_size);
  return data;
}

std::optional<uint8_t> RandomAccessFile::read(size_t position) const {
  std::fseek(file_, position, SEEK_SET);
  uint8_t byte;
  if (std::fread(&byte, sizeof(uint8_t), 1, file_) == 1) {
    return byte;
  } else {
    return std::nullopt;
  }
}

size_t RandomAccessFile::size() const {
  size_t size = 0;
  while (read(size).has_value()) {
    ++size;
  }
  return size;
}
