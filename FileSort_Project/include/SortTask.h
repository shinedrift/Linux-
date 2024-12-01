// include/SortTask.h
// SortTask类定义文件，支持外部排序

#ifndef SORTTASK_H
#define SORTTASK_H

#include <vector>
#include <string>
#include <stdint.h>  // 引入stdint.h以使用int64_t

// SortTask类，封装外部排序的功能
class SortTask {
public:
    SortTask(const std::string& inputFilePath, const std::string& outputFilePath);

    void externalSort();  // 外部排序的主要方法

private:
    std::string inputFilePath;   // 输入文件路径
    std::string outputFilePath;  // 输出文件路径
    size_t chunkSize;            // 每个块的大小，默认为64MB

    void splitAndSortChunks();   // 分块读取、排序并写入临时文件
    void mergeChunks();          // 多路归并排序临时文件，写入输出文件
};

#endif
