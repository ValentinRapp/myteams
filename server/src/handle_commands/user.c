#include "../../include/my.h"
#include "../../include/utils.h"
#include "../../include/server_lib.h"

int get_uuid_index(char UUID[37], char UUIDs[100][37])
{
    int i = 0;

    while (i < 100) {
        if (strcmp(UUID, UUIDs[i]) == 0) {
            return i;
            printf("%d\n", i);
        }
        i++;
    }
    printf("error %s\n", UUID);
    return -1;
}

void user(char *command, client_t *client, server_data_t *server)
{
    user_response_t response = {
        .len = sizeof(user_response_t), .code = USER_RESPONSE,
        .succeeded = false, .username = {0},
        .username_UUID = {0},
        .connection_count = 0
    };
    user_request_t request;
    int index;

    memcpy(&request, command, sizeof(user_request_t));
    index = get_uuid_index(request.UUID, server->save.usernames_UUID);
    if (index != -1) {
        response.succeeded = true;
        memcpy(response.username, server->save.usernames[index],
        MAX_NAME_LENGTH);
        memcpy(response.username_UUID, server->save.usernames_UUID[index], 37);
        response.connection_count =
        server->save.username_connection_count[index];
    }
    write(client->socket, &response, sizeof(user_response_t));
}
