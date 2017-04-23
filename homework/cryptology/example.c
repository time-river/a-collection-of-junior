#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void check_pharse(const int argc, const char *argv[]);

int main(int argc, char *argv[]){

    check_pharse(argc, argv);



    return 0;
}

void check_pharse(const int argc, const char *argv[]){
    if(argc != 6 ||
        (argv[5][1] != 'e' && argv[5][1] != 'd')){
        fprintf(stdout, "Usage: %s\n"
                        "  -o file_name\n"
                        "  -k key\n"
                        "  -e (encrypt) or -d (decrypt)\n"
                        "  < file\n",
                        argv[0]);
        exit(EXIT_SUCCESS);
    }
    return;
}
