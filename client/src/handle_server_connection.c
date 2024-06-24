#include "../include/my.h"
#include "../include/utils.h"
#include "../include/revolution.h"
#include "../include/client_lib.h"

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

void handle_server_requests(SOCK socket, context_t *context)
{
    parsing_t parsing;
    char buffer[1024];
    int c = read_client(socket, buffer);

    if (c == 0)
        exit(0);
    memcpy(&parsing, buffer, sizeof(parsing_t));
    if (parsing.op_code == QUIT) {
        if (context->is_logged_in)
            logout(socket, context);
        exit(0);
    }
    if (parsing.op_code == MESSAGE_SENT) {
        NEW(message_sent_t, message);
        memcpy(&message, buffer, sizeof(message_sent_t));
        client_event_private_message_received(message.uuid, message.message);
    }
}

void handle_client_requests(char *buffer, SOCK server_sock, context_t *context)
{
    if (fgets(buffer, BUFFER_SIZE, stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
        handle_command(buffer, server_sock, context);
        memset(buffer, 0, BUFFER_SIZE);
        return;
    }
    if (feof(stdin)) {
        if (context->is_logged_in)
            logout(server_sock, context);
        write(server_sock, &(quit_t){sizeof(quit_t), QUIT}, sizeof(quit_t));
        printf("exit.\n");
        exit(0);
    } else {
        printf("error while reading stdin.\n");
        exit(0);
    }
}

void handle_server_connection(SOCK server_socket)
{
    fd_set readfds;
    char buffer[BUFFER_SIZE];
    context_t context = {{0}, {0}, false};

    while (1) {
        FD_ZERO(&readfds);
        FD_SET(STDIN_FILENO, &readfds);
        FD_SET(server_socket, &readfds);
        if (select(server_socket + 1, &readfds, NULL, NULL, NULL) < 0)
            error("select() error");
        if (FD_ISSET(STDIN_FILENO, &readfds))
            handle_client_requests(buffer, server_socket, &context);
        if (FD_ISSET(server_socket, &readfds))
            handle_server_requests(server_socket, &context);
    }
    close(server_socket);
}
