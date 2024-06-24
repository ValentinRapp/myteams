#include "../include/my.h"

int init_server(int port)
{
    SOCK server_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in address;
    int opt = 1;

    if (server_fd == -1)
        exit(84);
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, 4) < 0) {
        close(server_fd);
        exit(84);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
        exit(84);
    if (listen(server_fd, 3) < 0)
        exit(84);
    return server_fd;
}
