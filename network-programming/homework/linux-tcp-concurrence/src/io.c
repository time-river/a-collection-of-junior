#include "io.h"
#include <fcntl.h>
#include <netdb.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <sys/socket.h>

int create_and_bind_nonblock_sock(char *port){
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    int s, sfd;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_flags = AI_PASSIVE;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    s = getaddrinfo(NULL, port, &hints, &result);
    assert(s == 0);

    for(rp=result; rp != NULL; rp=rp->ai_next){
        sfd = socket(rp->ai_family, rp->ai_socktype | SOCK_NONBLOCK, rp->ai_protocol);
        if(sfd == -1)
            continue;

        s = bind(sfd, rp->ai_addr, rp->ai_addrlen);
        if(s == 0)
            break;

        close(sfd);
    }

    assert(rp != NULL);

    freeaddrinfo(result);

    return sfd;
}

int get_client_fd(int sfd){
    struct sockaddr in_addr;
    socklen_t in_len = sizeof(in_addr);
    char hbuf[NI_MAXHOST], sbuf[NI_MAXSERV];
    int infd;

    infd = accept(sfd, &in_addr, &in_len);
    if(infd == -1){
        if((errno != EAGAIN) &&
                (errno != EWOULDBLOCK)){
            perror("accept");
        }
        return -1;
    }

    /* debug */
    int s;
    extern int user;
    s= getnameinfo(&in_addr, in_len, hbuf, sizeof(hbuf), sbuf, sizeof(sbuf), NI_NUMERICHOST | NI_NUMERICSERV);
    if(s == 0)
        printf("Accepted %d connection on descriptor %d"
                "(host=%s, port=%s)\n", ++user, infd, hbuf, sbuf);
    /* end */

    return infd;
}

int set_nonblocking_fd(int sfd){
    int flags, s;

    flags = fcntl(sfd, F_GETFL);
    assert(flags != -1);

    flags |= O_NONBLOCK;
    s = fcntl(sfd, F_SETFL, flags);
    assert(s == 0);

    return 0;
}

void tcp_reuse(int sfd){
    int optval = 1;

    if(setsockopt(sfd, SOL_SOCKET, (SO_REUSEPORT | SO_REUSEADDR), &optval, sizeof(optval)) < 0){
            perror("tcp reuse failed.");
            return;
    }
    return;
}
