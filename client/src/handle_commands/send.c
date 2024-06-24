#include "../../include/my.h"
#include "../../include/utils.h"
#include "../../include/revolution.h"
#include "../../include/client_lib.h"

void send_command(char *buffer, SOCK socket, context_t context)
{
    send_t request = {sizeof(send_t), SEND, {0}, {0}, {0}};
    bool response;

    if (!is_valid_nb_quotes(buffer, 2))
        return;
    remove_all_chars(buffer, '\"');
    strtok(buffer, " ");
    memcpy(request.sender_uuid, context.user_UUID, sizeof(char) * 37);
    memcpy(request.receiver_uuid, strtok(NULL, " "), sizeof(char) * 37);
    memcpy(request.message_body, strtok(NULL, ""), MAX_BODY_LENGTH);
    write(socket, &request, sizeof(send_t));
    read(socket, &response, sizeof(bool));
    if (!response)
        client_error_unknown_user(request.receiver_uuid);
}
