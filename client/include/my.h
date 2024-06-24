#ifndef MY_H_
    #define MY_H_

    #define BUFFER_SIZE 2048
    #define SOCK    int
    #define MAX_NAME_LENGTH 32

    #define ELSE    else
    #define IF  if

    #include "lib.h"

    #include <stdbool.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #include <sys/select.h>

typedef struct {
    char user_UUID[37];
    char username[MAX_NAME_LENGTH];
    bool is_logged_in;
} context_t;

typedef struct {
    size_t len;
    int op_code;
} parsing_t;

int init_server_connection(char *ip, int port);
void handle_server_connection(SOCK server_socket);
void handle_command(char *buffer, SOCK socket, context_t *context);
int help(int exit_code);
void users(SOCK socket, context_t context);
void user(char *buffer, SOCK socket);
void send_command(char *buffer, SOCK socket, context_t context);
void messages(char *buffer, SOCK socket, context_t context);
void logout(SOCK socket, context_t *context);

#endif /* !MY_H_ */
