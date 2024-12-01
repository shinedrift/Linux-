#include "CLBufferedFile.h"
#include <iostream>
#include <cstring>
#include <chrono>
#include <fstream>
#include <cstdlib>
#include <ctime>

#define FILE_SIZE 1 * 1024 * 1024 * 1024  // 文件大小：1GB
#define BLOCK_SIZE 4096*2                   // 块大小：4KB
#define CACHE_CAPACITY 256                // 缓存容量：256个块

// 模拟不使用缓存的写入操作
void writeWithoutCache(const std::string &filename) {
    std::ofstream file(filename, std::ios::out | std::ios::binary);
    if (!file) {
        std::cerr << "Error opening file for writing" << std::endl;
        return;
    }

    std::vector<char> data(BLOCK_SIZE, 'A');  // 每块写入 'A'
    for (size_t i = 0; i < FILE_SIZE / BLOCK_SIZE; ++i) {
        file.write(data.data(), BLOCK_SIZE);
    }

    file.close();
}

// 模拟不使用缓存的读取操作
void readWithoutCache(const std::string &filename) {
    std::ifstream file(filename, std::ios::in | std::ios::binary);
    if (!file) {
        std::cerr << "Error opening file for reading" << std::endl;
        return;
    }

    std::vector<char> buffer(BLOCK_SIZE);
    for (size_t i = 0; i < FILE_SIZE / BLOCK_SIZE; ++i) {
        file.read(buffer.data(), BLOCK_SIZE);
    }

    file.close();
}

// 模拟随机访问文件并读取
void randomAccessRead(CLBufferedFile &bufferedFile) {
    std::vector<char> buffer(BLOCK_SIZE);
    size_t num_accesses = 0;
    
    // 随机读取文件中的块，模拟缓存命中/未命中
    for (size_t i = 0; i < FILE_SIZE / BLOCK_SIZE; ++i) {
        size_t block_num = rand() % (FILE_SIZE / BLOCK_SIZE);
        bufferedFile.read(buffer.data(), BLOCK_SIZE);
        num_accesses++;
    }
    std::cout << "Total accesses: " << num_accesses << std::endl;
}

// 使用缓存的写入性能测试
void writeWithCache(CLBufferedFile &bufferedFile) {
    std::vector<char> data(BLOCK_SIZE, 'A');  // 每块写入 'A'
    for (size_t i = 0; i < FILE_SIZE / BLOCK_SIZE; ++i) {
        bufferedFile.write(data.data(), BLOCK_SIZE);
    }
}

// 使用缓存的读取性能测试
void readWithCache(CLBufferedFile &bufferedFile) {
    std::vector<char> buffer(BLOCK_SIZE);
    for (size_t i = 0; i < FILE_SIZE / BLOCK_SIZE; ++i) {
        bufferedFile.read(buffer.data(), BLOCK_SIZE);
    }
}

int main() {
    srand(time(0));  // 设置随机种子

    std::string filename = "test_file.bin";
    
    // 不使用缓存的写入性能测试
    auto start = std::chrono::high_resolution_clock::now();
    writeWithoutCache(filename);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> write_no_cache_duration = end - start;
    std::cout << "Write without cache time: " << write_no_cache_duration.count() << " seconds" << std::endl;

    // 不使用缓存的读取性能测试
    start = std::chrono::high_resolution_clock::now();
    readWithoutCache(filename);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> read_no_cache_duration = end - start;
    std::cout << "Read without cache time: " << read_no_cache_duration.count() << " seconds" << std::endl;

    // 使用缓存的写入性能测试
    CLBufferedFile bufferedFileWithCache(filename, FILE_SIZE, BLOCK_SIZE, std::ios::in | std::ios::out | std::ios::binary);
    start = std::chrono::high_resolution_clock::now();
    writeWithCache(bufferedFileWithCache);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> write_with_cache_duration = end - start;
    std::cout << "Write with cache time: " << write_with_cache_duration.count() << " seconds" << std::endl;

    // 使用缓存的读取性能测试
    start = std::chrono::high_resolution_clock::now();
    readWithCache(bufferedFileWithCache);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> read_with_cache_duration = end - start;
    std::cout << "Read with cache time: " << read_with_cache_duration.count() << " seconds" << std::endl;

    // 随机访问测试
    std::cout << "Random access with cache:" << std::endl;
    randomAccessRead(bufferedFileWithCache);

    return 0;
}

