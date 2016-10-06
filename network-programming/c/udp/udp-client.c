#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char *argv[]) {
    int sock_fd;
    int send_num;
    int dst_len;
    char send_buf[20] = {0};
    char recv_buf[20] = {0};
    struct sockaddr_in addr_serv;

    sock_fd = socket(AF_INET, SOCK_DGRAM, 17);
    memset(&addr_serv, 0, sizeof(addr_serv));
    addr_serv.sin_family = AF_INET;
    addr_serv.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr_serv.sin_port = htons(3000);

    dst_len = sizeof(struct sockaddr_in);
    printf("input message: ");
    scanf("%s", send_buf);
    puts("begin send:\n");
    send_num = sendto(sock_fd, send_buf, sizeof(send_buf), 0, (struct sockaddr *)&addr_serv, dst_len);

    if(send_num < 0){
        perror("sendto\n");
        exit(-1);
    }
    else {
        printf("send sucessful: %s\n", send_buf);
    }
    
    close(sock_fd);
    return 0;
}
