#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *copy_string(const char *src)
{
    size_t size = strlen(src) + 1;
    char *cpy = malloc(size);

    strcpy(cpy, src);
    return cpy;
}
