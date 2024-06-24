#include "../include/my.h"
#include <errno.h>

int read_client(SOCK sock, char *buffer)
{
    int n = read(sock, buffer, 1024 - 1);

    if (n < 0) {
        printf("read() error");
        n = 0;
    }
    buffer[n] = '\0';
    return n;
}

/*
utitlizing memset works fine on structs without pointers
this will need to be tweeked if pointers are added to the struct later on
thus the existence of this function instead of calling memset directly
*/
void reset_client(client_t *client)
{
    memset(client, 0, sizeof(client_t));
}

void init_new_client(client_t *client, SOCK socket)
{
    client->is_logged_in = false;
    client->socket = socket;
    memset(client->name, 0, MAX_NAME_LENGTH);
}

bool init_select(server_data_t *server_data, SOCK server_fd)
{
    FD_ZERO(&server_data->rdfs);
    FD_SET(server_fd, &server_data->rdfs);
    FD_SET(STDIN_FILENO, &server_data->rdfs);
    for (int i = 0; i < server_data->actual; i++)
        FD_SET(server_data->clients[i].socket, &server_data->rdfs);
    if (select(server_data->max + 1, &server_data->rdfs,
    NULL, NULL, NULL) == -1) {
        if (errno == EINTR)
            return false;
        else
            error("select() error");
    }
    return true;
}

server_data_t init_server_data(int server_fd)
{
    server_data_t data;

    data.max = server_fd;
    data.actual = 0;
    data.new_user_created = false;
    if (file_exists("save.dat")) {
        data.save = read_save();
        log_loaded_users(data.save);
    } else {
        memset(data.save.usernames, 0, MAX_NAME_LENGTH * 100);
        memset(data.save.username_connection_count, 0, sizeof(int) * 100);
        memset(data.save.private_messages, 0, sizeof(thread_t) * 10);
        fill_users_uuids(data.save.usernames_UUID);
    }
    return data;
}
