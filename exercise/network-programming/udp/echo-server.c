#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define true  1

int main(void){
    int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(1234);
    bind(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size = sizeof(clnt_addr);
    
    char buffer[100];
    while(true){
        int str_len = recvfrom(sock, buffer, 100, 0, (struct sockaddr *)&clnt_addr, &clnt_addr_size);
//  ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags,
//                        struct sockaddr *src_addr, socklen_t *addrlen);

        sendto(sock, buffer, str_len, 0, (struct sockaddr *)&clnt_addr, clnt_addr_size);
//  ssize_t sendto(int sockfd, const void *buf, size_t len, int flags,
//                        const struct sockaddr *dest_addr, socklen_t addrlen);                        
    }

    close(sock);

    return 0;
}
