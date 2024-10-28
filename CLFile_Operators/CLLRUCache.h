#ifndef LRUCACHE_H
#define LRUCACHE_H

#include <list>
#include <unordered_map>
#include <vector>
#include <cstddef>

using namespace std;

// 实现LRUCache类，用于缓存文件数据
class CLLRUCache {
public:
    CLLRUCache(size_t capacity, size_t bsize);

    // 获取缓存的值，若存在则返回true，并更新LRU数据
    bool get(size_t block_no, vector<char>& block_data);

    // 插入数据，超出容量则删除最久没有使用的数据块
    void put(size_t block_no, const vector<char>& block_data);

private:
    size_t _capacity;                     // 缓存块的数量
    size_t _bsize;                        // 每个块的大小
    list<pair<size_t, vector<char>>> cache_list; // 缓存双向链表
    unordered_map<size_t, decltype(cache_list.begin())> cache_map;// 用于定位的哈希表 
};

#endif
