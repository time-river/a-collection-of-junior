#include "io.h"
#include <unistd.h>
#include <sys/epoll.h>
#include <sys/socket.h>

int add_fd(int epollfd, int fd){
    int s;

    struct epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN | EPOLLET | EPOLLRDHUP;
    s = epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
    if(s != 0)
        return -1;

    s = set_nonblocking_fd(epollfd);
    if(s != 0)
        return -1;
    return 0;
}

void remove_fd(int epollfd, int fd){
    epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, 0);
    close(fd);
}
