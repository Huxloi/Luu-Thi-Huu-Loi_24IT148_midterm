#include <stdio.h>
#include <string.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <sys/stat.h>
#include <unistd.h>
#include "format.h"

char get_file_type_suffix(struct stat *st) {
    if (S_ISDIR(st->st_mode)) return '/';
    if (S_ISLNK(st->st_mode)) return '@';
    if (S_ISFIFO(st->st_mode)) return '|';
    if (S_ISSOCK(st->st_mode)) return '=';
    if ((st->st_mode & S_IXUSR) || (st->st_mode & S_IXGRP) || (st->st_mode & S_IXOTH)) return '*';
    return '\0';
}

void print_long_format(const struct stat *st, const char *filepath, const char *filename) {
    char mode_str[11];
    strmode(st->st_mode, mode_str);

    struct passwd *pw = getpwuid(st->st_uid);
    struct group *gr = getgrgid(st->st_gid);

    char time_str[64];
    struct tm *tm_info = localtime(&st->st_mtime);
    strftime(time_str, sizeof(time_str), "%b %d %H:%M", tm_info);

    printf("%s %3ld %-8s %-8s %8lld %s %s",
           mode_str,
           (long)st->st_nlink,
           pw ? pw->pw_name : "unknown",
           gr ? gr->gr_name : "unknown",
           (long long)st->st_size,
           time_str,
           filename);

    if (S_ISLNK(st->st_mode)) {
        char linkbuf[1024];
        ssize_t len = readlink(filepath, linkbuf, sizeof(linkbuf) - 1);
        if (len != -1) {
            linkbuf[len] = '\0';
            printf(" -> %s", linkbuf);
        }
    }
    printf("\n");
}
