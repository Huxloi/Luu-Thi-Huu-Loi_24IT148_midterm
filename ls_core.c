#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include "ls_core.h"
#include "format.h"
#include "sort.h"

void list_path(const char *path, int show_hidden, int long_format, int sort_time, int sort_size, int reverse_sort) {
    DIR *dir = opendir(path);
    if (!dir) {
        perror("ls error");
        return;
    }

    int capacity = 10;
    int count = 0;
    file_info_t *files = malloc(capacity * sizeof(file_info_t));
    if (!files) {
        closedir(dir);
        perror("malloc error");
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (!show_hidden && entry->d_name[0] == '.') {
            continue;
        }

        if (count >= capacity) {
            capacity *= 2;
            file_info_t *temp = realloc(files, capacity * sizeof(file_info_t));
            if (!temp) {
                free(files);
                closedir(dir);
                perror("realloc error");
                return;
            }
            files = temp;
        }

        strncpy(files[count].name, entry->d_name, sizeof(files[count].name) - 1);
        files[count].name[sizeof(files[count].name) - 1] = '\0';

        snprintf(files[count].path, sizeof(files[count].path), "%s/%s", path, entry->d_name);

        if (lstat(files[count].path, &files[count].st) < 0) {
            perror("lstat error");
        }

        count++;
    }
    closedir(dir);

    // Thực hiện sắp xếp
    if (sort_time) {
        qsort(files, count, sizeof(file_info_t), compare_by_time);
    } else if (sort_size) {
        qsort(files, count, sizeof(file_info_t), compare_by_size);
    } else {
        qsort(files, count, sizeof(file_info_t), compare_by_name);
    }

    // Nếu bật cờ -r, đảo ngược mảng sau khi sắp xếp
    if (reverse_sort) {
        for (int i = 0; i < count / 2; i++) {
            file_info_t temp = files[i];
            files[i] = files[count - 1 - i];
            files[count - 1 - i] = temp;
        }
    }

    // In kết quả
    for (int i = 0; i < count; i++) {
        if (long_format) {
            print_long_format(files[i].path, files[i].name, &files[i].st);
        } else {
            printf("%s\n", files[i].name);
        }
    }

    free(files);
}
