#include "BufferedFile.h"

BufferedFile::BufferedFile(const std::string &file_path, size_t buffer_size, size_t block_size, std::ios::openmode mode)
    : block_size_(block_size), file_pos_(0), cache_(buffer_size / block_size, block_size) {
    file_.open(file_path, mode);
    if (!file_.is_open()) {
        throw std::ios_base::failure("Failed to open file: " + file_path);
    }
}

BufferedFile::~BufferedFile() {
    flush();
    if (file_.is_open()) file_.close();
}

void BufferedFile::write(const char *data, size_t size) {
    size_t bytes_written = 0;
    while (bytes_written < size) {
        size_t block_index = getBlockIndex(file_pos_);
        size_t offset_in_block = getOffsetInBlock(file_pos_);

        std::vector<char> block_data(block_size_, 0);
        cache_.get(block_index, block_data);

        size_t bytes_to_copy = std::min(size - bytes_written, block_size_ - offset_in_block);
        std::copy(data + bytes_written, data + bytes_written + bytes_to_copy, block_data.begin() + offset_in_block);

        cache_.put(block_index, block_data);
        bytes_written += bytes_to_copy;
        file_pos_ += bytes_to_copy;
    }
}

size_t BufferedFile::read(char *buffer, size_t size) {
    size_t bytes_read = 0;
    while (bytes_read < size) {
        size_t block_index = getBlockIndex(file_pos_);
        size_t offset_in_block = getOffsetInBlock(file_pos_);

        std::vector<char> block_data;
        if (!cache_.get(block_index, block_data)) {
            block_data.resize(block_size_, 0);
            file_.seekg(block_index * block_size_);
            file_.read(block_data.data(), block_size_);
            cache_.put(block_index, block_data);
        }

        size_t bytes_to_copy = std::min(size - bytes_read, block_size_ - offset_in_block);
        std::copy(block_data.begin() + offset_in_block, block_data.begin() + offset_in_block + bytes_to_copy, buffer + bytes_read);

        bytes_read += bytes_to_copy;
        file_pos_ += bytes_to_copy;
    }
    return bytes_read;
}

void BufferedFile::seek(std::streampos offset, std::ios::seekdir direction) {
    flush();
    file_.seekg(offset, direction);
    file_.seekp(offset, direction);
    file_pos_ = file_.tellg();
}

void BufferedFile::flush() {
    // 将缓存中的块数据写入文件
    for (auto &[block_index, block_data] : cache_.cache_list_) {
        file_.seekp(block_index * block_size_);
        file_.write(block_data.data(), block_data.size());
    }
}

// 获取给定位置所在的块索引
size_t BufferedFile::getBlockIndex(std::streampos pos) const {
    return pos / block_size_;
}

// 获取给定位置在块内的偏移量
size_t BufferedFile::getOffsetInBlock(std::streampos pos) const {
    return pos % block_size_;
}
