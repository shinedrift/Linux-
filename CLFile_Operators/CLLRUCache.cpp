#include "CLLRUCache.h"

CLLRUCache::CLLRUCache(size_t capacity, size_t bsize)
     : _capacity(capacity), _bsize(bsize) {}

bool CLLRUCache::get(size_t block_no, std::vector<char>& block_data)
{
    // 获取块号对应节点，没有则返回false
    auto item = cache_map.find(block_no);
    if (item == cache_map.end()) return false;
    // 找到对应节点，则将对应块置于表头，代表最近使用
    cache_list.splice(cache_list.begin(), cache_list, item->second);
    block_data = it->second->second;
    return true;
}

void CLLRUCache::put(size_t block_no, std::vector<char>& block_data)
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
