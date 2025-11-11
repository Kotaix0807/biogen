#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ADN 4

struct TrieNode {
    struct TrieNode *children[ADN];
    int isEnd;
};

typedef struct TrieNode* TrieNodePtr;

TrieNodePtr createNode() {
    TrieNodePtr newNode = (TrieNodePtr)malloc(sizeof(struct TrieNode));
    if (newNode) {
        newNode->isEnd = 0;
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

int LoadTrie(TrieNodePtr tree){
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
}

void bioStart(TrieNodePtr tree, const char* numb){
    if(numb == NULL || atoi(numb) <= 0){
        printf("Error: Invalid Tree length\n");
    }
    FILE *ADN_txt = fopen("adn.txt", "w+");
    if(!ADN_txt){
        printf("Error: something went wrong with adn.txt\n");
    }
    fputs(numb, ADN_txt);
    fputc('\n', ADN_txt);
    fclose(ADN_txt);
}



