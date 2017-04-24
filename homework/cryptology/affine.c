/* single table substitution cipher:  <23-04-17, river>
 *   https://en.wikipedia.org/wiki/Substitution_cipher
 */

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ALPHA_SIZE 26

void check_pharse(int argc, char *argv[]);
void encrypt(char *cipher, const char *plain,  int len, int *key);
void decrypt(char *plain,  const char *cipher, int len, int *key);

int main(int argc, char *argv[]){

    check_pharse(argc, argv);

    int count;
    int key[2];
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
    
    key[0] = atoi(argv[5]);
    key[1] = atoi(argv[6]);

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
    if(argc != 7 ||
        (argv[1][1] != 'e' && argv[1][1] != 'd')){
        fprintf(stdout, "Usage: %s\n"
                        "  -e (encrypt) or -d (decrypt)\n"
                        "  -o file_name\n"
                        "  -k x b\n"
                        "  < file\n",
                        argv[0]);
        exit(EXIT_SUCCESS);
    }
    return;
}

void encrypt(char *cipher, const char *plain,  int len, int *key){
    int i, tmp;

    for(i=0; i<len; i++){
        if('A' <= plain[i] && plain[i] <= 'Z'){
            tmp = plain[i] - 'A';
            tmp = (tmp * key[0] + key[1]) % ALPHA_SIZE;
            cipher[i] = tmp + 'A';
        }
        else if('a' <= plain[i] && plain[i] <= 'z'){
            tmp = plain[i] - 'a';
            tmp = (tmp * key[0] + key[1]) % ALPHA_SIZE;
            cipher[i] = tmp + 'a';
        }
        else
            cipher[i] = plain[i];
    }

    return;
}

void decrypt(char *plain,  const char *cipher, int len, int *key){
    int i, tmp, d, inverse;

    // get key[0]'s inverse element
    for(inverse=1; ; inverse++){
        tmp = key[0] * inverse;
        if(tmp % ALPHA_SIZE == 1)
            break;
    }

    for(i=0; i<len; i++){
        if('A' <= cipher[i] && cipher[i] <= 'Z'){
            tmp = cipher[i] - 'A';
            d = tmp - key[1];
            tmp = inverse * (d<0 ? d+ALPHA_SIZE : d) % ALPHA_SIZE;
            plain[i] = tmp + 'A';
        }
        else if('a' <= cipher[i] && cipher[i] <= 'z'){
            tmp = cipher[i] - 'a';
            d = tmp - key[1];
            tmp = inverse * (d<0 ? d+ALPHA_SIZE : d) % ALPHA_SIZE;
            plain[i] = tmp + 'a';
        }
        else
            plain[i] = cipher[i];
    }
}
