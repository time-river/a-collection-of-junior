#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/uio.h>
#include <unistd.h>

int main(void){
    char foo[48] = {0}, bar[51] = {0}, baz[49] = {0};
    struct iovec iov[3];
    ssize_t nr;
    int fd, i;

    fd = open("buccaneer.txt", O_RDONLY);
    if(fd == -1){
        perror("open");
        return 1;
    }

    iov[0].iov_base = foo;
    iov[0].iov_len = sizeof(foo);
    iov[1].iov_base = bar;
    iov[1].iov_len = sizeof(bar);
    iov[2].iov_base = baz;
    iov[2].iov_len = sizeof(baz);

    nr = readv(fd, iov, 3);
    if(nr == -1){
        perror("readv");
        return 1;
    }

    for(i=0; i<3;i++){
        write(STDOUT_FILENO, iov[i].iov_base, iov[i].iov_len);
    }

    if(close(fd)){
        perror("close");
        return 1;
    }

    return 0;
}
