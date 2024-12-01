#include "CLBufferedFile.h"
#include <iostream>
#include <cstring>

int main() {
    try {
        // 创建 BufferedFile 实例，块大小为 4KB
        CLBufferedFile bufferedFile("example.txt", 64 * 1024 * 1024, 4096);

        // 写入一些数据到文件
        const char *data = "Hello, World!";
        bufferedFile.write(data, strlen(data));

        // 移动文件指针到文件开头
        bufferedFile.seek(0, std::ios::beg);

        // 读取写入的数据，确保缓冲区足够大并添加字符串终止符
        char buffer[14] = {0};  // 多留一个空间用于 `\0`
        bufferedFile.read(buffer, sizeof(buffer) - 1);
        buffer[13] = '\0';  // 手动添加终止符
        std::cout << "Read data: " << buffer << std::endl;

        // 再次写入数据，检查缓存效果
        const char *moreData = "Buffered File Test";
        bufferedFile.write(moreData, strlen(moreData));
        bufferedFile.seek(0, std::ios::beg);

        // 读取新数据以验证缓存和写入是否成功
        char buffer2[31] = {0};  // 增大缓冲区以容纳全部数据
        bufferedFile.read(buffer2, sizeof(buffer2) - 1);
        buffer2[30] = '\0';  // 手动添加终止符
        std::cout << "Read data after additional write: " << buffer2 << std::endl;

    } catch (const std::ios_base::failure &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
