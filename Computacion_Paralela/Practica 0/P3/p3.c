#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#define row_less_fr 10
#define row_less_l 3
#define clmn_less_fr 7
#define clmn_less_l 6
#define row_total_less 13



int** reserva_memoria(int tamFila, int tamColum);
void imprimirMatriz(int tamFila, int tamColum, int **matriz);
void liberar_memoria(int **matriz, int tamFila);
//int tam_fichero(char *nombre_fichero);

//void find_mltiply_numbers(int &tamColum, int &tamFila, int tam);

int main(int argc, char *argv[]) {



    if(argc != 2) {
        printf("Numero de parametros incorrectos\n");
        printf("Solo debe introducir el nombre del fichero\n");
        printf("Introduce 'fichero1.bin' o'fichero2.bin'\n");
        return -1;
    }

    if(strcmp(argv[1], "fichero1.bin") != 0 && strcmp(argv[1], "fichero2.bin") != 0) {
        printf("Parametros incorrectos\n");
        printf("Introduce 'fichero1.bin' o 'fichero2.bin'\n");
        return -1;
    }
    

    FILE *fichero = fopen(argv[1], "rb");

    if(fichero == NULL) {
        printf("Error al abrir el fichero\n");
        return -1;
    }

    int tam = 0;
    int tamColum, tamFila;
    fseek(fichero, 0, SEEK_END);
    tam = ftell(fichero)/sizeof(int);
    fseek(fichero, 0, 0);
    
    //printf("El tamaño del archivo es: %d\n", tam);  

    tamColum = tamFila = sqrt(tam);
    //printf("\nColum: %d \nFila: %d\n", tamColum, tamFila);

    int **matriz = reserva_memoria(tamFila, tamColum);

    for(int i = 0; i < tamFila; i++) fread(matriz[i], sizeof(int), tamColum, fichero);



    int fila_reducida = tamFila - row_less_fr - row_less_l;
    int colum_reducida = tamColum - clmn_less_fr - clmn_less_l;

    int **matriz_reducida = reserva_memoria(fila_reducida, colum_reducida);

    int aux = 0;
    for(int i = 10; i < tamFila - row_less_l; i++) {
        memcpy(matriz_reducida[aux], matriz[i] + (clmn_less_fr), sizeof(int) * colum_reducida);
        aux++;
    }

    //imprimirMatriz(tamFila, tamColum, matriz);
    imprimirMatriz(fila_reducida, colum_reducida, matriz_reducida);
    
    FILE *fichero_matriz_reducida = fopen("matriz_reducida.bin", "wb");

    if (fichero_matriz_reducida == NULL) {
        printf("Error al abrir el fichero donde se iba a escribir la matriz reducida\n");
        return -1;
    }

    for(int i = 0; i < fila_reducida; i++) 
        fwrite(matriz_reducida[i], sizeof(int), colum_reducida, fichero_matriz_reducida);

    




    int tam_vector_reducido = (fila_reducida - row_less_fr - row_less_l) * (colum_reducida - clmn_less_fr - clmn_less_l);



    int *vector_reducido = (int *) malloc(tam_vector_reducido * sizeof(int));
    //Eliminamos de nuevo las 10 primeras filas y las 3 ultimas
    //Eliminamos de nuevo las 7 primeras filas y las 6 ultimas
    //Se usa aritmetica de punteros para mover el puntero del vector a la posicion que queremos
    //En el segundo parametro tambien se usa aritmetica de punteros para mover el puntero de las columnas de la matriz
    for(int i = 10; i < fila_reducida - row_less_l ; i++) {
        memcpy(vector_reducido + ( (i - 10) * (colum_reducida - row_total_less)), matriz_reducida[i] + (clmn_less_fr), sizeof(int)* (colum_reducida - row_total_less));
    }
    
    free(vector_reducido);
    liberar_memoria(matriz, tamFila);
    liberar_memoria(matriz_reducida, fila_reducida);

}
int** reserva_memoria(int tamFila, int tamColum) {
    int **matriz = (int**) malloc(tamFila * sizeof(int*));
    for(int i = 0; i < tamFila; i++) matriz[i] = (int*) malloc(tamColum * sizeof(int));

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