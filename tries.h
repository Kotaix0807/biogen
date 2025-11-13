#ifndef TRIES_H
#define TRIES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tools.h"

struct TrieNode {
    struct TrieNode *children[ADN];
    int isLeaf;
};

typedef struct TrieNode* TrieNodePtr;

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

TrieNodePtr createTrie(TrieNodePtr root, int max_height, const char *seq){
    if(seq == NULL || seq[0] == '\0'){
        printf("Error: failed to create Trie, invalid sequence\n\n");
        return NULL;
    }
    if(max_height <= 0){
        printf("Error: invalid trie height %d\n\n", max_height);
        return NULL;
    }
    if(root == NULL){
        root = createNode();
        if(!root){
            printf("Error: unable to allocate trie root\n\n");
            return NULL;
        }
    }

    size_t seq_len = strlen(seq);
    size_t limit = seq_len < (size_t)max_height ? seq_len : (size_t)max_height;
    TrieNodePtr current = root;

    for(size_t i = 0; i < limit; i++){
        int gen = genToInt(seq[i]);
        if(gen < 0){
            printf("Error: char '%c' is not valid for trie insertion\n", seq[i]);
            return root;
        }
        if(current->children[gen] == NULL){
            current->children[gen] = createNode();
            if(current->children[gen] == NULL){
                printf("Error: unable to allocate trie node\n");
                return root;
            }
        }
        current = current->children[gen];
    }
    current->isLeaf = 1;
    return root;
}

void freeTrie(TrieNodePtr tree, int len){
    for(int i = 0; i < len; i++){
        free(tree->children[i]);
    }
}

#endif // TRIES_H
