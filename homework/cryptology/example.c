/* single table substitution cipher:  <23-04-17, river>
 *   https://en.wikipedia.org/wiki/Substitution_cipher
 */

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void check_pharse(int argc, char *argv[]);
void encrypt(char *cipher, const char *plain,  int len, char *key);
void decrypt(char *plain,  const char *cipher, int len, char *key);

int main(int argc, char *argv[]){

    check_pharse(argc, argv);

    int count;
    char *key;
    char *path;
    char raw[BUFSIZ];
    char result[sizeof(raw)];
    FILE *file;

    if(argv[2][1] == 'o')
        path = argv[3];
    else{
        printf("input the output file name.\n");
        return 0;
    }
    
    key = argv[5];

    file = fopen(path, "w");
    if(file == NULL){
        fprintf(stderr, "%s LINE %d: %s\n", __FILE__, __LINE__, strerror(errno));
        exit(EXIT_FAILURE);        
    }

    while((count = fread(raw, sizeof(char), sizeof(raw), stdin)) != 0){
        switch(argv[1][1]){
            case 'e':
                encrypt(result, raw, count, key);
                break;
            case 'd':
                decrypt(result, raw, count, key);
                break;
        }
        fwrite(result, sizeof(char), count, file);
#ifdef DEBUG
        fwrite(result, sizeof(char), count, stdout);
#endif
    }
    fclose(file);
    return 0;
}

void check_pharse(int argc, char *argv[]){
    if(argc != 6 ||
        (argv[1][1] != 'e' && argv[1][1] != 'd')){
        fprintf(stdout, "Usage: %s\n"
                        "  -e (encrypt) or -d (decrypt)\n"
                        "  -o file_name\n"
                        "  -k key\n"
                        "  < file\n",
                        argv[0]);
        exit(EXIT_SUCCESS);
    }
    return;
}

void encrypt(char *cipher, const char *plain,  int len, char *key);
void decrypt(char *plain,  const char *cipher, int len, char *key);
