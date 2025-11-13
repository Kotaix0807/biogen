#ifndef BIO_H
#define BIO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tries.h"
#include "tools.h"

void bioStart(TrieNodePtr tree, const char *arg, int *adn_length){
    if(arg == NULL || atoi(arg) <= 0){
        printf("Error: Invalid Tree length\n");
        return;
    }
    *adn_length = atoi(arg);
    FILE *ADN_txt = fopen("adn.txt", "w+");
    if(!ADN_txt){
        printf("Error: something went wrong with adn.txt\n");
        return;
    }
    fclose(ADN_txt);
    printf("Tree created with height %d\n\n", *adn_length);
}

void bioNew(char *arg[]){
    if(arg[1] == NULL){
        printf("Error: invalid sequence\n\n");
        return;
    }
    if(!strcmp(arg[1], "random")){
        insertRandAdn();
        return;
    }
    //size_t sizeArg = strlen(arg);
        /*
        if(genToInt(arg[i]) == -1){
            printf("Error: Your sequence must have this characters:\n");
            printf("'A', 'C', 'G', 'T'\n");
        }*/
    if(validateSeq(arg[1])){
        printf("\n");
        return;
    }
    FILE *ADN_txt = fopen("adn.txt", "w+");
    if(!ADN_txt){
        printf("Error: something went wrong with adn.txt\n\n");
        return;
    }
    fputs(arg[1], ADN_txt);
    fclose(ADN_txt);
}
void bioRead(){
    FILE *ADN_txt = fopen("adn.txt", "rb");
    if(!ADN_txt){
        printf("Error: file 'adn.txt' not found\n");
        printf("type: 'start <tree_length>' to initialize a new tree\n\n");
        return;
    }

    if(fseek(ADN_txt, 0, SEEK_END) != 0){
        printf("Error: unable to read 'adn.txt' size\n");
        fclose(ADN_txt);
        return;
    }

    long file_size = ftell(ADN_txt);
    if(file_size < 0){
        printf("Error: unable to determine 'adn.txt' size\n");
        fclose(ADN_txt);
        return;
    }

    rewind(ADN_txt);
    size_t large = (size_t)file_size;
    char *seq = malloc(large + 1);
    if(!seq){
        printf("Error: malloc failed\n");
        fclose(ADN_txt);
        return;
    }

    size_t read_bytes = fread(seq, 1, large, ADN_txt);
    seq[read_bytes] = '\0';
    fclose(ADN_txt);

    if(read_bytes == 0){
        printf("Warning: 'adn.txt' is empty\n\n");
        free(seq);
        seq = insertRandAdn();
        if(seq){
            free(seq);
        }
        return;
    }
    
    printf("DNA sequence: [%s]\n", seq); //<---------- HALF-END
    
    if(validateSeq(seq)){
        printf("Error: invalid sequence in 'adn.txt'\n");
        free(seq);
        seq = insertRandAdn();
        if(seq){
            free(seq);
        }
        return;
    }
    
    //Aqui deberia empezar a crear el arbol
    //createTrie();
    free(seq);
}

#endif // BIO_H
