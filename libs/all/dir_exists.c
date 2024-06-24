#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdbool.h>

bool dir_exists(const char *path)
{
    struct stat sb;

    if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode)) {
        return true;
    }
    return false;
}
