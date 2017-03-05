#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <sys/types.h>

// XSI（System Interface and Headers 信号量

#define true 1

static pid_t producer, customer;
static int semid[2];

union semun {
    int             val;
    struct semid_ds *buf;
    unsigned short  *array;
    struct seminfo  *__buf;
};

int  sem_init(int proj_id, int value);
void sem_destroy(int semid);
int  P(int semid);
int  V(int semid);
void signal_handler(int signum);

int main(void){
    semid[0] = sem_init(0, 1);
    semid[1] = sem_init(1, 0);

    producer = fork();
    customer = fork();
    if(producer == -1){
        perror("producer");
        return -1;
    }
    if(customer == -1){
        perror("customer");
        return -1;
    }

    if(producer == 0){
        while(true){
            P(semid[0]);
            puts("  Sleep 1s, then production");
            sleep(1);
            puts("Produce...");
            V(semid[1]);
        }
    }

    if(customer == 0){
        while(true){
            P(semid[1]);
            puts("Custom...");
            puts("  Sleep 1s, then V");
            sleep(1);
            V(semid[0]);
        }
    }

    signal(SIGINT, signal_handler);
    int producer_status, customer_status;
    wait(&producer_status);
    wait(&customer_status);

    return 0;
}

int sem_init(int proj_id, int value){

    int semid = semget(ftok(".", proj_id), 1, IPC_CREAT | 0600);
    if(semid < 0){
        perror("Semget()");
        return -1;
    }

    if(semctl(semid, 0, SETVAL, value) < 0){
        perror("Semctl()");
        return -1;
    }

    return semid;
}

void sem_destroy(int semid){
    semctl(semid, 0, IPC_RMID);
}

int P(int semid){
    struct sembuf sops;

    sops.sem_num = 0;
    sops.sem_op = -1;
    sops.sem_flg = SEM_UNDO;

    if(semop(semid, &sops, 1) == -1){
        perror("Semaphore P operation");
        return -1;
    }
    return 0;
}

int V(int semid){
    struct sembuf sops;
    
    sops.sem_num = 0;
    sops.sem_op = 1;
    sops.sem_flg = SEM_UNDO;

    if(semop(semid, &sops, 1) == -1){
        perror("Semaphore V operation");
        return -1;
    }
    return 0;
}

void signal_handler(int signum){
    if(signum == SIGINT){
        kill(producer, SIGINT);
        kill(customer, SIGINT);
        sem_destroy(semid[0]);
        sem_destroy(semid[1]);
    }
}
