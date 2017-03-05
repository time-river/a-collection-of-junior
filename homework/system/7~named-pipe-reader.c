#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(void){
    char buf[BUFSIZ];
    int fd;
   
    fd = open("fifo", O_RDONLY);
    read(fd, buf, BUFSIZ);
    write(STDOUT_FILENO, buf, strlen(buf));
    close(fd);

    fd = open("fifo", O_WRONLY);
    dprintf(fd, "Reply from pid %d: Hello.\n", getpid());
    close(fd);

    return 0;
}
