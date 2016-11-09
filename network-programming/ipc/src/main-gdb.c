#include "shm.h"
#include "semaphore.h"
#include <time.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <sys/types.h>

#define SIZE 0x10000
#define true 1

static pid_t child[3];
static int sem_w, sem_d, sem_r, shm_w, shm_r;
static int shmid;
static void *shmaddr;

void kill_handler(int sig);

int main(void){
    int fd[4];
    struct shmem *shm;

    sem_w = init_sem(ftok(".", 1), 1, 1);
    sem_d = init_sem(ftok(".", 2), 0, 1);
    sem_r = init_sem(ftok(".", 3), 0, 1);
    shm_w = init_sem(ftok(".", 4), 1, 1);
    shm_r = init_sem(ftok(".", 5), 0, 1);


    if(pipe(fd) == -1 || pipe(fd+2) == -1){
        perror("pipe()");
        return -1;
    }

    shmid = init_shm(ftok(".", 6), SIZE);
    shmaddr = at_shm(shmid, SIZE, 1);
    shm = shmaddr;

    child[0] = fork();
    if(child[0] == -1){
        dt_shm(shmaddr);
        des_shm(shmid);
        perror("fork()");
        return -1;
    }
    else if(child[0] == 0){
        char buffer[LINE_MAX];
        int ch;

        FILE * stream = fopen("auth.log", "r");
        if(stream == NULL){
            perror("fopen()");
            return -1;
        }

        while(fgets(buffer, LINE_MAX, stream) != NULL){
            P(sem_w);
            puts("test point 1");

            write(fd[1], buffer, strlen(buffer));
            puts("Send.");
            
            V(sem_d);
            puts("test point 2");
            P(shm_r);
            puts("test point 9");

            while((ch = delete_queue(shm)) != -1){
                write(STDOUT_FILENO, &ch, 1);
                usleep(100);
            }

            V(shm_w);
            puts("test point 10");
        }
        puts("Send all.");
        fclose(stream);

        return 0; 
    }

    child[1] = fork();
    if(child[0] == -1){
        dt_shm(shmaddr);
        des_shm(shmid);
        perror("fork()");
        return -1;
    }
    else if(child[1] == 0){
        char buffer[BUFSIZ];
        ssize_t ret, len;

        while(true){
            P(sem_r);
            puts("test point 5");
         
            ret = read(fd[2], buffer, BUFSIZ);
            if(ret == -1 && errno != EINTR){
                perror("read");
                break;
            }
            //write(STDOUT_FILENO, buffer, ret);
            puts("Receive.");

            P(shm_w);
            puts("test point 6");
            for(len = 0; len <= ret; len++){
                if(add_queue(shm, buffer[len])){
                    sleep(1);
                }
            }
            V(shm_r);
            puts("test point 7");

            bzero(buffer, BUFSIZ);

            V(sem_w);
            puts("test point 8");
        }

        return 0;
    }

    signal(SIGINT, kill_handler);

    char buffer[BUFSIZ];
    ssize_t ret;

    while(true){
        P(sem_d);
        puts("test point 3");
        
        ret = read(fd[0], buffer, BUFSIZ);
        if(ret == -1 && errno != EINTR){
            perror("read");
            break;
        }
        write(fd[3], buffer, ret);
        puts("Delivery.");
        bzero(buffer, BUFSIZ);

        V(sem_r);
        puts("test point 4");
    }

    return 0;
}

void kill_handler(int sig){
    if(sig == SIGINT){
        kill(child[0], SIGINT);
        kill(child[1], SIGINT);
       
        int status[2];
        wait(status);
        wait(status+1);

        des_sem(sem_w);
        des_sem(sem_d);
        des_sem(sem_r);
        des_sem(shm_w);
        des_sem(shm_r);
        dt_shm(shmaddr);
        des_shm(shmid);

        puts("Exit sucessfully.");
        exit(0);
    }
}
