#include <sys/stat.h>
#include <stdio.h>
#include <stdbool.h>

bool file_exists(const char *filename)
{
    struct stat buffer;
    int exist = stat(filename, &buffer);

    if (exist == 0)
        return true;
    else
        return false;
}
