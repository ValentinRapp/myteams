#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void error(char *message)
{
    write(1, message, strlen(message));
    write(1, "\n", 1);
    exit(84);
}
