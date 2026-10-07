#include <stdio.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include "format.h"

void print_long_format(const char *filepath, const char *filename, const struct stat *st) {
    char mode_str[11];

    if (S_ISDIR(st->st_mode)) mode_str[0] = 'd';
    else if (S_ISLNK(st->st_mode)) mode_str[0] = 'l';
    else if (S_ISCHR(st->st_mode)) mode_str[0] = 'c';
    else if (S_ISBLK(st->st_mode)) mode_str[0] = 'b';
    else if (S_ISSOCK(st->st_mode)) mode_str[0] = 's';
    else if (S_ISFIFO(st->st_mode)) mode_str[0] = 'p';
    else mode_str[0] = '-';

    mode_str[1] = (st->st_mode & S_IRUSR) ? 'r' : '-';
    mode_str[2] = (st->st_mode & S_IWUSR) ? 'w' : '-';
    mode_str[3] = (st->st_mode & S_IXUSR) ? 
                  ((st->st_mode & S_ISUID) ? 's' : 'x') : 
                  ((st->st_mode & S_ISUID) ? 'S' : '-');

    mode_str[4] = (st->st_mode & S_IRGRP) ? 'r' : '-';
    mode_str[5] = (st->st_mode & S_IWGRP) ? 'w' : '-';
    mode_str[6] = (st->st_mode & S_IXGRP) ? 
                  ((st->st_mode & S_ISGID) ? 's' : 'x') : 
                  ((st->st_mode & S_ISGID) ? 'S' : '-');

    mode_str[7] = (st->st_mode & S_IROTH) ? 'r' : '-';
    mode_str[8] = (st->st_mode & S_IWOTH) ? 'w' : '-';
    mode_str[9] = (st->st_mode & S_IXOTH) ? 
                  ((st->st_mode & S_ISVTX) ? 't' : 'x') : 
                  ((st->st_mode & S_ISVTX) ? 'T' : '-');
    mode_str[10] = '\0';

    struct passwd *pwd = getpwuid(st->st_uid);
    struct group *grp = getgrgid(st->st_gid);

    char time_str[64];
    struct tm *tm_info = localtime(&(st->st_mtime));
    strftime(time_str, sizeof(time_str), "%b %d %H:%M", tm_info);

    printf("%s %4ld %-8s %-8s %8ld %s %s",
           mode_str,
           (long)st->st_nlink,
           pwd ? pwd->pw_name : "unknown",
           grp ? grp->gr_name : "unknown",
           (long)st->st_size,
           time_str,
           filename);

    if (S_ISLNK(st->st_mode)) {
        char link_target[1024];
        ssize_t len = readlink(filepath, link_target, sizeof(link_target) - 1);
        if (len != -1) {
            link_target[len] = '\0';
            printf(" -> %s", link_target);
        }
    }
    printf("\n");
}
