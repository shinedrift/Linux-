# 任务
    实现一个带缓存的文件操作类  

# 要求
    提供open/read/write/lseek/close等函数的封装函数
    该类要提供数据缓存服务
        - write：先写入缓存，再根据策略写入文件
        - read: 根据策略缓存读出的数据

# 当前思路

## 设计一个bcache类
    提供满足lru算法的接口，包括bwrite、bread、binit、bclear  

## 实现对文件系统调用的封装


## 在mian.c中测试文件
