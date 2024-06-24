#include "../../include/my.h"
#include "../../include/utils.h"
#include "../../include/revolution.h"
#include "../../include/client_lib.h"

void users(SOCK socket, context_t context)
{
    users_response_t response;
    int i = 0;

    if (!context.is_logged_in)
        return;
    write(socket, &(users_request_t){sizeof(users_request_t), USERS_REQUEST},
    sizeof(users_request_t));
    read(socket, &response, sizeof(users_response_t));
    while (response.usernames[i][0]) {
        response.username_connection_count[i] =
            response.username_connection_count[i] ? 1 : 0;
        i++;
    }
    i = 0;
    while (response.usernames[i][0]) {
        client_print_users(response.usernames_UUID[i],
            response.usernames[i],
            response.username_connection_count[i]);
        i++;
    }
}
