#include "../include/my.h"
#include "../include/revolution.h"
#include "../include/utils.h"
#include "../include/server_lib.h"

void handle_client_logging_in(server_data_t *server_data, int csock)
{
    server_data->max = csock > server_data->max ? csock : server_data->max;
    FD_SET(csock, &server_data->rdfs);
    printf("New connection\n");
    init_new_client(server_data->clients + server_data->actual, csock);
    server_data->actual++;
}

void handle_input(server_data_t *server_data)
{
    if (!run)
        return;
    for (int i = 0; i < server_data->actual; i++) {
        if (FD_ISSET(server_data->clients[i].socket, &server_data->rdfs)) {
            NEW(int, c) = read_client(server_data->clients[i].socket,
            server_data->buffer);
            printf("Incoming command from client\n");
            IF(c == 0) {
                close_session(&server_data->clients[i], server_data);
            } ELSE {
                handle_command(server_data->buffer, &server_data->clients[i],
                server_data);
            }
        }
    }
}

int create_new_client_socket(SOCK server_sock)
{
    struct sockaddr_in csin = {0};
    socklen_t sinsize = sizeof csin;

    return accept(server_sock, (struct sockaddr *)&csin, &sinsize);
}

void exit_server(server_data_t server_data)
{
    for (int i = 0; i < server_data.actual; i++) {
        write(server_data.clients[i].socket,
            &(quit_t){sizeof(quit_t), QUIT}, sizeof(quit_t));
    }
    for (int i = 0; i < 100; i++) {
        while (server_data.save.username_connection_count[i] > 0) {
            server_event_user_logged_out(server_data.save.usernames_UUID[i]);
            server_data.save.username_connection_count[i]--;
        }
    }
    write_save(server_data.save);
    exit(0);
}

void handle_server(int server_fd)
{
    server_data_t server_data = init_server_data(server_fd);
    char stdin_buffer[1024];

    while (run) {
        run = init_select(&server_data, server_fd);
        if (!run)
            break;
        if (FD_ISSET(STDIN_FILENO, &server_data.rdfs) && run)
            IF(read(STDIN_FILENO, stdin_buffer, sizeof(stdin_buffer)) == 0)
                run = false;
        if (FD_ISSET(server_fd, &server_data.rdfs) && run) {
            NEW(SOCK, csock) = create_new_client_socket(server_fd);
            IF(csock == -1)
                continue;
            handle_client_logging_in(&server_data, csock);
        } else
            handle_input(&server_data);
    }
    exit_server(server_data);
}
