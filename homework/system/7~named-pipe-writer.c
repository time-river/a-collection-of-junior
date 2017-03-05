#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(void){
    char buf[BUFSIZ];
    int fd;
    mkfifo("fifo", 0666);
   
    fd = open("fifo", O_WRONLY);
    dprintf(fd, "Message from pid %d: Hello!\n", getpid());
    close(fd);

    fd = open("fifo", O_RDONLY);
    read(fd, buf, BUFSIZ);
    write(STDOUT_FILENO, buf, strlen(buf));
    close(fd);

    unlink("fifo");

    return 0;
}
