#include <stdbool.h>

bool is_valid_nb_quotes(char *command, int n_parameters)
{
    int i = 0;
    int n_quotes = 0;

    while (command[i]) {
        if (command[i] == '\"')
            n_quotes++;
        i++;
    }
    return (n_parameters * 2) == n_quotes;
}

void remove_all_chars(char *str, char c)
{
    char *pr = str;
    char *pw = str;

    while (*pr) {
        *pr++;
        *pw = *pr;
        pw += (*pw != c);
    }
    *pw = '\0';
}
