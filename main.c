#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "nodes.h"
#include "tries.h"

#define MAX_ARGS 4

int main(void){
    //Variables globales del programa
    int instance = 1;
    char *strns[MAX_ARGS];

    //Variables globales del arbol
    TrieNodePtr root = createNode();
    int adn_len = 0;

    printf("Welcome to BioGen program!\nIf you need help, type:\n'help' || 'h'\n\n");

    //int adn_len = loadTrie(root);
    while(instance){

        printf(">bio ");
        int len = escanf(strns, MAX_ARGS, 1024);
        if(len < 1){
            printf("Error, non arguments in\n");
            continue;
        }

        //Comandos
        if(!strcmp(strns[0], "help") || !strcmp(strns[0], "h") || !strcmp(strns[0], "Help")){
            printf("Commands:\nbio start <numb> -> Trie max length\n");
            printf("bio read -> read adn.txt file\n");
            printf("bio search <gen> -> Shows gen position\n");
            printf("bio max -> shows most repeated gens\n");
            printf("bio min -> shows last repeated gens\n");
            printf("bio all -> shows all gens\n");
            printf("bio exit -> delete adn.tx file and clear program\n\n");
        }
        else if(!strcmp(strns[0], "start")){
            printf("Initializing tree...\n\n");
            bioStart(root, strns[1], &adn_len);
            printf("Gen large: %d\n", adn_len);
        }
        else if(!strcmp(strns[0], "new")){
            printf("Creating new sequence...\n");
            bioNew(strns[1]);
        }
        else if(!strcmp(strns[0], "read")){
            printf("Reading tree...\n\n");
        }
        else if(!strcmp(strns[0], "search")){
            printf("Finding '%s'\n\n", strns[1]);
        }
        else if(!strcmp(strns[0], "max")){
            printf("Finding max...\n\n");
        }
        else if(!strcmp(strns[0], "min")){
            printf("Finding min...\n\n");
        }
        else if(!strcmp(strns[0], "all")){
            printf("Showing tree\n\n");
        }
        else if(!strcmp(strns[0], "exit")){
            printf("Cleaning cache and exiting...\n");
            //Exiting...
            printf("Bye!\n");
            instance = 0;
        }
        else if(strns[0] != NULL){
            printf("Command '%s' does not exists\n\n", strns[0]);
        }
        freeArgs(strns, len);
    }
    return 0;

}
