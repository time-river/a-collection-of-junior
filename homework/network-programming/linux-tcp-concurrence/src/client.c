#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/wait.h>

#define CLIENT 1000

uint16_t get_port(char *string);

int main(int argc, char *argv[]){
    pid_t pid[10];
    int s;

    if(argc != 3){
        fprintf(stderr, "Usage: %s [address] [port].\n", argv[0]);
            exit(EXIT_FAILURE);
    }

    for(int i=0; i < CLIENT; i++){
        pid[i] = fork();
        if(pid[i] < 0)
            perror("fork");
        else if(pid[i] == 0){
            int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

            struct sockaddr_in serv_addr;
            memset(&serv_addr, 0, sizeof(serv_addr));

            serv_addr.sin_family = AF_INET;
            serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
            serv_addr.sin_port = htons(get_port(argv[2]));

            s = connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
            if(s == -1)
                perror("connect");
            char buffer[BUFSIZ];
            sprintf(buffer, "Message from client: %d\n", getpid());
            send(sock, buffer, strlen(buffer), 0);
            ssize_t count;
            count = recv(sock, buffer, sizeof(buffer), 0);
            write(STDOUT_FILENO, buffer, count);

            sleep(i);

            close(sock);
            printf("pid %d exit\n", getpid());
            exit(0);
        }
        else{
            continue;
        }
    }

    for(int i=0; i < CLIENT; i++){
        int status;
        waitpid(pid[i], &status, WUNTRACED | WCONTINUED);
    }

    return 0;
}

uint16_t get_port(char *string){
    uint16_t port = 0;
    
    for(int i=0; string[i] != '\0'; i++)
        port = port * 10 + string[i] - '0';

    return port;
}
