#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

#define nDivisiones 10


int max_bloque(int *vector, int limite, int comienzo);


int main(int argc, char *argv[]) {

    srand(time(NULL));
    int *vectorCompletoEnteros;
    //Nos aseguramos que como minimo tenga un tamaño de 10000000
    int dimension = 10000000 + abs(rand() % 9000000 + 1);

    vectorCompletoEnteros = malloc(dimension * sizeof(int));
    
    for(int i = 0; i < dimension; i++) {
        vectorCompletoEnteros[i] = abs(rand() % 10000 + 1);
        /*
        int numero = rand() % 10000;
        if(numero > 0) vectorCompletoEnteros[i] = numero;
        else vectorCompletoEnteros[i] = -numero;
        */
    }

    int tam_Divisiones = dimension / nDivisiones;

    int divisiones_sobreantes = dimension % nDivisiones;

    int aux[10];
    for(int i = 0; i < 10; i++) {
        if(divisiones_sobreantes > i) aux[i] = 1;
        else aux[i] = 0;
    }

    double *vectorParcialDoubles0 = malloc(sizeof(double) * (tam_Divisiones + aux[0]));
    double *vectorParcialDoubles1 = malloc(sizeof(double) * (tam_Divisiones + aux[1]));
    double *vectorParcialDoubles2 = malloc(sizeof(double) * (tam_Divisiones + aux[2]));
    double *vectorParcialDoubles3 = malloc(sizeof(double) * (tam_Divisiones + aux[3]));
    double *vectorParcialDoubles4 = malloc(sizeof(double) * (tam_Divisiones + aux[4]));
    double *vectorParcialDoubles5 = malloc(sizeof(double) * (tam_Divisiones + aux[5]));
    double *vectorParcialDoubles6 = malloc(sizeof(double) * (tam_Divisiones + aux[6]));
    double *vectorParcialDoubles7 = malloc(sizeof(double) * (tam_Divisiones + aux[7]));
    double *vectorParcialDoubles8 = malloc(sizeof(double) * (tam_Divisiones + aux[8]));
    double *vectorParcialDoubles9 = malloc(sizeof(double) * (tam_Divisiones + aux[9]));

    if(vectorParcialDoubles0 == NULL) {
        printf("Fallo al reservar memoria\n");
        return 0;}
    //memcpy(vectorParcialDoubles0, vectorCompletoEnteros, sizeof(int) * tam_Divisiones);


 
    int maximo = max_bloque(vectorCompletoEnteros, tam_Divisiones + aux[0], 0);
    printf("Maximo: %d\n", maximo);
    
    double division;

    //Primer bloque (Bloque 0)
    for(int i = 0; i < tam_Divisiones + aux[0]; i++){
        division =  (double)  vectorCompletoEnteros[i] / maximo;
        vectorParcialDoubles0[i] = division;
    }

    //Segundo bloque (Bloque 1)
    maximo = max_bloque(vectorCompletoEnteros, tam_Divisiones*2 + aux[1], tam_Divisiones);
    int j = 0;
    for(int i = tam_Divisiones + aux[0]; i < tam_Divisiones*2 + aux[1]; i++){
        division =  (double)  vectorCompletoEnteros[i] / maximo;
        vectorParcialDoubles1[j] = division;
        j++;
    }
    
    //Tercer bloque (Bloque 2)
    maximo = max_bloque(vectorCompletoEnteros, tam_Divisiones*3 + aux[2], tam_Divisiones*2);
    j = 0;
    for(int i = tam_Divisiones*2 + aux[1]; i < tam_Divisiones*3 + aux[2]; i++){
        division =  (double)  vectorCompletoEnteros[i] / maximo;
        vectorParcialDoubles2[j] = division;
        j++;
    }

    //Cuarto bloque (Bloque 3)
    maximo = max_bloque(vectorCompletoEnteros, tam_Divisiones*4 + aux[3], tam_Divisiones*3);
    j = 0;
    for(int i = tam_Divisiones*3 + aux[2]; i < tam_Divisiones*4 + aux[3]; i++){
        division =  (double)  vectorCompletoEnteros[i] / maximo;
        vectorParcialDoubles3[j] = division;
        j++;
    }

    //Quinto bloque (Bloque 4)
    maximo = max_bloque(vectorCompletoEnteros, tam_Divisiones*5 + aux[4], tam_Divisiones*4);
    j = 0;
    for(int i = tam_Divisiones*4 + aux[3]; i < tam_Divisiones*5 + aux[4]; i++){
        division =  (double)  vectorCompletoEnteros[i] / maximo;
        vectorParcialDoubles4[j] = division;
        j++;
    }

    //Sexto bloque (Bloque 5)
    maximo = max_bloque(vectorCompletoEnteros, tam_Divisiones*6 + aux[5], tam_Divisiones*5);
    j = 0;
    for(int i = tam_Divisiones*5 + aux[4]; i < tam_Divisiones*6 + aux[5]; i++){
        division =  (double)  vectorCompletoEnteros[i] / maximo;
        vectorParcialDoubles5[j] = division;
        j++;
    }

    //Septimo bloque (Bloque 6)
    maximo = max_bloque(vectorCompletoEnteros, tam_Divisiones*7 + aux[6], tam_Divisiones*6);
    j = 0;
    for(int i = tam_Divisiones*6 + aux[5]; i < tam_Divisiones*7 + aux[6]; i++){
        division =  (double)  vectorCompletoEnteros[i] / maximo;
        vectorParcialDoubles6[j] = division;
        j++;
    }

    //Octavo bloque (Bloque 7)
    maximo = max_bloque(vectorCompletoEnteros, tam_Divisiones*8 + aux[7], tam_Divisiones*7);
    j = 0;
    for(int i = tam_Divisiones*7 + aux[6]; i < tam_Divisiones*8 + aux[7]; i++){
        division =  (double)  vectorCompletoEnteros[i] / maximo;
        vectorParcialDoubles7[j] = division;
        j++;
    }
    
    //Noveno bloque (Bloque 8)
    maximo = max_bloque(vectorCompletoEnteros, tam_Divisiones*9 + aux[8], tam_Divisiones*8);
    j = 0;
    for(int i = tam_Divisiones*8 + aux[7]; i < tam_Divisiones*9 + aux[8]; i++){
        division =  (double)  vectorCompletoEnteros[i] / maximo;
        vectorParcialDoubles8[j] = division;
        j++;
    }

    //Decimo bloque (Bloque 9)
    maximo = max_bloque(vectorCompletoEnteros, tam_Divisiones*10 + aux[9], tam_Divisiones*9);
    j = 0;
    for(int i = tam_Divisiones*9 + aux[8]; i < tam_Divisiones*10 + aux[9]; i++){
        division =  (double)  vectorCompletoEnteros[i] / maximo;
        vectorParcialDoubles9[j] = division;
        j++;
    }

    /*
    for(int i = 0; i < 5; i++){
        printf("vectorParcial0 [%d]: %lf\n", i, vectorParcialDoubles0[i]);
        printf("vectorParcial1 [%d]: %lf\n", i, vectorParcialDoubles1[i]);
        printf("vectorParcial2 [%d]: %lf\n", i, vectorParcialDoubles2[i]);
        printf("vectorParcial3 [%d]: %lf\n", i, vectorParcialDoubles3[i]);
        printf("vectorParcial4 [%d]: %lf\n", i, vectorParcialDoubles4[i]);
        printf("vectorParcial5 [%d]: %lf\n", i, vectorParcialDoubles5[i]);
        printf("vectorParcial6 [%d]: %lf\n", i, vectorParcialDoubles6[i]);
        printf("vectorParcial7 [%d]: %lf\n", i, vectorParcialDoubles7[i]);
        printf("vectorParcial8 [%d]: %lf\n", i, vectorParcialDoubles8[i]);
        printf("vectorParcial9 [%d]: %lf\n", i, vectorParcialDoubles9[i]);
    }
   */


    free(vectorParcialDoubles0);
    free(vectorParcialDoubles1);
    free(vectorParcialDoubles2);
    free(vectorParcialDoubles3);
    free(vectorParcialDoubles4);
    free(vectorParcialDoubles5);
    free(vectorParcialDoubles6);
    free(vectorParcialDoubles7);
    free(vectorParcialDoubles8);
    free(vectorParcialDoubles9);
    free(vectorCompletoEnteros);


   return 0;
}

int max_bloque(int *vector, int limite, int comienzo) {
    int max = 0;
    for(int i = comienzo; i < limite; i++)
        if(max < vector[i]) max = vector[i];

    return max;
}