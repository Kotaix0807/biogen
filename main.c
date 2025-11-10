#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nodes.h"
#include "tries.h"

int main(int argc, char *argv[]){
    if(argc < 2){
        printf("Error, non arguments in\n");
        return EXIT_FAILURE;
    }
    TrieNodePtr root;
    int len = LoadTrie(root);

    //Comandos
    if(!strcmp(argv[1], "help") || !strcmp(argv[1], "h") || !strcmp(argv[1], "Help")){
        printf("Commands:\nbio start <numb> -> Trie max length\n");
        printf("bio read -> read adn.txt file\n");
        printf("bio search <gen> -> Shows gen position\n");
        printf("bio max -> shows most repeated gens\n");
        printf("bio min -> shows last repeated gens\n");
        printf("bio all -> shows all gens\n");
        printf("bio exit -> delete adn.tx file and clear program\n");

        return EXIT_SUCCESS;
    }
    else if(!strcmp(argv[1], "start")){
        printf("Initializing tree...\n");
        return bioStart(root, argv[2]);
    }
    else if(!strcmp(argv[1], "read")){
        printf("Reading tree...\n");
        return EXIT_SUCCESS;
    }
    else if(!strcmp(argv[1], "search")){
        printf("Finding '%s'\n", argv[2]);
        return EXIT_SUCCESS;
    }
    else if(!strcmp(argv[1], "max")){
        printf("Finding max...\n");
        return EXIT_SUCCESS;
    }
    else if(!strcmp(argv[1], "min")){
        printf("Finding min...\n");
        return EXIT_SUCCESS;
    }
    else if(!strcmp(argv[1], "all")){
        printf("Showing tree\n");
        return EXIT_SUCCESS;
    }
    else if(!strcmp(argv[1], "exit")){
        printf("Cleaning cache and exiting...\n");
        return EXIT_SUCCESS;
    }
    else if(argv[1] != NULL){
        printf("Command '%s' does not exists\n", argv[1]);
        return EXIT_FAILURE;
    }
    return 0;

}