#ifndef MY_H_
    #define MY_H_

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <stdbool.h>
    #include <unistd.h>
    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <sys/select.h>
    #include <signal.h>

    #include "lib.h"
    #include "utils.h"

    #define MIN(a, b) ((a) < (b) ? (a) : (b))
    #define MAX_CLIENTS MIN(100, FD_SETSIZE)
    #define BUFFER_SIZE 1024
    #define SOCK    int
    #define MAX_NAME_LENGTH 32

    #define IF  if
    #define ELSE    else

// not completed yet, lacks a 'context' variable for example
typedef struct {
    SOCK socket;
    bool is_logged_in;
    char name[MAX_NAME_LENGTH];
} client_t;

/*
le coding style checker détecte pas les globales
quand elles sont entre 2 structs (rip bozo).
Il y a un bug qui empêche run de changer de valeur.
le code qui lui permet de changer de valeur est resté même si
ne fonctionnant pas, mais en attendant, j'utilise de la magie noire
pour détecter le ctrl-c (détecter si select a été interrompu par
un signal plutôt que de checker pour la valeur run elle même)
*/
static volatile sig_atomic_t run = true;

typedef struct {
    char usernames[MAX_CLIENTS][MAX_NAME_LENGTH];
    char usernames_UUID[MAX_CLIENTS][37];
    int username_connection_count[MAX_CLIENTS];
    // n_threads = n * (n - 1) // 2
    // with n = 5 for 5 users
    // allocating space for all 100 users would
    // weigh 264MB on the stack... yeah that segfaults
    thread_t private_messages[10];
} save_data_t;

typedef struct {
    char buffer[1024];
    int actual;
    int max;
    client_t clients[MAX_CLIENTS];
    bool new_user_created;
    fd_set rdfs;
    save_data_t save;
} server_data_t;

typedef struct {
    size_t len;
    int op_code;
} parsing_t;

int init_server(int port);
void handle_server(int server_fd);
server_data_t init_server_data(int server_fd);
bool init_select(server_data_t *server_data, SOCK server_fd);
void init_new_client(client_t *client, SOCK socket);
int read_client(SOCK sock, char *buffer);
void reset_client(client_t *client);
bool handle_command(char *command, client_t *client, server_data_t *server);
int get_user_index(char *username,
    char usernames[MAX_CLIENTS][MAX_NAME_LENGTH], server_data_t *server_data);
void fill_users_uuids(char usernames_UUID[MAX_CLIENTS][37]);
save_data_t read_save(void);
void write_save(save_data_t save);
void log_loaded_users(save_data_t save);
int get_uuid_index(char UUID[37], char UUIDs[MAX_CLIENTS][37]);
int get_thread_index(int user_1, int user_2);
void send_boolean_response(SOCK socket, bool to_send);

void close_session(client_t *client, server_data_t *server);
bool login(char *command, client_t *client, server_data_t *server);
bool logout(client_t *client, server_data_t *server_data);
void users(client_t *client, server_data_t *server);
void user(char *command, client_t *client, server_data_t *server);
void send_command(char *command, client_t client, server_data_t *server);
void messages(char *command, client_t client, server_data_t *server);

#endif /* !MY_H_ */
