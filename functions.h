#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

int validateSeq(const char *seq){
    const char valid[] = {'A', 'C', 'G', 'T'};
    const int n_valids = sizeof(valid) / sizeof(valid[0]);

    for (size_t i = 0; seq[i] != '\0'; ++i) {
        if (binarySearch(valid, 0, n_valids - 1, seq[i]) == -1) {
            printf("Error: char '%c' is not allowed on sequence\n\n", seq[i]);
            return 1;
        }
    }
    return 0;
}