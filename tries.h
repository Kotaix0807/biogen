#ifndef TRIES_H
#define TRIES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tools.h"

struct TrieNode {
    struct TrieNode *children[ADN];
    int isLeaf;
    int *positions;
    size_t pos_count;
    size_t pos_capacity;
};

typedef struct TrieNode* TrieNodePtr;

TrieNodePtr createNode() {
    TrieNodePtr newNode = (TrieNodePtr)malloc(sizeof(struct TrieNode));
    if (newNode) {
        newNode->isLeaf = 0;
        newNode->positions = NULL;
        newNode->pos_count = 0;
        newNode->pos_capacity = 0;
        for (int i = 0; i < ADN; i++) {
            newNode->children[i] = NULL;
        }
    }
    return newNode;
}

int isTrie(TrieNodePtr root){
    if(!root){
        return 0;
    }
    if(root->pos_count > 0){
        return 1;
    }
    for(int i = 0; i < ADN; ++i){
        if(root->children[i]){
            return 1;
        }
    }
    return 0;
}

int addPosition(TrieNodePtr node, int position){
    if(!node){
        return 1;
    }
    if(node->pos_count == node->pos_capacity){
        size_t new_capacity;
        if(node->pos_capacity == 0){
            new_capacity = 4;
        } else {
            new_capacity = node->pos_capacity * 2;
        }
        int *tmp = realloc(node->positions, new_capacity * sizeof(int));
        if(!tmp){
            printf("Error: unable to store positions for node\n");
            return 1;
        }
        node->positions = tmp;
        node->pos_capacity = new_capacity;
    }
    node->positions[node->pos_count++] = position;
    return 0;
}

TrieNodePtr createTrie(TrieNodePtr root, size_t len, const char *seq){
    if(seq == NULL || seq[0] == '\0'){
        printf("Error: failed to create Trie, invalid sequence\n\n");
        return NULL;
    }
    if(len <= 0){
        printf("Error: invalid trie height %ld\n\n", len);
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
    for(size_t start = 0; start < seq_len; ++start){
        TrieNodePtr current = root;
        size_t limit = seq_len - start;
        if(limit > len){
            limit = len;
        }
        for(size_t depth = 0; depth < limit; ++depth){
            char base = seq[start + depth];
            int gen = genToInt(base);
            if(gen < 0){
                printf("Error: char '%c' is not valid for trie insertion\n", base);
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
        if(addPosition(current, (int)start)){
            printf("Warning: could not store position %ld for substring\n", start);
        }
    }
    return root;
}

int search(TrieNodePtr root, size_t len, const char *seq, int print){
    if(seq == NULL || seq[0] == '\0'){
        printf("Error: no sequence in\n\n");
        return -2;
    }
    if(len <= 0){
        printf("Error: invalid trie height %ld\n\n", len);
        return -2;
    }
    if(root == NULL){
        root = createNode();
        if(!root){
            printf("Error: unable to allocate trie root\n\n");
            return -2;
        }
    }

    size_t seq_len = strlen(seq);
    if(seq_len > (size_t)len){
        printf("Error: '%s' is longer than the configured trie length (%ld)\n\n", seq, len);
        return -1;
    }

    TrieNodePtr current = root;
    for(size_t i = 0; i < seq_len; i++){
        int gen = genToInt(seq[i]);
        if(gen < 0){
            printf("Error: char '%c' is not valid for trie search\n", seq[i]);
            return -1;
        }
        if(current->children[gen] != NULL){
            current = current->children[gen];
        } else {
            printf("Couldn't find '%s'\n\n", seq);
            return -1;
        }
    }
    if(!current->isLeaf){
        printf("Couldn't find '%s'\n\n", seq);
        return -1;
    }
    if(current->pos_count == 0){
        printf("'%s' found, but no positions stored\n\n", seq);
        return 0;
    }
    if(print)
        printf("%s", seq);
    for(size_t i = 0; i < current->pos_count; ++i){
        if(print)
            printf(" %d", current->positions[i]); //printf("- pos %d: %s\n", current->positions[i], seq);
    }
    if(print)
        printf("\n");
    return (int)current->pos_count;
}

void freeTrie(TrieNodePtr tree){
    if(!tree){
        return;
    }
    for(int i = 0; i < ADN; i++){
        freeTrie(tree->children[i]);
    }
    free(tree->positions);
    free(tree);
}

void clearTrie(TrieNodePtr root){
    if(!root){
        return;
    }
    for(int i = 0; i < ADN; ++i){
        if(root->children[i]){
            freeTrie(root->children[i]);
            root->children[i] = NULL;
        }
    }
    free(root->positions);
    root->positions = NULL;
    root->pos_count = 0;
    root->pos_capacity = 0;
    root->isLeaf = 0;
}

#endif // TRIES_H
