#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include "ls_core.h"
#include "format.h"
#include "sort.h"

int opt_A = 0, opt_a = 0, opt_c = 0, opt_d = 0, opt_F = 0, opt_f = 0;
int opt_h = 0, opt_i = 0, opt_k = 0, opt_l = 0, opt_n = 0, opt_q = 0;
int opt_R = 0, opt_r = 0, opt_S = 0, opt_s = 0, opt_t = 0, opt_u = 0, opt_w = 0;

void list_directory(const char *dir_path) {
    struct stat dir_stat;
    if (lstat(dir_path, &dir_stat) < 0) {
        perror("my_ls");
        return;
    }

    // Nếu là file thông thường hoặc có cờ -d, chỉ in chính nó
    if (!S_ISDIR(dir_stat.st_mode) || opt_d) {
        if (opt_i) printf("%lu ", (unsigned long)dir_stat.st_ino);
        if (opt_s) printf("%lld ", (long long)(dir_stat.st_blocks / 2));
        if (opt_l) {
            print_long_format(&dir_stat, dir_path, dir_path);
        } else {
            printf("%s\n", dir_path);
        }
        return;
    }

    DIR *dir = opendir(dir_path);
    if (!dir) {
        perror("my_ls");
        return;
    }

    file_info_t *files = NULL;
    int count = 0, capacity = 10;
    files = malloc(capacity * sizeof(file_info_t));

    long total_blocks = 0;
    struct dirent *entry;

    while ((entry = readdir(dir)) != NULL) {
        // Lọc ẩn theo -a và -A
        if (!opt_a && !opt_A && entry->d_name[0] == '.') continue;
        if (opt_A && entry->d_name[0] == '.' && (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)) continue;

        if (count >= capacity) {
            capacity *= 2;
            files = realloc(files, capacity * sizeof(file_info_t));
        }

        snprintf(files[count].path, sizeof(files[count].path), "%s/%s", dir_path, entry->d_name);
        snprintf(files[count].name, sizeof(files[count].name), "%s", entry->d_name);

        lstat(files[count].path, &files[count].statbuf);
        files[count].ino = files[count].statbuf.st_ino;
        files[count].blocks = files[count].statbuf.st_blocks;

        total_blocks += files[count].blocks;
        count++;
    }
    closedir(dir);

    // Sắp xếp nếu không có cờ -f
    if (!opt_f) {
        sort_files(files, count);
    }

    // In dòng total nếu dùng -l hoặc -s
    if (opt_l || opt_s) {
        printf("total %ld\n", total_blocks / 2);
    }

    // In danh sách file
    for (int i = 0; i < count; i++) {
        if (opt_i) {
            printf("%lu ", (unsigned long)files[i].ino);
        }
        if (opt_s) {
            printf("%lld ", (long long)(files[i].blocks / 2));
        }
        if (opt_l) {
            print_long_format(&files[i].statbuf, files[i].name, files[i].path);
        } else {
            printf("%s", files[i].name);
            if (opt_F) {
                char suffix = get_file_type_suffix(&files[i].statbuf);
                if (suffix) putchar(suffix);
            }
            printf("\n");
        }
    }

    // Đệ quy nếu có cờ -R
    if (opt_R) {
        for (int i = 0; i < count; i++) {
            if (S_ISDIR(files[i].statbuf.st_mode)) {
                if (strcmp(files[i].name, ".") == 0 || strcmp(files[i].name, "..") == 0) continue;
                printf("\n%s:\n", files[i].path);
                list_directory(files[i].path);
            }
        }
    }

    free(files);
}
