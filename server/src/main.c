#include "../include/server_lib.h"
#include "../include/my.h"

int help(int exit_code)
{
    printf("USAGE: ./myteams_server port\n");
    printf("\n");
    printf("\tport\tis the port number on which the server socket listens\n");
    return exit_code;
}

void error_handling(int ac, char *av[])
{
    if (ac != 2) {
        exit(help(84));
    }
    if (strcmp("-help", av[1]) == 0) {
        exit(help(0));
    }
    if (!is_number(av[1])) {
        error("Invalid port");
    }
}

void sigint_handler(int sig_num)
{
    signal(SIGINT, SIG_DFL);
    (void)sig_num;
    printf("exit\n");
    run = false;
}

int main(int ac, char **av)
{
    int port;
    SOCK server_sock;

    error_handling(ac, av);
    signal(SIGINT, sigint_handler);
    port = atoi(av[1]);
    server_sock = init_server(port);
    handle_server(server_sock);
    return 0;
}
