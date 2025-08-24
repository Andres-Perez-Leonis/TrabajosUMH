#include <stdlib.h>
#include <stdio.h>

#define size 256 * 1024


void par_found_char(unsigned char *vector, int elementos);
void par_found_short_int(unsigned short int *vector, int elementos);
void par_found_int(unsigned int *vector, int elementos);
void positive_found_double(double *vector, int elementos);
void imprimir_datos(int elementos, int pares, unsigned long long int direccion[2]);

int main() {

    unsigned char *vector_char;

    int elementos = size/sizeof(unsigned char);

    FILE *fichero = fopen("fichero2.bin", "rb");

    if(fichero == NULL) {
        printf("Error al intentar abrir el documento\n");
        return -1;
    }

    vector_char = malloc(size);
    if(vector_char == NULL) {
        printf("Error al reservar memoria\n");
        return -1;
    }


    fread(vector_char, sizeof(unsigned char), size, fichero);

    par_found_char(vector_char, elementos);
    free(vector_char);

    unsigned short int *vector_short_int;
    elementos = size/sizeof(unsigned short int);

    vector_short_int = malloc(size);
    if(vector_short_int == NULL) {
        printf("Error al reservar memoria\n");
        return -1;
    }

    fseek(fichero, 0, 0);
    fread(vector_short_int, sizeof(unsigned short int), size, fichero);

    par_found_short_int(vector_short_int, elementos);
    free(vector_short_int);

    unsigned int *vector_int = malloc(size);
    if(vector_int == NULL) {
        printf("Error al reservar memoria\n");
        return -1;
    }

    elementos = size/sizeof(unsigned int);

    fseek(fichero, 0, 0);
    fread(vector_int, sizeof(unsigned int), size, fichero);
    par_found_int(vector_int, elementos);

    free(vector_int);

    double *vector_double;
    elementos = size/sizeof(double);
    vector_double = malloc(size);
    if (vector_double==NULL){
        printf ("Error al reservar memoria\n");
        return -1;
    }
    fseek(fichero, 0, 0);
    fread(vector_double, sizeof(double), size, fichero);

    fclose(fichero);
    
    positive_found_double(vector_double, elementos);
    
    free(vector_double);
    
    return 0;


}

void par_found_char(unsigned char *vector, int elementos) {    
    int pares = 0;
    unsigned long long int direccion[2];
    int aux = 0;

    for(int i = 0; i < elementos; i++)
        if(*(vector + i) % 2 == 0) {
            pares++;
            if(aux < 2) {
                direccion[aux] = (vector + i);
                aux;
            }
        }

    imprimir_datos(elementos, pares, direccion);
}

void par_found_short_int(unsigned short int *vector, int elementos) {    
    int pares = 0;
    unsigned long long int direccion[2];
    int aux = 0;

    for(int i = 0; i < elementos; i++)
        if(*(vector + i) % 2 == 0) {
            pares++;
            if(aux < 2) {
                direccion[aux] = (vector + i);
                aux;
            }
        }
    imprimir_datos(elementos, pares, direccion);
}

void par_found_int(unsigned int *vector, int elementos) {    
    int pares = 0;
    unsigned long long int direccion[2];
    int aux = 0;

    for(int i = 0; i < elementos; i++)
        if(*(vector + i) % 2 == 0) {
            pares++;
            if(aux < 2) {
                direccion[aux] = (vector + i);
                aux;
            }
        }

    imprimir_datos(elementos, pares, direccion);
}


void positive_found_double(double *vector, int elementos) {    
    int positive = 0;
    unsigned long long int direccion[2];
    int aux = 0;

    for(int i = 0; i < elementos; i++)
        if(*(vector + i) > 0) {
            positive++;
            if(aux < 2) {
                direccion[aux] = (vector + i);
                aux;
            }
        }
    printf("El numero total de elementos son: %d\n", elementos);
    printf("El numero de positivos es: %d\n", positive);
    printf("Direccion elemento 1: %llu\n", (direccion+1));
    printf("Direccion elemento 2: %llu\n", (direccion+2));
}

void imprimir_datos(int elementos, int pares, unsigned long long int direccion[2]){
    printf("El numero total de elementos son: %d\n", elementos);
    printf("El numero de pares es: %d\n", pares);
    printf("Direccion elemento 1: %llu\n", (direccion+1));
    printf("Direccion elemento 2: %llu\n", (direccion+2));
}