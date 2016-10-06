#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define true  1
#define false 0

int main(void){
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(struct sockaddr_in));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(1234);

    char buff_send[100] = {0};
    char buff_recv[100] = {0};

    int flag = true;
    while(flag){
        int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
        printf("Input a string: ");
        scanf("%s", buff_send);
        send(sock, buff_send, strlen(buff_send), 0);
        recv(sock, buff_recv, 100, 0);
        printf("Message from server: %s\n", buff_recv);
        if(strcmp("bye", buff_recv) == 0)
            break;
        memset(buff_send, 0, 100);
        memset(buff_recv, 0, 100);
        close(sock);
    }

    return 0;
}
