/* single table substitution cipher:  <23-04-17, river>
 *   https://en.wikipedia.org/wiki/Substitution_cipher
 */

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ASCII_SIZE 256
#define ALPHA_SIZE 26

void check_pharse(int argc, char *argv[]);
void update_table(const char *key, char *table);
void encrypt(char *cipher, const char *plain,  int len, char *key);
void decrypt(char *plain,  const char *cipher, int len, char *key);

int main(int argc, char *argv[]){

    check_pharse(argc, argv);

    int count;
    char *key, table[ALPHA_SIZE*2];
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
    update_table(key, table);

    file = fopen(path, "w");
    if(file == NULL){
        fprintf(stderr, "%s LINE %d: %s\n", __FILE__, __LINE__, strerror(errno));
        exit(EXIT_FAILURE);        
    }

    while((count = fread(raw, sizeof(char), sizeof(raw), stdin)) != 0){
        putchar(argv[1][1]);
        switch(argv[1][1]){
            case 'e':
                encrypt(result, raw, count, table);
                break;
            case 'd':
                decrypt(result, raw, count, table);
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

void update_table(const char *key, char *table){
    int len = strlen(key);
    char flag[ASCII_SIZE] = {0};
    int i, count, ch;

/* Original table:
 *   0 1 2 3 4 5 6 7 8 9 10 ...
 *   A B C D E F G H I J K  ...
 */
    for(count=i=0; i<len; i++){
        if(('A' <= key[i] && key[i] <= 'Z')
                || ('a' <= key[i] && key[i] <= 'z')
                && flag[key[i]] == 0){
            flag[key[i]] = 1;
            table[count++] = key[i];
        }
    }
    for(i=0; i<ALPHA_SIZE*2; i++){
        ch = i < ALPHA_SIZE ? i+'A' : i-ALPHA_SIZE+'a'; // ['A', 'Z'] / ['a', 'z']
        if(flag[ch] == 0){
            table[count++] = ch;    
        }
    }
#ifdef DEBUG
    for(i=0; i<ALPHA_SIZE*2; i++)
        printf("%d: %c  ", i, table[i]);
    putchar('\n');
#endif
    return;
}

void encrypt(char *cipher, const char *plain,  int len, char *key){
    int i, tmp;

    for(i=0; i<len; i++){
        if('A' <= plain[i] && plain[i] <= 'Z'){ // ['A', 'Z']
            tmp = plain[i] - 'A';
            cipher[i] = key[tmp];
        }
        else if('a' <= plain[i] && plain[i] <= 'z'){ // ['a', 'z']
            tmp = plain[i] - 'a' + ALPHA_SIZE;
            cipher[i] = key[tmp];
        }
        else
            cipher[i] = plain[i];
    }

    return;
}

void decrypt(char *plain,  const char *cipher, int len, char *key){
    int i, j;

    for(i=0; i<len; i++){
        if(('A' <= cipher[i] && cipher[i] <= 'Z')
                || ('a' <= cipher[i] && cipher[i] <= 'z')){
            for(j=0; j<ALPHA_SIZE*2; j++)
                if(key[j] == cipher[i])
                    plain[i] = i < ALPHA_SIZE ? i+'A': i-ALPHA_SIZE+'a';
        }
        else
            plain[i] = cipher[i];
    }

    return;
}
