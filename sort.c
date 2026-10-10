#include <stdlib.h>
#include <string.h>
#include "sort.h"
#include "ls_core.h"

// So sánh theo tên (lexicographical order)
int compare_by_name(const void *a, const void *b) {
    const file_info_t *fa = (const file_info_t *)a;
    const file_info_t *fb = (const file_info_t *)b;
    int res = strcmp(fa->name, fb->name);
    return opt_r ? -res : res;
}

// So sánh theo thời gian sửa đổi (-t)
int compare_by_time(const void *a, const void *b) {
    const file_info_t *fa = (const file_info_t *)a;
    const file_info_t *fb = (const file_info_t *)b;
    
    if (fb->statbuf.st_mtime > fa->statbuf.st_mtime) return opt_r ? -1 : 1;
    if (fb->statbuf.st_mtime < fa->statbuf.st_mtime) return opt_r ? 1 : -1;
    return compare_by_name(a, b);
}

// So sánh theo kích thước file (-S)
int compare_by_size(const void *a, const void *b) {
    const file_info_t *fa = (const file_info_t *)a;
    const file_info_t *fb = (const file_info_t *)b;
    
    if (fb->statbuf.st_size > fa->statbuf.st_size) return opt_r ? -1 : 1;
    if (fb->statbuf.st_size < fa->statbuf.st_size) return opt_r ? 1 : -1;
    return compare_by_name(a, b);
}

void sort_files(file_info_t *files, int count) {
    if (count < 2) return;
    if (opt_t) {
        qsort(files, count, sizeof(file_info_t), compare_by_time);
    } else if (opt_S) {
        qsort(files, count, sizeof(file_info_t), compare_by_size);
    } else {
        qsort(files, count, sizeof(file_info_t), compare_by_name);
    }
}
