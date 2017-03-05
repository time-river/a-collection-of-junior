#include <stdio.h>
#include <netdb.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

int main(void){
    struct hostent * host = gethostbyname("vvl.me");
//  <netdb.h>
//  struct hostent *gethostbyname(const char *name);
//  /* Description of data base entry for a single host.  */
//  struct hostent
//  {
//    char *h_name;         /* Official name of host.  */
//    char **h_aliases;     /* Alias list.  */
//    int h_addrtype;       /* Host address type.  */
//    int h_length;         /* Length of address.  */
//    char **h_addr_list;       /* List of addresses from name server.  */
//  #ifdef __USE_MISC
//  # define    h_addr  h_addr_list[0] /* Address, for backward compatibility.*/
//  #endif
//  };


    if(!host){
        puts("Get IP address error!");
        exit(0);
    }

    for(int i=0; host->h_aliases[i]; i++)
        printf("Aliases %d: %s\n", i+1, host->h_aliases[i]);

    printf("Address type: %s\n", (host->h_addrtype==AF_INET) ? "AF_INET" : "AF_INET6");

    for(int i=0; host->h_addr_list[i]; i++)
        printf("IP addr %d: %s\n", i+1, inet_ntoa(*(struct in_addr *)host->h_addr_list[i]));
    return 0;
}
