#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "ls_core.h"

int main(int argc, char *argv[]) {
    int opt;
    int show_hidden = 0;
    int long_format = 0;
    int sort_time = 0;
    int sort_size = 0;
    int reverse_sort = 0;

    while ((opt = getopt(argc, argv, "altSr")) != -1) {
        switch (opt) {
            case 'a':
                show_hidden = 1;
                break;
            case 'l':
                long_format = 1;
                break;
            case 't':
                sort_time = 1;
                break;
            case 'S':
                sort_size = 1;
                break;
            case 'r':
                reverse_sort = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [-a] [-l] [-t] [-S] [-r] [file...]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    if (optind >= argc) {
        list_path(".", show_hidden, long_format, sort_time, sort_size, reverse_sort);
    } else {
        for (int i = optind; i < argc; i++) {
            list_path(argv[i], show_hidden, long_format, sort_time, sort_size, reverse_sort);
        }
    }

    return 0;
}
