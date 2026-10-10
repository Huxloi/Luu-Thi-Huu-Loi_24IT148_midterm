#ifndef FORMAT_H
#define FORMAT_H

#include <sys/types.h>
#include <sys/stat.h>

void print_long_format(const struct stat *st, const char *filepath, const char *filename);
void format_human_size(off_t bytes, char *buf, size_t maxlen);
char get_file_type_suffix(struct stat *st);

#endif
