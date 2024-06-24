#include "../include/my.h"

void send_boolean_response(SOCK socket, bool to_send)
{
    write(socket, &to_send, sizeof(bool));
}
