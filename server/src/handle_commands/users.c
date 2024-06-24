#include "../../include/my.h"
#include "../../include/utils.h"
#include "../../include/server_lib.h"

void users(client_t *client, server_data_t *server)
{
    users_response_t response = {
        .len = sizeof(users_response_t),
        .code = USERS_RESPONSE,
        .usernames = {{0}},
        .usernames_UUID = {{0}},
        .username_connection_count = {0}
    };

    memcpy(response.usernames, server->save.usernames,
    sizeof(server->save.usernames));
    memcpy(response.usernames_UUID, server->save.usernames_UUID,
    sizeof(server->save.usernames_UUID));
    memcpy(response.username_connection_count,
    server->save.username_connection_count,
    sizeof(server->save.username_connection_count));
    write(client->socket, &response, sizeof(users_response_t));
}
