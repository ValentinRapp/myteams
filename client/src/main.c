#include "../include/client_lib.h"
#include "../include/my.h"
#include <signal.h>

int help(int exit_code)
{
    printf("USAGE: ./myteams_cli ip port\n");
    printf("\tip\tis the server ip address on which");
    printf(" the server socket listens\n");
    printf("\tport\tis the port number on which the server socket listens\n");
    return exit_code;
}

void error_handling(int ac, char *av[])
{
    if (ac < 2) {
        exit(help(84));
    }
    if (strcmp("-help", av[1]) == 0) {
        exit(help(0));
    }
    if (!is_valid_ip(av[1])) {
        error("Invalid IP");
    }
    if (!is_number(av[2])) {
        error("Invalid port");
    }
}

void sigint_handler(int sig_num)
{
    signal(SIGINT, SIG_DFL);
    (void)sig_num;
    printf("exit\n");
    _exit(0);
}

int main(int ac, char **av)
{
    char *ip;
    int port;
    SOCK socket;

    error_handling(ac, av);
    signal(SIGINT, sigint_handler);
    ip = av[1];
    port = atoi(av[2]);
    socket = init_server_connection(ip, port);
    handle_server_connection(socket);
    return 0;
}
