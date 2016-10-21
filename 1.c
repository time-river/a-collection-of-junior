#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(void){
    int status;

    pid_t pid = fork();

    if (pid < 0){
        puts("fork error.");
        exit(-1);
    }
    else if(pid == 0){
        printf("child pid: %d\n", getpid());
        FILE *fp = fopen("Makefile", "r");
        int buf;
        while((buf = fgetc(fp)) != EOF){
            putchar(buf);
        }

        puts("child process is end.");
        exit(0);
    }
    else {
        printf("parent pid: %d\n", getpid());
        puts("parent process is waitting.");

        wait(&status);
        puts("child process has been end.");
    }
    return 0;
}
