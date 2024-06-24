#include "../../include/my.h"
#include "../../include/utils.h"
#include "../../include/revolution.h"
#include "../../include/client_lib.h"

void logout(SOCK socket, context_t *context)
{
    if (context->is_logged_in == false)
        return;
    client_event_logged_out(context->user_UUID, context->username);
    write(socket, &(logout_t){sizeof(logout_t), LOGOUT}, sizeof(logout_t));
    memset(context->user_UUID, 0, 37);
    memset(context->username, 0, MAX_NAME_LENGTH);
    context->is_logged_in = false;
}

void login(char *buffer, SOCK socket, context_t *context)
{
    if (!is_valid_nb_quotes(buffer, 1))
        return;
    remove_all_chars(buffer, '\"');
    if (context->is_logged_in)
        logout(socket, context);
    strtok(buffer, " ");
    NEW(char *, username);
    username = strtok(NULL, "");
    NEW(login_t, login_info) = {sizeof(login_t), LOGIN, ""};
    memcpy(login_info.username, username, strlen(username));
    write(socket, &login_info, sizeof(login_t));
    read(socket, context->user_UUID, 37);
    strcpy(context->username, username);
    client_event_logged_in(context->user_UUID, username);
    context->is_logged_in = true;
}

void handle_command(char *buffer, SOCK socket, context_t *context)
{
    if (strncmp(buffer, "QUIT", 4) == 0) {
        write(socket, &(quit_t){sizeof(quit_t), QUIT}, sizeof(quit_t));
        exit(0);
    }
    if (strncmp(buffer, "/help", 5) == 0)
        help(true);
    if (strncmp(buffer, "/login ", 7) == 0)
        login(buffer, socket, context);
    if (!context->is_logged_in)
        return (void)client_error_unauthorized();
    if (strncmp(buffer, "/logout", 7) == 0)
        logout(socket, context);
    if (strncmp(buffer, "/users", 6) == 0)
        users(socket, *context);
    if (strncmp(buffer, "/user ", 6) == 0)
        user(buffer, socket);
    if (strncmp(buffer, "/send ", 6) == 0)
        send_command(buffer, socket, *context);
    if (strncmp(buffer, "/messages ", 10) == 0)
        messages(buffer, socket, *context);
}
