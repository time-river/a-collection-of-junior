#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

void *modify(void *string){
    bzero(string, sizeof(string));
   
    strcpy(string, "Hello, process!"); 

    printf("Now string:\n    %s\n", (char * )string); 
}

int main(void){
    char string[20] = "Hello thread!";
    printf("Original string:\n    %s\n", (char *)string);

    pthread_t thread;

    if (pthread_create(&thread, NULL, modify, string)){
        puts("create thread error!");
        exit(-1);
    }

    if (pthread_join(thread, NULL)){
        puts("join error!");
        exit(-2);
    }
    printf("process string:\n    %s\n", (char * )string); 
        
    return 0;
}
