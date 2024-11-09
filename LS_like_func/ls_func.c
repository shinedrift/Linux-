#include "ls_func.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>

// 使用宏判断文件类型
char get_file_type(mode_t st_mode) {
    if (S_ISREG(st_mode)) return '-';
    if (S_ISDIR(st_mode)) return 'd';
    if (S_ISLNK(st_mode)) return 'l';
    if (S_ISCHR(st_mode)) return 'c'; 
    if (S_ISBLK(st_mode)) return 'b';
    if (S_ISFIFO(st_mode)) return 'p';
    if (S_ISSOCK(st_mode)) return 's';
    return '?'; 
}

// 根据st_mode的低11位，获取文件权限
void get_permissions(mode_t st_mode, char* perm) {
   perm[0] = (st_mode & S_IRUSR) ? 'r' : '-';
   perm[1] = (st_mode & S_IWUSR) ? 'w' : '-';
   perm[2] = (st_mode & S_IXUSR) ? 'x' : '-';
   perm[3] = (st_mode & S_IRGRP) ? 'r' : '-';
   perm[4] = (st_mode & S_IWGRP) ? 'w' : '-';
   perm[5] = (st_mode & S_IXGRP) ? 'x' : '-';
   perm[6] = (st_mode & S_IROTH) ? 'r' : '-';
   perm[7] = (st_mode & S_IWOTH) ? 'w' : '-';
   perm[8] = (st_mode & S_IXOTH) ? 'x' : '-';
   perm[9] = '\0';
}

// 获取file_stat结构体的文件大小
off_t get_file_size(const struct stat *file_stat) {
    return file_stat->st_size;
}

// 获取文件名称
const char* get_file_name(const char* path) {
    return path;
}

// 打印文件信息
void print_file_info(const char* path, const char* d_name) {
    struct stat file_stat;
    mode_t mode;
    if (stat(path, &file_stat) == -1) {
        perror("get stat failed");
        exit(EXIT_FAILURE);
    }
    
    // 从file_stat中获取需要的信息
    char perm[10];
    mode = file_stat.st_mode;
    char file_type = get_file_type(mode);
    get_permissions(mode, perm);

    off_t file_size = get_file_size(&file_stat);
    const char* file_name = get_file_name(d_name);

    printf("%c%s %-4ld %s\n", file_type, perm, file_size, file_name);
}

// 遍历目录下的每个文件，打印其信息

void myls(const char* path) {
    DIR *dir = opendir(path);
    if (dir == NULL) {
        perror("opendir failed");
        exit(EXIT_FAILURE);
    }
    
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        char full_path[512];
        memset(full_path, 0, sizeof(full_path));
		strcpy(full_path, path);
		strcat(full_path, "/");
		strcat(full_path, entry->d_name);
        print_file_info(full_path, entry->d_name);
    }
    closedir(dir);
    exit(1);
}
