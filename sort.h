#ifndef SORT_H
#define SORT_H

#include <sys/stat.h>

// Cấu trúc lưu thông tin file để phục vụ việc sắp xếp
typedef struct {
    char name[1024];
    char path[1024];
    struct stat st;
} file_info_t;

// Các hàm so sánh cho qsort
int compare_by_name(const void *a, const void *b);
int compare_by_time(const void *a, const void *b);
int compare_by_size(const void *a, const void *b);

#endif
