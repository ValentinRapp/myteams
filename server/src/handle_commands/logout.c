#include "../../include/my.h"
#include "../../include/utils.h"
#include "../../include/server_lib.h"

bool logout(client_t *client, server_data_t *server_data)
{
    int i = 0;

    if (client->is_logged_in == false)
        return false;
    client->is_logged_in = false;
    while (strcmp(client->name, server_data->save.usernames[i]) != 0)
        i++;
    memset(client->name, 0, MAX_NAME_LENGTH);
    server_data->save.username_connection_count[i] -= 1;
    server_event_user_logged_out(server_data->save.usernames_UUID[i]);
    return true;
}
