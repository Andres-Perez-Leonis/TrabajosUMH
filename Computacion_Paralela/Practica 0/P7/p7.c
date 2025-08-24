#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <time.h>


void imprimirMatriz(int tamFila, int tamColum, unsigned short int **matriz);
void liberar_memoria(unsigned short int **matriz, int tamFila);

int main(int argc, char *argv[]) {
    
    if(argc != 4) {
        printf("Numero de parametros incorrecto\n");
        printf("Debes introducir 3 parametros: Numero de filas Numero de columnas, Numero de divisiones\n");
        printf("Numero de filas y numero de columnas < 1000\n");
        printf("Numero de divisiones [2,5]");
        return -1;
    }

    if(isdigit(*argv[1]) == 0 || isdigit(*argv[2]) == 0 || isdigit(*argv[3]) == 0) {
        printf("Los parametros introducidos deben ser numeros enteros\n");
        return -1;
    }

    int nFilas = atoi(argv[1]);
    int nColum = atoi(argv[2]);
    int nDiv = atoi(argv[3]);

    printf("filas: %d columnas: %d div: %d\n", nFilas, nColum, nDiv);

    if(nFilas % nDiv == 1) {
        printf("El numero de filas debe ser divisible por el numero de divisiones");
        return -1;
    }

    if(nColum == nFilas) {
        printf("La matriz no debe ser cuadrada\n");
        return -1;
    }
    
    if(nDiv < 2 || nDiv > 5) {
        printf("El tercer parametro debe estar entre [2,5]\n");
        return -1;
    }

    if(nColum > 1000 || nFilas > 1000) {
        printf("El nuemro de filas y de columnas debe ser menor a 1000\n");
        return -1;
    }

    unsigned short int **matriz = (unsigned short int **) malloc(nFilas*sizeof(unsigned short int*));
    for(int i = 0; i < nFilas; i++) matriz[i] = malloc(nColum*sizeof(unsigned short int));

    if(matriz == NULL || matriz[0] == NULL) {
        printf("Error al reservar memoria\n");
        return -1;
    }

    srand(time(NULL));
    printf("NUMERO: %d", rand() % 65535);
    for(int i = 0; i < nFilas; i++) {
        for(int j = 0; j < nColum; j++) 
            matriz[i][j] = rand() % 65535;
    }

    printf("1\n");
    int fila_bloque = nFilas/nDiv;
    int sumaMaximos = 0;
    for(int i = 0; i < nDiv; i++) {
        unsigned short int max = 0;
        for(int j = i * fila_bloque; j < (i+1)*fila_bloque; j++)
            for(int k = 0; k < nColum; k++)
                if(max < matriz[j][k]) max = matriz[j][k];
        sumaMaximos += max;
    }

    liberar_memoria(matriz ,nFilas);
    printf("La suma de maximos es: %d\n", sumaMaximos);
    
    return 0;

}

void imprimirMatriz(int tamFila, int tamColum, unsigned short int **matriz) {
    for(int i = 0; i < tamFila; i++) {
        for(int j = 0; j < tamColum ;j++){
            printf("Posicion %d:%d = %d\n" , i, j, matriz[i][j]);
        }
        printf("\n");
    }
}

void liberar_memoria(unsigned short int **matriz, int tamFila) {
    for (int i = 0; i < tamFila; i++) {   
        free(matriz[i]);
    }
    free(matriz);
}