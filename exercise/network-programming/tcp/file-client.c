#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(void){
    int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(1234);
    
    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    char buffer[100];
    int count;
    FILE *fp;
    fp = fopen("/tmp/file-server", "w");
    while((count = recv(sock, buffer, 100, 0)) > 0){
        fwrite(buffer, count, 1, fp);
    }
    puts("File transfer sucess!");

    fclose(fp);
    close(sock);

    return 0;
}
