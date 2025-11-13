#ifndef BIO_H
#define BIO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tries.h"
#include "tools.h"

void bioStart(TrieNodePtr tree, const char *arg, int *adn_length){
    if(adn_length == NULL){
        printf("Error: invalid DNA length buffer\n\n");
        return;
    }
    if(arg == NULL || atoi(arg) <= 0){
        printf("Error: Invalid Tree length\n\n");
        return;
    }
    *adn_length = atoi(arg);

    FILE *ADN_txt = fopen("adn.txt", "r");
    if(!ADN_txt){
        printf("Warning: 'adn.txt' file does not exists\nCreating new file...\n");
        FILE *rewrite = fopen("adn.txt", "w+");
        if(!rewrite){
            printf("Error: something went wrong with adn.txt\n\n");
            return;
        }
        fclose(rewrite);
        printf("File Created!\nWould you like to generate a random gen string? (y/n) ");
        char *argv[1] = {0};
        int args = escanf(argv, 1, 4);
        char answer;
        if(args > 0 && argv[0][0] != '\0' && argv[0] != NULL){
            answer = argv[0][0];
        }
        switch(answer){
            case 'y':
            case 'Y':
                insertRandAdn();
                break;
            case 'n':
            case 'N':
                printf("Got it, no random gen string generated\n");
                break;
            default:
                printf("Invalid option, skipping random generation.\n");
                break;
        }
        if(args > 0){
            freeArgs(argv, args);
        }
    } else {
        fclose(ADN_txt);
    }
    printf("Tree created with height %d\n", *adn_length);
    printf("Done!\n\n");
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
    printf("DNA sequence: [%s]\n", arg[1]);
    fclose(ADN_txt);
    printf("Done!\n\n");
}

void bioRead(TrieNodePtr root, int max_height){
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
    root = createTrie(root, max_height, seq);//createTrie();
    if(!root){
        return;
    }
    free(seq);
    printf("Done!\n\n");
}

void bioExit(TrieNodePtr root){
    freeTrie(root);
}

void bioSearch(TrieNodePtr root, int len, const char *seq){
    
    printf("Search dice: %d\n", search(root, len, seq));
}

#endif // BIO_H
