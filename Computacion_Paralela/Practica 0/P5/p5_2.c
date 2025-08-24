#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>


int** reserva_memoria(int tam);
void imprimirMatriz(int tamFila, int tamColum, int **matriz);
void liberar_memoria(int **matriz, int tamFila);

int main(int argc, char *argv[]) {


    if(argc != 2 || isdigit(*argv[1]) != 1) {
        printf("Parametro(s) incorrecto(s)\n");
        printf("Solo se admite un numero entero\n");
        return -1;
    }


    FILE *fichero = fopen("fichero2.bin", "rb");

    if(fichero == NULL) {
        printf("Error al abrir el fichero.\n");
        return -1;
    }

    size_t size = 256 * 1024; // Tamaño a leer de fichero (256KB)
    int matriz_size = sqrt(size/sizeof(int));



    int **matriz = reserva_memoria(matriz_size);

    for(int i = 0; i < matriz_size; i++) fread(matriz[i], sizeof(int), matriz_size, fichero);
    
    
    int valor = atoi(argv[1]);
    int menores_iguales = 0;
    //imprimirMatriz(matriz_size, matriz_size, matriz);
    for(int i = 0; i < matriz_size; i++) {
        for(int j = 0; j < matriz_size; j+= 3) if(*(matriz[i] + j) <= valor) menores_iguales++;
    }
    printf("El numero de elementos menores o iguales al valor introducido son: %d\n", menores_iguales);
    fclose(fichero);
    liberar_memoria(matriz, matriz_size);
    return 0;
}


int** reserva_memoria(int tam) {
    int **matriz = (int**) malloc(tam * sizeof(int*));
    for(int i = 0; i < tam; i++) matriz[i] = (int*) malloc(tam * sizeof(int));

    if(matriz == NULL || matriz[0] == NULL) {
        printf("No se ha podido realizar la reserva de memoria para la matriz\n");
        return NULL;
    }
    return matriz;
}


void imprimirMatriz(int tamFila, int tamColum, int **matriz) {
    for(int i = 0; i < tamFila; i++) {
        for(int j = 0; j < tamColum ;j++){
            printf("Posicion %d:%d = %d\n" , i, j, matriz[i][j]);
        }
        printf("\n");
    }
}

void liberar_memoria(int **matriz, int tamFila) {
    for (int i = 0; i < tamFila; i++) {   
        free(matriz[i]);
    }
    free(matriz);
}