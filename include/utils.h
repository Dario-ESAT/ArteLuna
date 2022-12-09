#ifndef __UTILS_H__
#define __UTILS_H__ 1
#include <cassert>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>

static unsigned char* ReadFile(const char* filename)
{
    FILE* in_file = 0;
    int err = fopen_s(&in_file, filename, "rb");
    assert(in_file);
    struct stat sb;
    assert(stat(filename, &sb) != -1);
    unsigned char* file_contents = (unsigned char*)malloc(sb.st_size + 1);
    if (file_contents) {
        fread(file_contents, sb.st_size, 1, in_file);
        file_contents[sb.st_size] = 0;
        fclose(in_file);
    }
    return file_contents;
}



#endif