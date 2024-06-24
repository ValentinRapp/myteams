#include "../../include/my.h"
#include "../../include/utils.h"
#include "../../include/revolution.h"
#include "../../include/client_lib.h"

void user(char *buffer, SOCK socket)
{
    user_response_t response;
    user_request_t request = {sizeof(user_request_t), USER_REQUEST, {0}};
    char UUID[37];

    if (!is_valid_nb_quotes(buffer, 1))
        return;
    remove_all_chars(buffer, '\"');
    strtok(buffer, " ");
    memcpy(UUID, strtok(NULL, " "), 37);
    memcpy(request.UUID, UUID, 37);
    write(socket, &request, sizeof(user_request_t));
    read(socket, &response, sizeof(user_response_t));
    response.connection_count = response.connection_count ? 1 : 0;
    if (!response.succeeded)
        client_error_unknown_user(request.UUID);
    else
        client_print_user(UUID, response.username, response.connection_count);
}
