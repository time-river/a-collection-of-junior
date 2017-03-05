#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

#define STRING "hello"

int main(void){
    int pipefd[2];
    pid_t pid;
    char buf[BUFSIZ];

    if(pipe(pipefd) == -1){
        perror("pipe()");
        exit(-1);
    }

    pid = fork();
    if(-1 == pid){
        perror("fork()");
        exit(-1);
    }
    else if(pid == 0){
        printf("Child pid is: %d\n", getpid());
        if(read(pipefd[0], buf, BUFSIZ) < 0){
            perror("child read()");
            exit(-1);
        }
        write(STDOUT_FILENO, buf, strlen(buf));

        bzero(buf, BUFSIZ);
        snprintf(buf, BUFSIZ, "Message from child: My pid is: %d\n", getpid());
        if(write(pipefd[1], buf, strlen(buf)) < 0){
            perror("write()");
            exit(-1);
        }
    }
    else {
        printf("Parent pid is: %d\n", getpid());

        snprintf(buf, BUFSIZ, "Message from parent: My pid is %d\n", getpid());
        if(write(pipefd[1], buf, strlen(buf)) < 0){
            perror("write()");
            exit(-1);
        }

        int status;
        wait(&status);

        bzero(buf, BUFSIZ);
        if(read(pipefd[0], buf, BUFSIZ) < 0){
            perror("read()");
            exit(-1);
        }
        write(STDOUT_FILENO, buf, strlen(buf));
    }

    return 0;
}
