#include "shm.h"
#include <stdio.h>
#include <sys/shm.h>
#include <sys/ipc.h>

int  init_shm(key_t key, size_t size){
    int shmid;

    shmid = shmget(key, size, IPC_CREAT | 0666);
    if(shmid == -1)
        perror("shmget()");
    return shmid;
}

struct shmem *at_shm(int shmid, size_t size, int flag){
    void *shmaddr;
    struct shmem *addr;

    shmaddr = shmat(shmid, NULL, 0);
    if(shmaddr == (void *)-1){
        shmctl(shmid, IPC_RMID, NULL);
        perror("shmat()");
    }
    if(flag){
        addr = (struct shmem*)shmaddr;
        addr->size = size - sizeof(unsigned long long) * 3 - sizeof(char *);
        addr->queue = (char *)shmaddr + sizeof(char *) + sizeof(unsigned long long) * 3;
        addr->front = addr->rear = 0;
    }
    return addr;
}

int  dt_shm(const void *shmaddr){
    int ret;

    ret = shmdt(shmaddr);
    if(ret == -1)
        perror("shmdt()");
    return ret;
}

int  des_shm(int shmid){
    int ret;

    ret = shmctl(shmid, IPC_RMID, NULL) == -1;
    if(ret == -1)
        perror("shmctl()");
    return ret;
}

int add_queue(struct shmem *addr, char x){
    if(((addr->rear+1)%addr->size) == addr->front){
        return -1;
    }
    addr->queue[addr->rear] = x;
    addr->rear = (addr->rear + 1) % addr->size;
    return 0;
}

int delete_queue(struct shmem *addr){
    char ch;

    if(addr->front == addr->rear){
        return -1;
    }
    ch = addr->queue[addr->front];
    addr->front = (addr->front + 1) % addr->size;
    return ch;
}
