#include "../../include/my.h"
#include "../../include/utils.h"

void close_session(client_t *client, server_data_t *server)
{
    printf("Closing session\n");
    close(client->socket);
    FD_CLR(client->socket, &server->rdfs);
    reset_client(client);
}
