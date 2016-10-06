#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(void){
    int serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(1234);
    bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
//  int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
    listen(serv_sock, 20);
//  int listen(int sockfd, int backlog);

    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size = sizeof(struct sockaddr_in);
    int clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size);
//  int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

    char str[] = "Hello World!\n";
    write(clnt_sock, str, sizeof(str));
//  ssize_t write(int fd, const void *buf, size_t count);

    close(clnt_sock);
    close(serv_sock);

    return 0;
}
