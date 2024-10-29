#ifndef BUFFEREDFILE_H
#define BUFFEREDFILE_H

#include <iostream>
#include <fstream>
#include "CLLRUCache.h"

class CLBufferedFile {
public:
    CLBufferedFile(const std::string &file_path, size_t buffer_size = 64 * 1024 * 1024, 
                 size_t block_size = 4096,  // 块大小，默认为4KB
                 std::ios::openmode mode = std::ios::in | std::ios::out | std::ios::binary);
    ~CLBufferedFile();

    void write(const char *data, size_t size);
    size_t read(char *buffer, size_t size);
    void seek(std::streampos offset, std::ios::seekdir direction);

private:
    std::fstream file_;
    size_t block_size_;
    std::streampos file_pos_;
    CLLRUCache cache_;

    void flush();  // 将缓存的块写入文件
    size_t getBlockIndex(std::streampos pos) const;  // 获取位置所在块的索引
    size_t getOffsetInBlock(std::streampos pos) const;  // 获取位置在块内的偏移
};

#endif // BUFFEREDFILE_H
