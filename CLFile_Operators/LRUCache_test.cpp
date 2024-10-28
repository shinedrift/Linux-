#include "CLLRUCache.h"
#include <iostream>
#include <vector> 

int main() {
    // 创建一个 LRUCache 实例，容量为 4 块，每块大小为 4 字节
    CLLRUCache cache(4, 4);

    // 插入数据块
    cache.put(0, {'A', 'A', 'A', 'A'});
    cache.put(1, {'B', 'B', 'B', 'B'});
    cache.put(2, {'C', 'C', 'C', 'C'});
    cache.put(3, {'D', 'D', 'D', 'D'});

    // 打印缓存状态
    cache.printCacheState();

    // 测试获取块 1（更新块 1 的 LRU 顺序）
    std::vector<char> block_data;
    if (cache.get(1, block_data)) {
        std::cout << "Accessed block 1: ";
        for (char c : block_data) std::cout << c;
        std::cout << std::endl;
        cache.printCacheState();
    }
    
    // 添加新块以触发 LRU 机制
    cache.put(4, {'E', 'E', 'E', 'E'});  // 应该移除块 0（最久未使用）

    std::cout << "Put block 4" << std::endl;
    // 打印缓存状态
    cache.printCacheState();
    // 再次获取块 0（应不在缓存中）
    if (!cache.get(0, block_data)) {
        std::cout << "Block 0 has been evicted from cache." << std::endl;
    }

    // 检查是否按预期替换
    cache.put(5, {'F', 'F', 'F', 'F'});  // 应该移除块 2
    cache.printCacheState();
    return 0;
}
