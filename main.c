#include <stdio.h>
#include <unistd.h>
#include "ls_core.h"

int main(int argc, char *argv[]) {
    int opt;
    while ((opt = getopt(argc, argv, "AacdfFhiklnqRrSstuw")) != -1) {
        switch (opt) {
            case 'A': opt_A = 1; break;
            case 'a': opt_a = 1; break;
            case 'c': opt_c = 1; opt_u = 0; break;
            case 'd': opt_d = 1; break;
            case 'F': opt_F = 1; break;
            case 'f': opt_f = 1; opt_s = 0; opt_a = 1; break;
            case 'h': opt_h = 1; opt_k = 0; break;
            case 'i': opt_i = 1; break;
            case 'k': opt_k = 1; opt_h = 0; break;
            case 'l': opt_l = 1; opt_n = 0; break;
            case 'n': opt_n = 1; opt_l = 1; break;
            case 'q': opt_q = 1; opt_w = 0; break;
            case 'R': opt_R = 1; opt_d = 0; break;
            case 'r': opt_r = 1; break;
            case 'S': opt_S = 1; break;
            case 's': opt_s = 1; break;
            case 't': opt_t = 1; break;
            case 'u': opt_u = 1; opt_c = 0; break;
            case 'w': opt_w = 1; opt_q = 0; break;
            default:
                fprintf(stderr, "Usage: %s [-AacdfFhiklnqRrSstuw] [file...]\n", argv[0]);
                return 1;
        }
    }

    if (optind >= argc) {
        list_directory(".");
    } else {
        for (int i = optind; i < argc; i++) {
            list_directory(argv[i]);
        }
    }

    return 0;
}
