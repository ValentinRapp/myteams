#include "../../include/my.h"
#include "../../include/utils.h"
#include "../../include/server_lib.h"

// printf("\nusername\tUUID\n");
// for (int i = 0; server->usernames[i][0]; i++) {
//     printf("%s\t\t%s\n", server->usernames[i], server->usernames_UUID[i]);
// }
// printf("\n");
bool login(char *command, client_t *client, server_data_t *server)
{
    login_t info;
    int index;
    char UUID[37];

    client->is_logged_in = true;
    memcpy(&info, command, sizeof(login_t));
    memcpy(client->name, info.username, strlen(info.username));
    index = get_user_index(info.username, server->save.usernames, server);
    if (server->new_user_created)
        server_event_user_created(server->save.usernames_UUID[index],
        info.username);
    memcpy(server->save.usernames[index],
    info.username, strlen(info.username));
    memcpy(UUID, server->save.usernames_UUID[index], sizeof(UUID));
    server->save.username_connection_count[index] += 1;
    server_event_user_logged_in(UUID);
    write(client->socket, UUID, 37);
    return true;
}
