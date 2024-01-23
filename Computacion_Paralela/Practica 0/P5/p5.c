#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

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

    size_t tamLectura = 256 * 1024; // Tamaño a leer de fichero (256KB)
    unsigned char *vector = (unsigned char*) malloc(tamLectura);

    size_t tamLeidos = fread(vector, 1, tamLectura, fichero);
    if(tamLeidos != tamLectura) {
        printf("Error al leer el fichero\n");
        return -1;
    }

    fclose(fichero);

    int valor = atoi(argv[1]);
    int nElementos = tamLectura/sizeof(unsigned char);
    int menores_iguales = 0;
    for(int i = 0; i < nElementos; i++) {
        if(*(vector + i) <= valor) menores_iguales++;
    }

    printf("El numero de elementos menores o iguales al valor introducido son: %d\n", menores_iguales);

    free(vector);
}