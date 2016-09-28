#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
    int sock_fd;
    int send_num;
    int dst_len;
    char *dst = argv[1];
    int port = atoi(argv[2]);
    char *send_buf = argv[3];
    char recv_buf[20];
    struct sockaddr_in addr_serv;

    sock_fd = socket(AF_INET, SOCK_DGRAM, 17);
    memset(&addr_serv, 0, sizeof(addr_serv));
    addr_serv.sin_family = AF_INET;
    addr_serv.sin_addr.s_addr = inet_addr(dst);
    addr_serv.sin_port = htons(port);

    dst_len = sizeof(struct sockaddr_in);
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
