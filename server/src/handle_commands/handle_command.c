#include "../../include/my.h"
#include "../../include/utils.h"

bool handle_command(char *command, client_t *client, server_data_t *server)
{
    parsing_t command_struct;

    memcpy(&command_struct, command, sizeof(parsing_t));
    if (command_struct.op_code == QUIT)
        close_session(client, server);
    if (command_struct.op_code == LOGIN)
        login(command, client, server);
    if (command_struct.op_code == LOGOUT)
        logout(client, server);
    if (command_struct.op_code == USERS_REQUEST)
        users(client, server);
    if (command_struct.op_code == USER_REQUEST)
        user(command, client, server);
    if (command_struct.op_code == SEND)
        send_command(command, *client, server);
    if (command_struct.op_code == MESSAGES_REQUEST)
        messages(command, *client, server);
    return true;
}
