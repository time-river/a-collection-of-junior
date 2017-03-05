#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

/* http://blog.csdn.net/ljianhui/article/details/10128731 */

void signal_handler(int signum){
    if(signum == SIGALRM){
        printf("Hello, SIGALRM signal(%d).\n", SIGALRM);
    }
}

int main(void){

    pid_t pid = fork();
    if(pid < -1)
        perror("Fork error.\n");
    else if(pid == 0){
        printf("Child process: %d\n", getpid());
        printf("After 5 seconds, child process will send a ALARM signal(%d) to parent process.\n",  SIGALRM);
        sleep(5);
        kill(getppid(), SIGALRM);
        printf("Sent SIGALRM, child process is end.\n");
        exit(0);
    }
    else{
        printf("Parent process: %d\n", getpid());
        printf(" waitting a signal.\n");
        signal(SIGALRM, signal_handler);
        
        int status;
        wait(&status);
    }

    return 0;
}
