#include "../../include/my.h"
#include "../../include/utils.h"
#include "../../include/server_lib.h"

void log_loaded_users(save_data_t save)
{
    int i = 0;

    while (save.usernames[i][0] && i < 100) {
        server_event_user_loaded(save.usernames[i], save.usernames_UUID[i]);
        i++;
    }
}
