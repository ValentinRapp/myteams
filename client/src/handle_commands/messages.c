#include "../../include/my.h"
#include "../../include/utils.h"
#include "../../include/revolution.h"
#include "../../include/client_lib.h"

void print_private_messages(messages_response_t response)
{
    int i = 0;

    while (response.messages.thread.messages[i].message_body[0]) {
        client_private_message_print_messages(
            response.messages.thread.messages[i].sender_uuid,
            response.messages.thread.messages[i].message_timestamp,
            response.messages.thread.messages[i].message_body
        );
        i++;
    }
}

void messages(char *buffer, SOCK socket, context_t context)
{
    NEW(messages_request_t, request) =
    {sizeof(messages_request_t), MESSAGES_REQUEST, {0}, {0}};
    NEW(messages_response_t, response);
    NEW(bool, success);
    if (!is_valid_nb_quotes(buffer, 1))
        return;
    remove_all_chars(buffer, '\"');
    strtok(buffer, " ");
    memcpy(request.sender_uuid, context.user_UUID, sizeof(char) * 37);
    memcpy(request.receiver_uuid, strtok(NULL, " "), sizeof(char) * 37);
    write(socket, &request, sizeof(messages_request_t));
    read(socket, &success, sizeof(bool));
    if (!success)
        client_error_unknown_user(request.receiver_uuid);
    read(socket, &response, sizeof(messages_response_t));
    if (success)
        print_private_messages(response);
}
