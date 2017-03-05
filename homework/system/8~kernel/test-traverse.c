#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define TASK_COMM_LEN 16

struct info {
    pid_t pid;
    char comm[TASK_COMM_LEN];
};

int main(void){
    int number=100;
    struct info *tmp;

    int fd = open("/dev/traverse", O_RDWR);
//    write(fd, &number, sizeof(number));
    printf("number: %d\n", number);
    struct info p_info[1000];
    read(fd, p_info, sizeof(struct info)*1000);

// p_info[i].pid = -1 stands for end
    for(int i=0; p_info[i].pid != -1 && i < 1000; i++){
        printf("pid:%d comm: %s\n", p_info[i].pid, p_info[i].comm);
    printf("%d\n", i);
    }
    return 0;
}
