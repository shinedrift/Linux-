#include "BufferedFile.h"
#include <iostream>

int main() {
    BufferedFile bufferedFile(64 * 1024 * 1024);
    if (bufferedFile.open("example.txt", std::ios::in | std::ios::out | std::ios::binary | std::ios::trunc)) {
        const char *data = "Hello, World!";
        bufferedFile.write(data, strlen(data));
        bufferedFile.seek(0, std::ios::beg);

        char buffer[13] = {0};
        bufferedFile.read(buffer, sizeof(buffer) - 1);
        std::cout << buffer << std::endl;

        bufferedFile.close();
    } else {
        std::cerr << "Failed to open file." << std::endl;
    }
    return 0;
}
