#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

void *modify(void *string){
    printf("Original string:\n    %s\n", (char *)string);
    bzero(string, sizeof(string));
   
    strcpy(string, "Hello, process!"); 
    return;
}

int main(void){
    static char string[20] = "Hello thread!";
    pthread_t thread;

    if (pthread_create(&thread, NULL, modify, string)){
        puts("create thread error!");
        exit(-1);
    }

    if (pthread_join(thread, NULL)){
        puts("join error!");
        exit(-2);
    }
        
    printf("Now string:\n    %s\n", string); 
    return 0;
}
