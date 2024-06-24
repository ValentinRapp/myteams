#include <stdbool.h>
#include <arpa/inet.h>

bool is_valid_ip(char *ip)
{
    struct sockaddr_in sa;

    return inet_pton(AF_INET, ip, &(sa.sin_addr)) == 1;
}
