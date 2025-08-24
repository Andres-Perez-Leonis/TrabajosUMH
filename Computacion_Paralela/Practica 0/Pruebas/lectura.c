#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s <filas>\n", argv[0]);
        return 1;
    }

    int filas = atoi(argv[1]);

    if (filas != 2 && filas != 5) {
        printf("El número de filas debe ser 2 o 5.\n");
        return 1;
    }

    FILE *archivoBinario = fopen("datos10dobles.bin", "rb");
    if (archivoBinario == NULL) {
        perror("Error al abrir el archivo binario");
        return 1;
    }

    double **matrizEE = (double **)malloc(filas * sizeof(double *));
    double **matrizFF = (double **)malloc(filas * sizeof(double *));

    for (int i = 0; i < filas; i++) {
        matrizEE[i] = (double *)malloc(2 * sizeof(double));
        matrizFF[i] = (double *)malloc(2 * sizeof(double));
    }

    // Leer los datos directamente en la matriz utilizando una única instrucción de lectura
    fread(matrizEE[0], sizeof(double), filas * 2, archivoBinario);
    for (int i = 0; i < filas; i++) {
        matrizFF[i][0] = matrizEE[i][0];
        matrizFF[i][1] = matrizEE[i][1];
    }

    fclose(archivoBinario);

    // Escribir la información en un archivo de texto
    FILE *archivoTexto = fopen("informacion.txt", "w");
    if (archivoTexto == NULL) {
        perror("Error al abrir el archivo de texto");
        return 1;
    }

    for (int i = 0; i < filas; i++) {
        fprintf(archivoTexto, "Fila %d:\n", i + 1);
        fprintf(archivoTexto, "Dirección del primer elemento: %llu\n", (unsigned long long int)&matrizEE[i][0]);
        fprintf(archivoTexto, "Dirección del último elemento: %llu\n", (unsigned long long int)&matrizEE[i][1]);
        fprintf(archivoTexto, "\n");
    }

    fclose(archivoTexto);

    // Liberar la memoria
    for (int i = 0; i < filas; i++) {
        free(matrizEE[i]);
        free(matrizFF[i]);
    }
    free(matrizEE);
    free(matrizFF);

    return 0;
}