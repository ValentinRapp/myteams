#ifndef ALL_H_
    #define ALL_H_

    #include <stdbool.h>

bool dir_exists(const char *path);
bool is_number(char *str);
bool is_valid_ip(char *ip);
void error(char *message);
void replace_backslash(char *str);
char *copy_string(const char *src);
bool file_exists(const char *filename);
void remove_all_chars(char *str, char c);
bool is_valid_nb_quotes(char *command, int n_parameters);

#endif /* !ALL_H_ */
