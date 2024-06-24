#include "../../include/my.h"
#include "../../include/utils.h"
#include "../../include/revolution.h"

int get_thread_index(int user_1, int user_2)
{
    int n = 5;
    int temp;

    if (user_1 >= user_2) {
        temp = user_1;
        user_1 = user_2;
        user_2 = temp;
    }
    return (user_1 * (2 * n - user_1 - 1)) / 2 + user_2 - user_1 - 1;
}

int get_new_message_index(thread_t thread)
{
    int i = 0;

    while (i < 100) {
        if (thread.messages[i].message_body[0] == 0)
            return i;
        i++;
    }
    return -1;
}

void register_message(server_data_t *server, int thread_index,
    int message_index, send_t request)
{
    server->save.private_messages[thread_index].messages[message_index].
    message_timestamp = time(NULL);
    memcpy(server->save.private_messages[thread_index].messages[message_index].
    message_body, request.message_body, MAX_BODY_LENGTH);
    memcpy(server->save.private_messages[thread_index].messages[message_index].
    sender_uuid, request.sender_uuid, sizeof(char) * 37);
}

void send_to_user(server_data_t server, send_t request, int user_index)
{
    message_sent_t response = {sizeof(message_sent_t), MESSAGE_SENT, {0}, {0}};

    memcpy(response.uuid, request.receiver_uuid, sizeof(char) * 37);
    memcpy(response.message, request.message_body, sizeof(char) *
    MAX_BODY_LENGTH);
    printf("%s\n", response.message);
    for (int i = 0; i < 100; i++) {
        if (strcmp(server.save.usernames[user_index], server.clients[i].name)
        == 0) {
            write(server.clients[i].socket, &response, sizeof(message_sent_t));
        }
    }
}

void send_command(char *command, client_t client, server_data_t *server)
{
    NEW(send_t, request);
    NEW(int, thread_index) OTH_VAR(user_1) OTH_VAR(user_2)
    OTH_VAR(message_index);
    memcpy(&request, command, sizeof(send_t));
    user_1 = get_uuid_index(request.sender_uuid, server->save.usernames_UUID);
    user_2 = get_uuid_index(request.receiver_uuid,
    server->save.usernames_UUID);
    if (user_1 == -1 || user_2 == -1)
        return send_boolean_response(client.socket, false);
    thread_index = get_thread_index(user_1, user_2);
    if (thread_index > 10)
        return send_boolean_response(client.socket, false);
    message_index = get_new_message_index(server->save.
    private_messages[thread_index]);
    if (message_index == -1)
        return send_boolean_response(client.socket, false);
    register_message(server, thread_index, message_index, request);
    send_boolean_response(client.socket, true);
    send_to_user(*server, request, user_2);
}
