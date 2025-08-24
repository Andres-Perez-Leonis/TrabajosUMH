#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <ctype.h>
#include <math.h>
#include <unistd.h>

#define PARAM_ERROR 0
#define FILE_ERROR 1
#define MEMORY_RESERVE_ERROR 2
#define TAM_ERROR 3
#define FILT_NON_DEFINED 4


double **reserva_memoria(double **matriz, int anchura, int altura);
void normalizar_vector(double *vector, int altura);
void obtener_valores(double **matriz, int anchura, int altura, char* nombre);
void multiplicacion_matrices(double **matriz_1, int n_filas_1, int n_columnas_1, double **matriz_2, int n_filas_2, int n_columnas_2, double **matriz_resultado) ;
void show_error(int error);
double obtener_Multiplicacion(double **matriz_1, double **matriz_2, int tam, int pos_i, int pos_j);

int main(int argc, char *argv[]) {

    
    if(argc != 4) show_error(PARAM_ERROR);

    if( isdigit(*argv[1]) != 0 || isdigit(*argv[2]) == 0 || isdigit(*argv[3]) == 0) show_error(PARAM_ERROR);

    
    double **matriz_M, **vectores_iteracion, **resultado, aux = 0;
    int nIteraciones = atoi(argv[2]); //Filas
    int tam_N = atoi(argv[3]); //Columnas


    matriz_M = reserva_memoria(matriz_M, tam_N, tam_N);
    vectores_iteracion = reserva_memoria(vectores_iteracion, tam_N, nIteraciones);
    //aux = malloc(tam_N * sizeof(double));
    resultado = reserva_memoria(resultado, tam_N, nIteraciones);

    obtener_valores(matriz_M, tam_N, tam_N, argv[1]);
    for(int i = 0; i < tam_N; i++)
        vectores_iteracion[0][i] = 1.0;

    //Primere iteracion X1
    for(int i = 0; i < tam_N; i++) {
        vectores_iteracion[1][i] = obtener_Multiplicacion(matriz_M, vectores_iteracion, tam_N, i, 0);
    }
    normalizar_vector(vectores_iteracion[1], tam_N);

    for(int i = 2; i < nIteraciones; i++) {
        for(int j = 0; j < tam_N; j++) {
           aux = obtener_Multiplicacion(matriz_M, vectores_iteracion, tam_N, j, i - 1);
           vectores_iteracion[i][j] = vectores_iteracion[i-1][j] - aux;
        }
        normalizar_vector(vectores_iteracion[i], tam_N);
    }

    // for(int i = 0; i < nIteraciones; i++)
    //     for(int j = 0; j < tam_N; j++)
    //         printf("Valor pos [%d][%d]: %llf\n", i, j, vectores_iteracion[i][j]);

    for(int i = 0; i < nIteraciones; i++) {
        free(matriz_M[i]);
        free(resultado[i]);
    }
    free(resultado);
    free(vectores_iteracion);
    free(matriz_M);
    return 0;
}


double obtener_Multiplicacion(double **matriz_1, double **matriz_2, int tam, int pos_i, int pos_j){
    double aux = 0;
    for(int k = 0; k < tam; k++)
        aux += matriz_1[pos_i][k] * matriz_2[pos_j][k];

    return aux;
}



/*
    * obtener_valores *
    Funcion que obtiene los valores para las iteraciones, si no encuentra el documento genera los numeros
    Parametros:
        - matriz --> Variable doble puntero donde se guardaran todos los valores
        - anchura --> Variable que determina el ancho de la matriz
        - altura --> Variable que determina la altura de la matriz
        - nombre --> Nombre del fichero donde obtener los datos
*/


void obtener_valores(double **matriz, int anchura, int altura, char* nombre) {
    FILE *fichero = fopen(nombre, "rb");
    int aux = 1;
    if(fichero == NULL) {
        srand(getpid());
        for(int i = 0; i < altura; i++)
            for(int j = 0; j < anchura; j++) 
                if(i == j) matriz[i][j] = 1.0;
                else matriz[i][j] = ((double) rand() / RAND_MAX) * 0.01;
    } else {
        for(int i = 0; i < altura; i++){
            fread(matriz[i], sizeof(double), anchura, fichero);
        }
    }
}


/*
    * normalizar_vector *
    Funcion que normaliza los valores de un vector
    Parametros:
        - vector --> Valores a normalizar
        - anchura --> Numero de elementos que hay que normalizar
*/

void normalizar_vector(double *vector, int anchura) {
    double valor = 0;
    for(int i = 0; i < anchura; i++)
        valor += (vector[i] * vector[i]);
    valor = sqrt(valor);
    printf("Norma: %llf\n", valor);
    for(int i = 0; i < anchura; i++)
            vector[i] /= valor;
}


double **reserva_memoria(double **matriz, int anchura, int altura) {
    printf("Creo una matriz %dx%d\n", altura, anchura);
    matriz = malloc(altura * sizeof(double*));
    for(int i = 0; i < altura; i++) 
        matriz[i] = malloc(anchura * sizeof(double));

    if(matriz == NULL || matriz[0] == NULL)
        show_error(MEMORY_RESERVE_ERROR);    

    return matriz;
}


/*
    * show_error *
    Funcion para mostrar mensajes de error
    Parametros:
        - error (int): Variable para indicar el tipo de error

*/

void show_error(int error) {
    if(error == PARAM_ERROR) {
        printf("Error: Parametros incorrectos\n");
        printf("Son 3 parametros: \n[Nombre del fichero imagen]:String [Altura]:Entero positivo [Anchura]:Entero positivo\n");
    }
    else if(error == FILE_ERROR) {
        printf("Error al abrir el archivo\n");
        printf("El nombre del archivo hay que colocarlo sin extension\n");
    }
    else if(error == MEMORY_RESERVE_ERROR) printf("Error al reservar memoria\n");
    else if(error == TAM_ERROR) {
        printf("Error: Dimensiones de matriz indicados incorrectos\n");
        printf("Se esta reservando matriz que pixeles hay en la imagen\n");
    }
    else if(error == FILT_NON_DEFINED) {
        printf("Error: Tipo de filtrado indicado no existente\n");
        printf("Posibles valores para [Tipo filtrado]:\n1 --> Filtrado por media\n2 --> Filtrado SOBEL\n3 --> Historiograma\n");
    }
    printf("Saliendo del programa.......");
    exit(0);
}
