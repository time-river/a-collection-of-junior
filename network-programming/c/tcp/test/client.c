#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <errno.h>
#include <signal.h>

void handler(int sig){
    if(sig == RELEASE){
        kill(getpid(), SIGINT);
    }
}

int main(void){
    int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    struct sockaddr_in serv_addr;

    memset(&serv_addr, 0, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(1234);


    char buffer[40];
    int count;
    while(1){
    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    printf("errno: %d\n", errno);
    perror("read");
    count = read(sock, buffer, sizeof(buffer)-1);
    perror("read");
    printf("Message from server: %s\n", buffer);
    sleep(2);
    }
    close(sock);

    return 0;
}
