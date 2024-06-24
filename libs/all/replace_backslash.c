void replace_backslash(char *str)
{
    while (*str) {
        if (*str == '\n') {
            *str = '\0';
            return;
        }
        *str++;
    }
}
