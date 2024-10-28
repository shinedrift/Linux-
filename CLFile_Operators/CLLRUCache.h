#ifndef LRUCACHE_H
#define LRUCACHE_H

#include <iostream>
#include <list>
#include <unordered_map>
#include <vector>
#include <cstddef>

// 实现LRUCache类，用于缓存文件数据
class CLLRUCache {
public:
    CLLRUCache(size_t capacity, size_t bsize);

    // 获取缓存的值，若存在则返回true，并更新LRU数据
    bool get(size_t block_no, std::vector<char>& block_data);

    // 插入数据，超出容量则删除最久没有使用的数据块
    void put(size_t block_no, const std::vector<char>& block_data);

    // 打印当前缓存状态（用于测试）
    void printCacheState() const;
private:
    size_t _capacity;                     // 缓存块的数量
    size_t _bsize;                        // 每个块的大小
    std::list<std::pair<size_t, std::vector<char>>> cache_list; // 缓存双向链表
    std::unordered_map<size_t, decltype(cache_list.begin())> cache_map;// 用于定位的哈希表 
};

CLLRUCache::CLLRUCache(size_t capacity, size_t bsize)
     : _capacity(capacity), _bsize(bsize) {}

bool CLLRUCache::get(size_t block_no, std::vector<char>& block_data)
{
    // 获取块号对应节点，没有则返回false
    auto item = cache_map.find(block_no);
    if (item == cache_map.end()) return false;
    // 找到对应节点，则将对应块置于表头，代表最近使用
    cache_list.splice(cache_list.begin(), cache_list, item->second);
    block_data = item->second->second;
    return true;
}

void CLLRUCache::put(size_t block_no, const std::vector<char>& block_data)
{
        // 已存在则移除旧块
    if (cache_map.find(block_no) != cache_map.end()) {
        cache_list.erase(cache_map[block_no]);
    } else if (cache_list.size() >= _capacity) {
        // 超出容量则移除尾节点
        cache_map.erase(cache_list.back().first);
        cache_list.pop_back();
    }
        // 插入新块到头节点
    cache_list.emplace_front(block_no, block_data);
    cache_map[block_no] = cache_list.begin();
}

// 打印缓存状态（从最近使用到最久未使用的顺序）
void CLLRUCache::printCacheState() const {
    std::cout << "Current cache state (most recent to least recent):" << std::endl;
    for (const auto& entry : cache_list) {
        std::cout << "Block " << entry.first << ": ";
        for (char c : entry.second) {
            std::cout << c;
        }
        std::cout << std::endl;
    }
    std::cout << "-----------------------------" << std::endl;
}

#endif
