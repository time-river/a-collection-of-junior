#include <sys/types.h>

union semun{
    int             val;
    struct semid_ds *buf;
    unsigned short  *array;
    struct seminfo  *__buf;
};

int init_sem(key_t key, int value, int flag);
int P(int semid);
int V(int semid);
int des_sem(int semid);
