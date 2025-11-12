#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ADN 4

struct TrieNode {
    struct TrieNode *children[ADN];
    int isLeaf;
};

typedef struct TrieNode* TrieNodePtr;
/**
 * @brief Transforma de gen -> int (Interpreta el gen como entero)
 * 
 * @param gen el gen leido.
 * @return int del gen.
 */
int genToInt(char gen){
    switch(gen)
    {
        case('A'):{
            return 0;
            break;
        }
        case('C'):{
            return 1;
            break;
        }
        case('G'):{
            return 2;
            break;
        }
        case('T'):{
            return 3;
            break;
        }
        default:{
            return -1;
        }
    }
    return -1;
}

TrieNodePtr createNode() {
    TrieNodePtr newNode = (TrieNodePtr)malloc(sizeof(struct TrieNode));
    if (newNode) {
        newNode->isLeaf = 0;
        for (int i = 0; i < ADN; i++) {
            newNode->children[i] = NULL;
        }
    }
    return newNode;
}

void freeTrie(TrieNodePtr tree, int len){
    for(int i = 0; i < len; i++){
        free(tree->children[i]);
    }
}

/*int loadTrie(TrieNodePtr tree){
    int len = 0;
    tree = createNode();
    FILE *ADN_txt = fopen("adn.txt", "r");
    if(ADN_txt){
        char c = fgetc(ADN_txt);
        len = c - '0';
        fclose(ADN_txt);
        //printf("File adn.txt found\nTrie Lenght scanned: '%d'\n", len);
    }
    else{
        printf("FIle adn.txt not found\n");
    }
    return len;
}*/

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
}

void bioNew(const char *arg){
    if(arg == NULL){
        printf("Error: invalid sequence\n\n");
        return;
    }
    //size_t sizeArg = strlen(arg);
        /*
        if(genToInt(arg[i]) == -1){
            printf("Error: Your sequence must have this characters:\n");
            printf("'A', 'C', 'G', 'T'\n");
        }*/
    if(validateSeq(arg)){
        return;
    }
    FILE *ADN_txt = fopen("adn.txt", "w+");
    if(!ADN_txt){
        printf("Error: something went wrong with adn.txt\n\n");
        return;
    }
    printf("Good, now puting string on file...\n");
    fputs(arg, ADN_txt);
    fclose(ADN_txt);
}