#ifndef LS_CORE_H
#define LS_CORE_H

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

typedef struct {
    char name[1024];
    char path[2048];
    struct stat statbuf;
    ino_t ino;
    blkcnt_t blocks;
} file_info_t;

// Khai báo các cờ tùy chọn theo NetBSD ls(1)
extern int opt_A, opt_a, opt_c, opt_d, opt_F, opt_f, opt_h, opt_i, opt_k, opt_l, opt_n, opt_q, opt_R, opt_r, opt_S, opt_s, opt_t, opt_u, opt_w;

void list_directory(const char *dir_path);

#endif
