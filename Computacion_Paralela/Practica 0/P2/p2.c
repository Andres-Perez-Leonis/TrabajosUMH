#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void imprimirMatriz(int tamFila, int tamColum, double **matriz);

int main(int argc, char *argv[]) {
    FILE *fichero, *fEscribir;
    double **matrizEE, **matrizFF;
    double numeros[10];
    int tamFila, tamColum;
    unsigned long long int direccion;

    if(argc == 2) 
        if (strcmp(argv[1], "2x5") == 0) {
            tamFila = 2;
            tamColum= 5;
        } else if (strcmp(argv[1], "5x2") == 0){
            tamFila = 5;
            tamColum= 2;
        } else {
            printf("No has escrito una opcion valida.\n");
            return -1;
        }
    else {
        printf("Parametros incorrectos\n");
        printf("Introduce '5x2' o '2x5'");
        return -1;
    }
    //Abrimos los archivos

    fichero = fopen("datos10dobles.bin", "rb");
    fEscribir = fopen("Dmemoria.txt", "w");

    if(fichero != NULL || fEscribir != NULL) fread(numeros, sizeof(double), 10, fichero);
    else{
        printf("\nError abriendo el archivo\n");
        fclose(fichero);
        fclose(fEscribir);
        return -1;
    }

    matrizEE = (double**) malloc(tamFila * sizeof(double*));
    matrizFF = (double**) malloc(tamFila * sizeof(double*));
    for(int i = 0; i < tamFila; i++) {    
        matrizEE[i] = (double*) malloc(tamColum * sizeof(double));
        matrizFF[i] = (double*) malloc(tamColum * sizeof(double));
    }

    int num = 0;
    for(int i = 0; i < tamFila; i++) {
        for(int j = 0; j < tamColum ; j++){
            matrizEE[i][j] = numeros[num];
            num++;
        }
    }

    fseek(fichero, 0, 0) ;

    for(int i = 0; i < tamFila; i++) {
        fread(matrizFF[i], sizeof(double), tamColum, fichero);
    }

    imprimirMatriz(tamFila, tamColum, matrizEE);
    imprimirMatriz(tamFila, tamColum, matrizFF);

    fclose(fichero);

    
    for (int i = 0; i < tamFila; i++){
        direccion = &matrizEE[i][0];
        fprintf(fEscribir, "Dirección matrizEE (Pos %d:0): %llu\n", i, 0, direccion);
        direccion = &matrizEE[i][tamColum-1];
        fprintf(fEscribir, "Dirección matrizEE (Pos %d:%d): %llu\n", i, tamColum-1, direccion);
    }

    fprintf(fEscribir, "\n");

    for (int i = 0; i < tamFila; i++){
        direccion = &matrizFF[i][0];
        fprintf(fEscribir, "Dirección matrizFF (Pos %d:0): %llu\n", i, 0, direccion);
        direccion = &matrizFF[i][tamColum-1];
        fprintf(fEscribir, "Dirección matrizFF (Pos %d:%d): %llu\n", i, tamColum-1, direccion);
    }

    fclose(fEscribir);
    
    for (int i = 0; i < tamFila; i++) {   
        free(matrizEE[i]);
        free(matrizFF[i]);
    }
    free(matrizEE);
    free(matrizFF);


    return 0;
}

void imprimirMatriz(int tamFila, int tamColum, double **matriz) {
    for(int i = 0; i < tamFila; i++) {
        for(int j = 0; j < tamColum ;j++){
            printf("Posicion %d:%d = %d\n" , i, j, matriz[i][j]);
        }
        printf("\n");
    }
}