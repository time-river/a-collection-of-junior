/* caesar cipher:  <23-04-17, river>
 *   https://en.wikipedia.org/wiki/Caesar_cipher
 */

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void check_pharse(int argc, char **argv);
void encrypt(char *cipher, const char *plain,  int len, int key);
void decrypt(char *plain,  const char *cipher, int len, int key);

int main(int argc, char *argv[]){

    check_pharse(argc, argv);

    int key, count;
    FILE *file;
    char *path;
    char raw[BUFSIZ];
    char result[sizeof(raw)];

    if(argv[1][1] == 'o'){
        path = argv[2];
    }
    else{
        printf("input the output file name.\n");
        return 0;
    }

    key = atoi(argv[4]);
    if(key < 1 || 25 < key ){ // [1, 25]
        printf("1 <= k <= 25, integer");
        return 0;
    }

    file = fopen(path, "w");
    if(file == NULL){
        fprintf(stderr, "%s LINE %d: %s\n", __FILE__, __LINE__, strerror(errno));
        exit(EXIT_FAILURE);
    }

    while((count = fread(raw, sizeof(char), sizeof(raw), stdin)) != 0){
        switch(argv[5][1]){
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

    return 0;
}

void check_pharse(int argc, char **argv){
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

void encrypt(char *cipher, const char *plain,  int len, int key){
    int i, tmp;

    for(i=0; i<len; i++){
        if('A' <= plain[i] && plain[i] <= 'Z'){ // ['A', 'Z']
            tmp = plain[i] - 'A';
            tmp = (tmp + key) % 26;
            cipher[i] = tmp + 'A';
        }
        else if('a' <= plain[i] && plain[i] <= 'z'){ // ['a', 'z']
            tmp = plain[i] - 'a';
            tmp = (tmp + key) % 26;
            cipher[i] = tmp + 'a';
        }
        else
            cipher[i] = plain[i];
    }

    return;
}

void decrypt(char *plain,  const char *cipher, int len, int key){
    int i, tmp;

    for(i=0; i<len; i++){
        if('A' <= cipher[i] && cipher[i] <= 'Z'){
            tmp = cipher[i] - 'A' + 26;
            tmp = (tmp - key) % 26;
            plain[i] = tmp + 'A';
        }
        else if('a' <= cipher[i] && cipher[i] <= 'z'){
            tmp = cipher[i] - 'a' + 26;
            tmp = (tmp - key) % 26;
            plain[i] = tmp + 'a';
        }
        else
            plain[i] = cipher[i];
    }
    return;
}
