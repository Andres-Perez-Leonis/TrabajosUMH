#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define size 512

unsigned char** memory_reserve(unsigned char **matriz);
void free_memory(unsigned char **matriz);
unsigned char** read_document(char *name, unsigned char** matriz);

int main() {
    unsigned char **matriz = read_document("fichero2.bin", matriz);
    if(matriz == NULL) return -1;

    unsigned char *vector_media_rows = (unsigned char *) malloc(sizeof(unsigned char)*size);
    unsigned char *vector_media_columns = (unsigned char *) malloc(sizeof(unsigned char)* (size/2));

    int media_rows = 0;

    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) media_rows += matriz[i][j];
        media_rows /= size;
        vector_media_rows[i] = media_rows;
        media_rows = 0;
    }


    //for(int i = 0; i < size; i++) printf("Media de la fila %d: %d\n", i, vector_media_rows[i]);


    int media_columns = 0;
    int aux = 0;
    for(int i = 0; i < size; i += 2) {
        for(int j = 0; j < size; j++) media_columns += matriz[j][i];
        media_columns /= size;
        vector_media_columns[aux] = media_columns;
        media_columns = 0;
        aux++;

    }

    int max_column = 0, max_row = 0;
    int min_column = 9999999, min_row = 999999;
    for(int i = 0; i < size; i++) {
        if(max_row < vector_media_rows[i]) max_row = vector_media_rows[i];
        if(min_row > vector_media_rows[i]) min_row = vector_media_rows[i];
        if(max_column < vector_media_columns[i] && i < size/2) max_column = vector_media_columns[i];
        if(min_column > vector_media_columns[i] && i < size/2) min_column = vector_media_columns[i];
    }
    

    FILE *resultado = fopen("resultado.txt", "w");
    fprintf(resultado, "Valor maximo de media de las filas: %d\n", max_row);
    fprintf(resultado, "Valor minimo de media de las filas: %d \n", min_row);
    fprintf(resultado, "Valor maximo de media de las columnas: %d \n", max_column);
    fprintf(resultado, "Valor minimo de media de las columnas: %d \n", min_column);
    fclose(resultado);
    //for(int i = 0; i < size/2; i++) printf("Media de la columnas %d: %d\n", i, vector_media_columns[i]);


    free(vector_media_rows);
    free(vector_media_columns);
    free_memory(matriz);
    return 0;
    
}



void free_memory(unsigned char **matriz) {
    for (int i = 0; i < size; i++) {   
        free(matriz[i]);
    }
    free(matriz);
}

unsigned char** read_document(char *name, unsigned char** matriz) {
    FILE *fichero = fopen(name, "rb");

    if(fichero == NULL) {
        printf("Error al abrir el fichero\n");
        return NULL;
    }

    matriz = memory_reserve(matriz);
    if(matriz == NULL) return NULL;

    for(int i = 0; i < size; i++) fread(matriz[i], sizeof(unsigned char), size, fichero);
    fclose(fichero);
    return matriz;
}



unsigned char** memory_reserve(unsigned char **matriz) {
    matriz = (unsigned char**) malloc(size * sizeof(unsigned char*));
    for(int i = 0; i < size; i++) matriz[i] = (unsigned char*) malloc(size * sizeof(unsigned char));

    if(matriz == NULL || matriz[0] == NULL) {
        printf("No se ha podido realizar la reserva de memoria para la matriz\n");
        return NULL;
    }
    return matriz;
}