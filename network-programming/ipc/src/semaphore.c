#include "semaphore.h"
#include <stdio.h>
#include <sys/sem.h>
#include <sys/ipc.h>

int init_sem(key_t key, int value, int flag){
    if(key == -1){
        perror("init_sem key");
        return -1;
    }
    int semid = semget(key, 1 , IPC_CREAT | IPC_EXCL | 0666);
    if (semid == -1){
        semid = semget(key, 1, IPC_CREAT | 0666);
        if(semid == -1){
            perror("semget()");
            return semid;
        }
    }
    if(flag){
        if(semctl(semid, 0, SETVAL, value) == -1){
            perror("semctl()");
            des_sem(semid);
            semid = -1;
        }
    }
    return semid;
}

int P(int semid){
    struct sembuf sops = {
        .sem_num = 0,
        .sem_op = -1,
        .sem_flg = SEM_UNDO
    };

    if(semop(semid, &sops, 1) == -1){
        perror("semaphore P operation");
        return -1;
    }
    return 0;
}
int V(int semid){
    struct sembuf sops = {
        .sem_num = 0,
        .sem_op = 1,
        .sem_flg = SEM_UNDO
    };

    if(semop(semid, &sops, 1) == -1){
        perror("semaphore V operation");
        return -1;
    }
    return 0;
}

int des_sem(int semid){
    if(semctl(semid, 0, IPC_RMID) == -1){
        perror("des_sem()");
        return -1;
    }
}
