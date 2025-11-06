#include <stdio.h>
#include <stdlib.h>
#include "nodes.h"

int main(int argc, char *argv[]){
    if(argc < 2){
        printf("Error, non arguments in\n");
        return EXIT_FAILURE;
    }
    else if(argv[2] == 'help'){
        printf("Help command.\n");
        return EXIT_SUCCESS;
    }
    else if(argv[2] == 'start'){
        printf("Initializing tree...\n");
        return EXIT_SUCCESS;
    }
    else if(argv[2] == 'read'){
        printf("Reading tree...\n");
        return EXIT_SUCCESS;
    }
    else if(argv[2] == 'search'){
        printf("Finding '%s'\n", argv[3]);
        return EXIT_SUCCESS;
    }
    else if(argv[2] == 'max'){
        printf("Finding max...\n");
        return EXIT_SUCCESS;
    }
    else if(argv[2] == 'min'){
        printf("Finding min...\n");
        return EXIT_SUCCESS;
    }
    else if(argv[2] == 'all'){
        printf("Showing tree\n");
        return EXIT_SUCCESS;
    }
    else if(argv[2] == 'exit'){
        printf("Cleaning cache and exiting...\n");
        return EXIT_SUCCESS;
    }
    else{
        if(argv[2] != NULL)
            printf("Command '%s' does not exists\n", argv[2]);
        return EXIT_FAILURE;
    }


}