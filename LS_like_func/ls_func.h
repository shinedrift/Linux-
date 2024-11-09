#ifndef LS_FUNC_H
#define LS_FUNC_H

#include<sys/stat.h>

// 获取文件类型
char get_file_type(mode_t st_mode);

// 获取文件访问权限
void get_permissons(mode_t st_mode, char* perm);

// 获取文件大小
off_t get_file_size(const struct stat *file_stat);

// 获取文件名
const char* get_file_name(const char* path);

// 打印文件信息
void print_file_info(const char *path, const char* d_name);

// 根据路径打印路径下文件信息
void myls(const char* path);

#endif
