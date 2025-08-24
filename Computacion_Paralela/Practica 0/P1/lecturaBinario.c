#include "stdio.h"


int main() {
    FILE *fichero;
    FILE *fichero10decimales, *fichero15decimales;
    double numero[10];
    //Abrimos los archivos
    fichero = fopen("datos10dobles.bin", "rb");
    fichero10decimales = fopen("10decimales.txt", "w");
    fichero15decimales = fopen("15decimales.txt", "w");
    //Comprobacion de nulos
    if (fichero != NULL || fichero10decimales != NULL || 
        fichero15decimales != NULL) {
        //Lectura de fichero
        fread(numero, sizeof(double), 10, fichero);
        for(int i = 0; i < 10; i++) {
            //Escritura de fichero con un formato definido
            fprintf(fichero10decimales, "%.10f;", numero[i]);
            fprintf(fichero15decimales, "%.15f\n", numero[i]);
        }
    } else {
        printf("Error al abrir alguno de los archivos");
    }
    //Cerrar ficheros
    fclose(fichero);
    fclose(fichero10decimales);
    fclose(fichero15decimales);
    return 0;
}