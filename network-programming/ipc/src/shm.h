#include <sys/types.h>

struct shmem {
    char *queue;
    unsigned long long front;
    unsigned long long rear;
    unsigned long long size;
} __attribute__((packed));

int  init_shm(key_t key, size_t size);
struct shmem *at_shm(int shmid, size_t size, int flag);
int  dt_shm(const void *shmaddr);
int  des_shm(int shmid);
int  add_queue(struct shmem *addr, char x);
int  delete_queue(struct shmem *addr);
