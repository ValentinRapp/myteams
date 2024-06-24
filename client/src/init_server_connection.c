#include "../include/my.h"

int init_server_connection(char *ip, int port)
{
    SOCK server_socket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_address;

    if (server_socket == -1) {
        error("Failed to create socket");
        return -1;
    }
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(ip);
    server_address.sin_port = htons(port);
    if (connect(server_socket, (struct sockaddr *)&server_address,
    sizeof(server_address)) < 0)
        error("Failed to connect to server");
    return server_socket;
}
