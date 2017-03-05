#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define true 1

int main(void){
    int sock;
    int client_len;
    int recv_num;
    char recv_buf[20] = {0};
    struct sockaddr_in addr_serv;
    struct sockaddr_in addr_client;
    
    sock = socket(AF_INET, SOCK_DGRAM, 17);
    if (sock < 0){
        perror("socket fd error\n");
        exit(-1);
    }
    else {
        printf("socket sucessful.\n");
    }

    memset(&addr_serv, 0, sizeof(struct sockaddr_in));
    addr_serv.sin_family = AF_INET;
    addr_serv.sin_port = htons(3000);
    addr_serv.sin_addr.s_addr = htonl(INADDR_ANY);

    client_len = sizeof(struct sockaddr_in);
    if (bind(sock, (struct sockaddr *)&addr_serv, sizeof(struct sockaddr_in)) < 0){
        perror("bind error\n");
        exit(-1);
    }
    else {
        printf("bind sucessful\n");
    }

    while(true) {
        puts("begin receive:\n");
        recv_num = recvfrom(sock, recv_buf, sizeof(recv_buf), 0, (struct sockaddr *)&addr_client, &client_len);
        if (recv_num < 0){
            perror("sendto\n");
            exit(1);
        }
        else {
            printf("send sucessful\n");
            puts(recv_buf);
        }
        memset(&recv_buf, 0, sizeof(recv_buf));
    }
    close(sock);
    return 0;
}
