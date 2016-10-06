#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(void){
    int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//  int socket(int domain, int type, int protocol);
//  <bits/socket.h> <bits/socket_type.h> <netinet/in.h>

    struct sockaddr_in serv_addr;
//  <netinet/in.h>
//  struct sockaddr_in
//    {
//      __SOCKADDR_COMMON (sin_);
//      in_port_t sin_port;         /* Port number.  */
//      struct in_addr sin_addr;        /* Internet address.  */
//
//      /* Pad to size of `struct sockaddr'.  */
//      unsigned char sin_zero[sizeof (struct sockaddr) -
//                 __SOCKADDR_COMMON_SIZE -
//                 sizeof (in_port_t) -
//                 sizeof (struct in_addr)];
//    }; (16 + 16 + 32 + ...) = 128 bits
//
//  <bits/socket.h>
//  /* Structure describing a generic socket address.  */
//  struct sockaddr
//    {
//       __SOCKADDR_COMMON (sa_);    /* Common data: address family and length.  */
//       char sa_data[14];       /* Address data.  */
//    }; 
//  <sys/socket.h>
//  /* This is the 4.3 BSD `struct sockaddr' format, which is used as wire
//     format in the grotty old 4.3 `talk' protocol.  */
//  struct osockaddr
//    {
//      unsigned short int sa_family;
//      unsigned char sa_data[14];
//    };  (16 + 8*14) = 128 bits
//
//  <bits/sockaddr.h>
//  #define __SOCKADDR_COMMON_SIZE  (sizeof (unsigned short int))
//  http://blog.csdn.net/zhangboyj/article/details/6158215

    memset(&serv_addr, 0, sizeof(serv_addr));
//  void *memset(void *s, int c, size_t n);
//  把 sin_zero 部分填充为 0
//  http://www.gta.ufrj.br/ensino/eel878/sockets/sockaddr_inman.html

    serv_addr.sin_family = AF_INET;
//  <bits/sockaddr.h>
//  unsigned short int : 0 - 65535
//  typedef unsigned short int sa_family_t;
//  #define __SOCKADDR_COMMON(sa_prefix) sa_family_t sa_prefix##family
//  http://stackoverflow.com/questions/3829435/query-regarding-syntax-used-in-a-header-file-for-socket-programming

    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
//  typedef unsigned int        uint32_t;
//  typedef uint32_t in_addr_t;
//  in_addr_t inet_addr(const char *cp);
//  struct in_addr
//    {
//        in_addr_t s_addr;
//    };

    serv_addr.sin_port = htons(1234);
//  typedef uint16_t in_port_t;
//  uint16_t htons(uint16_t hostshort);
//      host byte order --> network byte order

    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
//  int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
//  typedef __socklen_t socklen_t;

    char buffer[40];
    read(sock, buffer, sizeof(buffer)-1);
//  ssize_t read(int fd, void *buf, size_t count);
//  typedef __ssize_t ssize_t;
//
    printf("Message from server: %s\n", buffer);

    close(sock);

    return 0;
}
