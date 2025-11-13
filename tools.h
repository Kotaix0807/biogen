#ifndef TOOLS_H
#define TOOLS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ADN 4
#define MAX_LEN 20
#define MIN_LEN 5

/**
 * @brief Transforma de gen -> int (Interpreta el gen como entero)
 * 
 * @param gen el gen leido.
 * @return int del gen.
 */
int genToInt(char gen){
    switch(gen)
    {
        case 'A':{
            return 0;
            break;
        }
        case 'C':{
            return 1;
            break;
        }
        case 'G':{
            return 2;
            break;
        }
        case 'T':{
            return 3;
            break;
        }
        default:{
            return -1;
        }
    }
    return -1;
}

/**
 * @brief 
 * Escanea strings hasta que el usuario presiona Enter.
 * @param strns arreglo de argumentos.
 * @param MAX_ARGS maximo de argumentos.
 * @param MAX_CHARS maximo de caracteres por argumento.
 * @return Cantidad de argumentos escaneados (int).
 */
int escanf(char *strns[], int MAX_ARGS, int MAX_CHARS)
{
    char buffer[MAX_CHARS];
    int count = 0;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL){ // Se obtiene el string de todo lo ingresado por teclado (Se obtiene stdin y se copia al buffer)
        return count;
    }
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n'){ //Agrega caracter nulo si detecta '\n'
        buffer[len - 1] = '\0';
    }

    char *token = strtok(buffer, " "); // Regla: Separa los strings con ' '
    while (token != NULL && count < MAX_ARGS){
        size_t token_len = strlen(token);

        strns[count] = (char *)malloc(token_len + 1); //Asigna memoria
        if (strns[count] == NULL){
            perror("Error allocating memory");
            break;
        }

        strcpy(strns[count], token); //Una vez alocada la memoria -> Copiar
        count++;

        token = strtok(NULL, " "); //Vacia string guardado en "token"
    }

    return count;
}
/**
 * @brief Libera el arreglo de argumentos usado.
 * 
 * @param strns arreglo de argumentos.
 * @param length cantidad de argumentos.
 */
void freeArgs(char* strns[], int length)
{
    if(length <= 0){
        printf("Error: couldn't free Arguments strings, invalid length.\n");
    }
    for(int i = 0; i < length; i++){
        free(strns[i]);
        strns[i] = NULL;
    }
}

/**
 * @brief Binary Search de strings y recursivo
 * 
 * @param arr 
 * @param low 
 * @param high 
 * @param target 
 * @return int 
 */
int binarySearch(const char *arr, int low, int high, char target){
    if (low > high) {
        return -1; //No encontrado
    }
    int mid = low + (high - low) / 2;

    if (arr[mid] == target) {
        return mid; //Encontrado
    } else if (arr[mid] < target) {
        return binarySearch(arr, mid + 1, high, target); //derecha
    } else {
        return binarySearch(arr, low, mid - 1, target);// izquierda
    }
}
/**
 * @brief Valida secuencia de ADN, si es correcta, devuelve 0, si no, devuelve 1
 * 
 * @param seq Secuencia de ADN
 * @return int 
 */
int validateSeq(const char *seq){
    const char valid[] = {'A', 'C', 'G', 'T'};
    const int n_valids = sizeof(valid) / sizeof(valid[0]);

    for (size_t i = 0; seq[i] != '\0'; i++) {
        if (binarySearch(valid, 0, n_valids - 1, seq[i]) == -1) {
            printf("Error: char '%c' is not allowed on sequence\n", seq[i]);
            printf("Your sequence must have this characters:\n");
            printf("'A', 'C', 'G', 'T'\n");
            return 1;
        }
    }
    return 0;
}

int randNumb(int min, int max){
    if(min == max || min > max){
        printf("Error: invalid values for random selection\n");
        return 0;
    }
    return min + rand() % (max - min + 1);
}

char *randAdnSeq(){
    srand(time(NULL));
    size_t len = (size_t)randNumb(MIN_LEN, MAX_LEN);
    if(!len)
        return NULL;
    char *seq = malloc(len + 1);
    if(!seq){
        return NULL;
    }
    const char alphabet[ADN] = {'A', 'C', 'G', 'T'};
    for(size_t i = 0; i < len; ++i){
        seq[i] = alphabet[rand() % ADN];
    }
    seq[len] = '\0';
    return seq;
}

char *insertRandAdn(){
    printf("Creating new random sequence...\n");
    char *buffer = randAdnSeq();
    if(!buffer){
        printf("Error: failed to generate random sequence\n");
        return NULL;
    }
    FILE *rewrite = fopen("adn.txt", "w+");
    if(!rewrite){
        printf("Error: something went wrong with adn.txt\n");
        free(buffer);
        return NULL;
    }
    fputs(buffer, rewrite);
    fclose(rewrite);
    printf("New sequence inserted succesfully: [%s]\nRead 'adn.txt'\n\n", buffer);
    return buffer;
}

#endif // TOOLS_H
