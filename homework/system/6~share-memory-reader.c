#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/types.h>

#define PACE_SIZE 0x00400000
#define FLAG "begin"
#define FLAGSIZE 8

typedef struct {
    char flag[8];
    int  readernum;
    char text[PACE_SIZE-sizeof(char)*8-sizeof(int)];
} share;

union semun {
    int             val;
    struct semid_ds *buf;
    unsigned short  *array;
    struct seminfo  *__buf;
};

int sem_init(key_t key, int value);
int sem_destroy(int semid);
int P(int semid);
int V(int semid);

int main(void){
    int writer, mutex, share_id;
    void *share_p;

    writer = sem_init(ftok(".", 1), 1);
    mutex = sem_init(ftok(".", 2), 1);

    // 共享内存--记录文件
    share_id = shmget(ftok("share", 1), PACE_SIZE, IPC_CREAT | 0666);
    if(share_id < 0){
        perror("shmget()");
        exit(-1);
    }
    share_p = shmat(share_id, NULL, 0);
    if(share_p == (void *)-1){
        perror("shmat()");
        exit(-1);
    }
    share* file = (share *)share_p;

    int readnum;

    P(mutex);
    if(strcmp(file->flag, FLAG)){
        bzero(file, PACE_SIZE);
        strcpy(file->flag, FLAG);
        readnum = 0;
    }
    else
        readnum = file->readernum;
    file->readernum = ++readnum;
    if(readnum == 1)
        P(writer);
    V(mutex);

    // read file
    char *cur = file->text;
    while(*cur != '\0'){
        putchar(*cur);
        cur += sizeof(char);
    }
    //end

    P(mutex);
    readnum = --(file->readernum);
    if(readnum == 0)
        V(writer);
    V(mutex);

    if(shmdt(share_p) == -1)
        perror("shmdt share_p");

    puts("destroy?");
    int ch;
    scanf("%d", &ch);
    if(ch == 1){
        sem_destroy(mutex);
        sem_destroy(writer);
        shmctl(share_id, IPC_RMID, NULL);
        sleep(1);
    }

    return 0;
}

int sem_init(key_t key, int value){
    int semid = semget(key, 1, IPC_EXCL | IPC_CREAT | 0666);
    if(semid < 0){
        semid = semget(key, 1, IPC_CREAT | 0666);
        if(semid < 0){
            perror("Semget()");
            return -1;
        }
        return semid;
    }

    if(semctl(semid, 0, SETVAL, value) < 0){
        perror("Semctl()");
        return -1;
    }

    return semid;
}

int sem_destroy(int semid){
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
    }
}
