#include "io.h"
#include "event.h"
#include <netdb.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <sys/sysctl.h>
#include <sys/types.h>
#include <sys/epoll.h>

#define true 1
#define MAXEVENTS 64

int user = 0;

int main(int argc, char *argv[]){
    int sfd, s;
    int efd;
    struct epoll_event *events;
    
    if(argc != 2){
        fprintf(stderr, "Usage: %s [port].\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    sfd = create_and_bind_nonblock_sock(argv[1]);

    tcp_reuse(sfd);

    s = listen(sfd, SOMAXCONN);
    assert(s != -1);

    efd = epoll_create1(0);
    assert(efd != -1);

    s = add_fd(efd, sfd);
    assert(s != -1);

    events = calloc(MAXEVENTS, sizeof(struct epoll_event));
    assert(events != NULL);

    int i, n;
    while(true){
        n = epoll_wait(efd, events, MAXEVENTS, -1);
        for(i=0; i<n; i++){
            if((events[i].events & EPOLLERR) ||
                    (events[i].events & EPOLLHUP) ||
                    (!(events[i].events & EPOLLIN))){
                fprintf(stderr, "epoll error.\n");
                close(events[i].data.fd);
                continue;
            }
            else if(sfd == events[i].data.fd){
                /* We have a notification on the listening socket, which
                 * means one or more incoming connection.
                 */
                while(true){
                    int infd;

                    infd = get_client_fd(sfd);
                    if(infd == -1)
                        break;

                    s = set_nonblocking_fd(infd);
                    tcp_reuse(infd);
                    assert(s == 0);

                    s = add_fd(efd, infd);
                    assert(s == 0);
                }
                continue;
            } 
            else if(events[i].events & EPOLLRDHUP){
                // client close socket
                remove_fd(efd, events[i].data.fd);
                user--;
                printf("Left %d users\n", user);
            }
            else if(events[i].events & EPOLLIN){
                /* We have data on the fd waiting to be read. Read and
                 * display it. Then replay client.
                 */
                ssize_t count;
                char buffer[BUFSIZ];

                while(true){
                    count = recv(events[i].data.fd, buffer, sizeof(buffer), 0);
                    if(count == -1){
                        if(errno != EAGAIN){
                            perror("read");
                        }
                        break;
                    }
                    else if(count == 0){
                        break;
                    }

                    s = write(STDOUT_FILENO, buffer, count);
                    if(s == -1)
                        perror("output");
                }

                snprintf(buffer, sizeof(buffer), "Message fron server %d: Welcome, %d user\n", getpid(), user);
                s = send(events[i].data.fd, buffer, strlen(buffer), 0);
                if(s == -1)
                    perror("send");
            }
        }
    }
    return 0;    
}
