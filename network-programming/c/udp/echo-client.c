#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define true  1
#define false 0

int main(void){
    int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(1234);

    struct sockaddr_in src_addr;
    socklen_t src_addr_size = sizeof(src_addr);
    int flag = true;
    while(flag){
        char buffer[100] = {0};
        printf("Input a string: ");
        scanf("%s", buffer);
        sendto(sock, buffer, strlen(buffer), 0, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
        int str_len = recvfrom(sock, buffer, 100, 0, (struct sockaddr *)&src_addr, &src_addr_size);
        buffer[str_len] = '\0';
        printf("Message from server: %s\n", buffer);

        if(strcmp(buffer, "bye") == 0)
            flag = false;
    }

    close(sock);

    return 0;
}
