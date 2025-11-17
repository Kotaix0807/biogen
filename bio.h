#ifndef BIO_H
#define BIO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tries.h"
#include "tools.h"

void bioStart(TrieNodePtr tree, const char *arg, size_t *adn_length){
    if(adn_length == NULL){
        printf("Error: invalid ADN length buffer\n\n");
        return;
    }
    if(arg == NULL || atoi(arg) <= 0){
        printf("Error: Invalid Tree length\n\n");
        return;
    }
    size_t new_len = (size_t)atoi(arg);
    if(tree && (isTrie(tree) || tree->pos_count > 0)){
        clearTrie(tree);
    }
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

    char *seq = getAdn();
    if(seq){
        if(validateSeq(seq)){
            printf("Error: invalid sequence in 'adn.txt'\n");
            free(seq);
            seq = insertRandAdn();
            if(!seq){
                printf("Error: unable to build tree with random sequence\n\n");
                return;
            }
        }
        createTrie(tree, new_len, seq);
        free(seq);
    } else {
        printf("Warning: trie cleared but no ADN sequence loaded\n");
    }

    *adn_length = new_len;
    printf("Tree created with height %ld\n", *adn_length);
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
    printf("ADN sequence: [%s]\n", arg[1]);
    fclose(ADN_txt);
    printf("Done!\n\n");
}

void bioRead(TrieNodePtr root, size_t len){
    if(isTrie(root) || root->pos_count > 0){
        clearTrie(root);
    }
    char *seq = getAdn();
    if(seq){
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
        createTrie(root, (int)len, seq);
        free(seq);
        printf("Done!\n\n");
    }
    else{
        return;
    }
}

void bioExit(TrieNodePtr root){
    freeTrie(root);
}

void bioSearch(TrieNodePtr root, size_t len, const char *seq){
    search(root, len, seq, 1);
    printf("Done!\n\n");
}

void bioAll(TrieNodePtr root, size_t len){
    if(len <= 0){
        printf("Error: invalid tree length\n\n");
        return;
    }
    if(root == NULL){
        printf("Error: trie not initialized\n\n");
        return;
    }
    if(!isTrie(root)){
        printf("Warning: trie is empty, try running 'bio read' first\n\n");
        return;
    }

    char *sequence = getAdn();
    if(!sequence){
        return;
    }
    if(validateSeq(sequence)){
        printf("Error: invalid ADN sequence in 'adn.txt'\n\n");
        free(sequence);
        return;
    }

    size_t seq_len = strlen(sequence);
    if(seq_len < len){
        printf("Warning: ADN sequence is shorter than the requested group size (%ld)\n\n", len);
        free(sequence);
        return;
    }

    char *buffer = malloc(len + 1);
    if(!buffer){
        printf("Error: unable to allocate buffer for groups\n\n");
        free(sequence);
        return;
    }

    printf("All ADN groups (size %ld):\n", len);
    for(size_t start = 0; start + len <= seq_len; ++start){
        memcpy(buffer, sequence + start, len);
        buffer[len] = '\0';
        search(root, len, buffer, 1);
    }

    free(buffer);
    free(sequence);
    printf("Done!\n\n");
}

static char *copySequence(const char *src, size_t len){
    char *dup = malloc(len + 1);
    if(!dup){
        return NULL;
    }
    memcpy(dup, src, len);
    dup[len] = '\0';
    return dup;
}

void bioMax(TrieNodePtr root, size_t len){
    if(len <= 0){
        printf("Error: invalid tree length\n\n");
        return;
    }
    if(root == NULL){
        printf("Error: trie not initialized\n\n");
        return;
    }
    if(!isTrie(root)){
        printf("Warning: trie is empty, try running 'bio read' first\n\n");
        return;
    }

    char *seq = getAdn();
    if(!seq){
        return;
    }
    if(validateSeq(seq)){
        printf("Error: invalid ADN sequence in 'adn.txt'\n\n");
        free(seq);
        return;
    }

    size_t seq_len = strlen(seq);
    if(seq_len < len){
        printf("Warning: ADN sequence is shorter than the requested group size (%ld)\n\n", len);
        free(seq);
        return;
    }

    char *buffer = malloc(len + 1);
    if(!buffer){
        printf("Error: unable to allocate buffer for groups\n\n");
        free(seq);
        return;
    }

    int first = 0;
    printf("All ADN groups (size %ld):\n", len);
    for(size_t start = 0; start + len <= seq_len; ++start){
        memcpy(buffer, seq + start, len);
        buffer[len] = '\0';
        int current = search(root, len, buffer, 0);
        if(current == -2){
            free(buffer);
            free(seq);
            return;
        }
        if(current > first){
            first = current;
        }
    }

    if(first < 2){
        printf("No repeated sequences of size %ld were found\n\n", len);
        free(buffer);
        free(seq);
        return;
    }

    size_t max_slots = seq_len - len + 1;
    char **tops = calloc(max_slots, sizeof(char*));
    if(!tops){
        printf("Error: unable to store maximum sequences\n\n");
        free(buffer);
        free(seq);
        return;
    }
    size_t stored = 0;

    for(size_t start = 0; start + len <= seq_len; ++start){
        memcpy(buffer, seq + start, len);
        buffer[len] = '\0';
        int current = search(root, len, buffer, 0);
        if(current != first){
            continue;
        }
        int repeated = 0;
        for(size_t i = 0; i < stored; ++i){
            if(strcmp(tops[i], buffer) == 0){
                repeated = 1;
                break;
            }
        }
        if(!repeated){
            tops[stored] = copySequence(buffer, len);
            if(!tops[stored]){
                printf("Error: unable to copy max sequence\n\n");
                break;
            }
            stored++;
        }
    }

    printf("Most repeated sequences (size %ld, %d repetitions):\n", len, first);
    for(size_t i = 0; i < stored; ++i){
        search(root, len, tops[i], 1);
        free(tops[i]);
    }
    free(tops);
    free(buffer);
    free(seq);
    printf("Done!\n\n");
}

void bioMin(TrieNodePtr root, size_t len){
    if(len <= 0){
        printf("Error: invalid tree length\n\n");
        return;
    }
    if(root == NULL){
        printf("Error: trie not initialized\n\n");
        return;
    }
    if(!isTrie(root)){
        printf("Warning: trie is empty, try running 'bio read' first\n\n");
        return;
    }

    char *seq = getAdn();
    if(!seq){
        return;
    }
    if(validateSeq(seq)){
        printf("Error: invalid ADN sequence in 'adn.txt'\n\n");
        free(seq);
        return;
    }

    size_t seq_len = strlen(seq);
    if(seq_len < len){
        printf("Warning: ADN sequence is shorter than the requested group size (%ld)\n\n", len);
        free(seq);
        return;
    }

    char *buffer = malloc(len + 1);
    if(!buffer){
        printf("Error: unable to allocate buffer for groups\n\n");
        free(seq);
        return;
    }

    int min_count = 0;
    printf("All ADN groups (size %ld):\n", len);
    for(size_t start = 0; start + len <= seq_len; ++start){
        memcpy(buffer, seq + start, len);
        buffer[len] = '\0';
        int current = search(root, len, buffer, 0);
        if(current == -2){
            free(buffer);
            free(seq);
            return;
        }
        if(current > 0 && (min_count == 0 || current < min_count)){
            min_count = current;
        }
    }

    if(min_count == 0){
        printf("No matching sequences of size %ld were found\n\n", len);
        free(buffer);
        free(seq);
        return;
    }

    size_t max_slots = seq_len - len + 1;
    char **mins = calloc(max_slots, sizeof(char*));
    if(!mins){
        printf("Error: unable to store minimum sequences\n\n");
        free(buffer);
        free(seq);
        return;
    }
    size_t stored = 0;

    for(size_t start = 0; start + len <= seq_len; ++start){
        memcpy(buffer, seq + start, len);
        buffer[len] = '\0';
        int current = search(root, len, buffer, 0);
        if(current != min_count){
            continue;
        }
        int repeated = 0;
        for(size_t i = 0; i < stored; ++i){
            if(strcmp(mins[i], buffer) == 0){
                repeated = 1;
                break;
            }
        }
        if(!repeated){
            mins[stored] = copySequence(buffer, len);
            if(!mins[stored]){
                printf("Error: unable to copy min sequence\n\n");
                break;
            }
            stored++;
        }
    }

    printf("Least repeated sequences (size %ld, %d repetitions):\n", len, min_count);
    for(size_t i = 0; i < stored; ++i){
        search(root, len, mins[i], 1);
        free(mins[i]);
    }
    free(mins);
    free(buffer);
    free(seq);
    printf("Done!\n\n");
}

#endif // BIO_H
