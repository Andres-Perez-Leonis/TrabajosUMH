#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

#define nDivisiones 10
#define nParciales 10


int max_bloque(int *vector, int comienzo, int limite, int max);
int min_bloque(int *vector, int comienzo, int limite, int min);
double *escalado(int *vector, int comienzo, int limite, int max, int min, double *destino);


int main(int argc, char *argv[]) {

    srand(time(NULL));
    int *vectorCompletoEnteros;
    //Nos aseguramos que como minimo tenga un tamaño de 10000000
    int dimension = 10000000 + abs(rand() % 9000000 + 1);

    vectorCompletoEnteros = malloc(dimension * sizeof(int));
    
    for(int i = 0; i < dimension; i++)
        vectorCompletoEnteros[i] = abs(rand() % 10000 + 1);

    int tam_Divisiones = dimension / nDivisiones;

    int divisiones_sobreantes = dimension % nDivisiones;

    int aux[nParciales];
    for(int i = 0; i < nParciales; i++) {
        if(divisiones_sobreantes > i) aux[i] = 1;
        else aux[i] = 0;
    }

    double **vectoresParcialDoubles = malloc(nParciales * sizeof(double));
    for(int i = 0; i < nParciales; i++)
        vectoresParcialDoubles[i] = malloc((tam_Divisiones + aux[i]) * sizeof(double));

    int max = 0;
    //Buscamos el maximo del primer grupo
    //Bloque 0
    max = max_bloque(vectorCompletoEnteros, 0, tam_Divisiones + aux[0], max);
    //Bloque 2
    max = max_bloque(vectorCompletoEnteros, tam_Divisiones*2, tam_Divisiones*3 + aux[2], max);
    //Bloque 3
    max = max_bloque(vectorCompletoEnteros, tam_Divisiones*3, tam_Divisiones*4 + aux[3], max);
    //Bloque 5
    max = max_bloque(vectorCompletoEnteros, tam_Divisiones*5, tam_Divisiones*6 + aux[5], max);
    //Bloque 8
    max = max_bloque(vectorCompletoEnteros, tam_Divisiones*8, tam_Divisiones*9 + aux[8], max);


    
    int min = 0;
    //Buscamos el minimo del primer grupo
    //Bloque 0
    min = min_bloque(vectorCompletoEnteros, 0, tam_Divisiones + aux[0], min);
    //Bloque 2
    min = min_bloque(vectorCompletoEnteros, tam_Divisiones*2, tam_Divisiones*3 + aux[2], min);
    //Bloque 3
    min = min_bloque(vectorCompletoEnteros, tam_Divisiones*3, tam_Divisiones*4 + aux[3], min);
    //Bloque 5
    min = min_bloque(vectorCompletoEnteros, tam_Divisiones*5, tam_Divisiones*6 + aux[5], min);
    //Bloque 8
    min = min_bloque(vectorCompletoEnteros, tam_Divisiones*8, tam_Divisiones*9 + aux[8], min);

    

    vectoresParcialDoubles[0] = escalado(vectorCompletoEnteros, 0, tam_Divisiones + aux[0], max, min, vectoresParcialDoubles[0]);
    vectoresParcialDoubles[2] = escalado(vectorCompletoEnteros, tam_Divisiones*2, tam_Divisiones*3 + aux[2], max, min, vectoresParcialDoubles[2]);
    vectoresParcialDoubles[3] = escalado(vectorCompletoEnteros, tam_Divisiones*3, tam_Divisiones*4 + aux[3], max, min, vectoresParcialDoubles[3]);
    vectoresParcialDoubles[5] = escalado(vectorCompletoEnteros, tam_Divisiones*5, tam_Divisiones*6 + aux[5], max, min, vectoresParcialDoubles[5]);
    vectoresParcialDoubles[8] = escalado(vectorCompletoEnteros, tam_Divisiones*8, tam_Divisiones*9 + aux[8], max, min, vectoresParcialDoubles[8]);

    //Buscamos el maximo del segundo grupo
    //Bloque 1
    max = max_bloque(vectorCompletoEnteros, tam_Divisiones, tam_Divisiones*2 + aux[1], max);
    //Bloque 4
    max = max_bloque(vectorCompletoEnteros, tam_Divisiones*4, tam_Divisiones*5 + aux[4], max);

    //Buscamos el minimo del segundo grupo
    //Bloque 1
    max = max_bloque(vectorCompletoEnteros, tam_Divisiones, tam_Divisiones*2 + aux[1], min);
    //Bloque 4
    max = max_bloque(vectorCompletoEnteros, tam_Divisiones*4, tam_Divisiones*5 + aux[4], min);

    vectoresParcialDoubles[1] = escalado(vectorCompletoEnteros, tam_Divisiones, tam_Divisiones*2 + aux[1], max, min, vectoresParcialDoubles[1]);
    vectoresParcialDoubles[4] = escalado(vectorCompletoEnteros, tam_Divisiones*4, tam_Divisiones*5 + aux[4], max, min, vectoresParcialDoubles[4]);
    
    //Buscamos  el maximo del ultimo grupo
    //Bloque 6
    max = max_bloque(vectorCompletoEnteros, tam_Divisiones*6, tam_Divisiones*7 + aux[6], max);
    //Bloque 7
    max = max_bloque(vectorCompletoEnteros, tam_Divisiones*7, tam_Divisiones*8 + aux[7], max);
    //Bloque 9
    max = max_bloque(vectorCompletoEnteros, tam_Divisiones*9, tam_Divisiones*10 + aux[9], max);

    //Buscamos  el minimo del ultimo grupo
    //Bloque 6
    min = min_bloque(vectorCompletoEnteros, tam_Divisiones*6, tam_Divisiones*7 + aux[6], min);
    //Bloque 7
    min = min_bloque(vectorCompletoEnteros, tam_Divisiones*7, tam_Divisiones*8 + aux[7], min);
    //Bloque 9
    min = min_bloque(vectorCompletoEnteros, tam_Divisiones*9, tam_Divisiones*10 + aux[9], min);


    vectoresParcialDoubles[6] = escalado(vectorCompletoEnteros, tam_Divisiones*6, tam_Divisiones*7 + aux[6], max, min, vectoresParcialDoubles[6]);
    vectoresParcialDoubles[7] = escalado(vectorCompletoEnteros, tam_Divisiones*7, tam_Divisiones*8 + aux[7], max, min, vectoresParcialDoubles[7]);
    vectoresParcialDoubles[9] = escalado(vectorCompletoEnteros, tam_Divisiones*9, tam_Divisiones*10 + aux[9], max, min, vectoresParcialDoubles[9]);
    /*
    for(int i = 0; i < 5; i++){
        printf("vectorParcial0 [%d]: %lf\n", i, vectoresParcialDoubles[0][i]);
        printf("vectorParcial1 [%d]: %lf\n", i, vectoresParcialDoubles[1][i]);
        printf("vectorParcial2 [%d]: %lf\n", i, vectoresParcialDoubles[2][i]);
        printf("vectorParcial3 [%d]: %lf\n", i, vectoresParcialDoubles[3][i]);
        printf("vectorParcial4 [%d]: %lf\n", i, vectoresParcialDoubles[4][i]);
        printf("vectorParcial5 [%d]: %lf\n", i, vectoresParcialDoubles[5][i]);
        printf("vectorParcial6 [%d]: %lf\n", i, vectoresParcialDoubles[6][i]);
        printf("vectorParcial7 [%d]: %lf\n", i, vectoresParcialDoubles[7][i]);
        printf("vectorParcial8 [%d]: %lf\n", i, vectoresParcialDoubles[8][i]);
        printf("vectorParcial9 [%d]: %lf\n", i, vectoresParcialDoubles[9][i]);
    }
    */

    for(int i = 0; i < nParciales; i++) free(vectoresParcialDoubles[i]);
    free(vectoresParcialDoubles);

    free(vectorCompletoEnteros);
    
    return 0;
    
}

int min_bloque(int *vector, int comienzo, int limite, int min) {
    for(int i = comienzo; i < limite; i++)
        if(min > vector[i]) min = vector[i];

    return min;
}

int max_bloque(int *vector, int comienzo, int limite, int max) {
    for(int i = comienzo; i < limite; i++)
        if(max < vector[i]) max = vector[i];

    return max;
}

double *escalado(int *vector, int comienzo, int limite, int max, int min, double *destino){
    int j = 0;
    double division;
    
    for(int i = comienzo; i < limite; i++) {
        division = (double) (vector[i] - min) / (max - min);
        destino[j] = division;
        j++; 
    }
    return destino;
}