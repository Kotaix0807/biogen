#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tools.h"
#include "tries.h"
#include "bio.h"

#define MAX_ARGS 4

int main(void){
    //Variables globales del programa
    int instance = 1;
    char *strns[MAX_ARGS] = {0};
    
    //Variables globales del arbol
    TrieNodePtr root = createNode();
    int adn_len = 0;

    printf("Welcome to BioGen program!\nType: 'help' || 'h' for help\n\n");

    //int adn_len = loadTrie(root);
    while(instance){
        printf(">bio ");
        int numb_str = escanf(strns, MAX_ARGS, 1024);
        if(numb_str < 1){
            printf("Error, non arguments in\n");
            continue;
        }

        //Comandos
        if(!strcmp(strns[0], "help") || !strcmp(strns[0], "h") || !strcmp(strns[0], "Help")){
            printf("Commands:\n\tbio start <numb> -> Trie max length\n");
            printf("\tbio new <DNA_Sequence> -> create a new DNA Sequence\n");
            printf("\tbio new random -> create a new random DNA Sequence\n");
            printf("\tbio read -> read adn.txt file\n");
            printf("\tbio search <gen> -> Shows gen position\n");
            printf("\tbio max -> shows most repeated gens\n");
            printf("\tbio min -> shows last repeated gens\n");
            printf("\tbio all -> shows all gens\n");
            printf("\tbio exit -> delete adn.txt file and clear program\n\n");
        }
        else if(!strcmp(strns[0], "start")){
            printf("Initializing tree...\n");
            bioStart(root, strns[1], &adn_len);
        }
        else if(!strcmp(strns[0], "read")){
            printf("Reading tree...\n");
            bioRead(root, adn_len);
        }
        else if(!strcmp(strns[0], "new")){
            printf("Creating new sequence...\n");
            bioNew(strns);
        }
        else if(!strcmp(strns[0], "search")){
            printf("Finding '%s'\n\n", strns[1]);
            bioSearch(root, adn_len, strns[1]);
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
            bioExit(root);
            printf("Bye!\n\n");
            instance = 0;
        }
        else if(strns[0] != NULL){
            printf("Command '%s' does not exists\n\n", strns[0]);
        }
        freeArgs(strns, numb_str);
    }
    return 0;

}
