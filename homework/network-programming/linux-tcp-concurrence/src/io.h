#include <stdio.h>

int create_and_bind_nonblock_sock(char *port);
int get_client_fd(int sfd);
void tcp_reuse(int sfd);
int set_nonblocking_fd(int sfd);
