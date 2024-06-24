#include <uuid/uuid.h>
#include "../../include/my.h"
#include "../../include/utils.h"
#include "../../include/server_lib.h"

int get_new_user_index(char usernames[100][MAX_NAME_LENGTH])
{
    int i = 0;

    while (usernames[i][0] != 0) {
        if (i < 100)
            i++;
        else
            error("User limit exceeded (100)");
    }
    return i;
}

int user_exists(char *username, char usernames[100][MAX_NAME_LENGTH])
{
    int i = 0;

    while (usernames[i][0] != 0 && i < 100) {
        if (strncmp(username, usernames[i], strlen(username)) == 0)
            return i;
        i++;
    }
    return -1;
}

int get_user_index(char *username, char usernames[100][MAX_NAME_LENGTH],
    server_data_t *server_data)
{
    int index = user_exists(username, usernames);

    if (index != -1) {
        server_data->new_user_created = false;
        return index;
    }
    server_data->new_user_created = true;
    return get_new_user_index(usernames);
}

void fill_users_uuids(char usernames_UUID[100][37])
{
    uuid_t uuid;

    for (int i = 0; i < 100; i++) {
        uuid_generate_random(uuid);
        uuid_unparse(uuid, usernames_UUID[i]);
    }
}
