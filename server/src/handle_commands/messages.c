#include "../../include/my.h"
#include "../../include/utils.h"
#include "../../include/revolution.h"

void messages(char *command, client_t client, server_data_t *server)
{
    messages_request_t request;
    messages_response_t response;
    int user_1;
    int user_2;
    int thread_index;

    memcpy(&request, command, sizeof(messages_request_t));
    user_1 = get_uuid_index(request.sender_uuid, server->save.usernames_UUID);
    user_2 = get_uuid_index(request.receiver_uuid, server->save.usernames_UUID)
    ;
    if (user_1 == -1 || user_2 == -1)
        return send_boolean_response(client.socket, false);
    thread_index = get_thread_index(user_1, user_2);
    if (thread_index > 10)
        return send_boolean_response(client.socket, false);
    response.len = sizeof(messages_response_t);
    response.code = MESSAGES_RESPONSE;
    response.messages.thread = server->save.private_messages[thread_index];
    send_boolean_response(client.socket, true);
    write(client.socket, &response, sizeof(messages_response_t));
}
