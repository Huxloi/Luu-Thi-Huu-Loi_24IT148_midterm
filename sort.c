#include <string.h>
#include "sort.h"

// Sắp xếp theo tên (thứ tự từ điển)
int compare_by_name(const void *a, const void *b) {
    const file_info_t *fa = (const file_info_t *)a;
    const file_info_t *fb = (const file_info_t *)b;
    return strcmp(fa->name, fb->name);
}

// Sắp xếp theo thời gian sửa đổi (mới nhất lên trước)
int compare_by_time(const void *a, const void *b) {
    const file_info_t *fa = (const file_info_t *)a;
    const file_info_t *fb = (const file_info_t *)b;
    if (fb->st.st_mtime > fa->st.st_mtime) return 1;
    if (fb->st.st_mtime < fa->st.st_mtime) return -1;
    return strcmp(fa->name, fb->name); // Nếu trùng thời gian thì sắp theo tên
}

// Sắp xếp theo kích thước (file lớn nhất lên trước)
int compare_by_size(const void *a, const void *b) {
    const file_info_t *fa = (const file_info_t *)a;
    const file_info_t *fb = (const file_info_t *)b;
    if (fb->st.st_size > fa->st.st_size) return 1;
    if (fb->st.st_size < fa->st.st_size) return -1;
    return strcmp(fa->name, fb->name);
}
