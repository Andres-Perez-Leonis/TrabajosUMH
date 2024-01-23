#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>
#include <ctype.h>
#include <limits.h>
#include <unistd.h>
#include <mpi.h>
 
#define PARAM_ERROR 0
#define FILE_ERROR 1
#define MEMORY_RESERVE_ERROR 2
#define TAM_ERROR 3


double obtener_Multiplicacion(double **matriz_1, double **matriz_2, int tam, int pos_i, int pos_j);
double obtener_sum_cuadrado(double *matriz, double tam);
void normalizar_vector(double *vector, int anchura, double suma);
void show_error(int error);
double **reserva_memoria(double **matriz, int anchura, int altura);
void obtener_valores(double **matriz, int anchura, int altura, char* nombre);




int main(int argc,char *argv[])
{


    /*
        Cosas que hay que comprobar sobre los parametros introducidos por el usuario
            - Que el numero de procesos no sea mayor al numero de filas indicada
            - Que los parametros que indican el tamaño y el numero de iteraciones es un numero y mayor que 0
            - Que esté el nombre del fichero como primer parametro
    */




    int nprocess, myrank;
    MPI_Status status;
    double tiempo_inicio, tiempo_final; 
    MPI_Init(&argc,&argv);
    //
    //    PROGRAMA A DESARROLLAR CON 
    //    LLAMADAS A RUTINAS MPI
    //
    MPI_Comm_size(MPI_COMM_WORLD,&nprocess);
    MPI_Comm_rank(MPI_COMM_WORLD,&myrank);

    double **matriz_M, **matriz_vect_iter;
    double prod_sum, sum, sum_general;
    int tam_N = 150, nIteraciones = 8 + 1;

    int exceso = tam_N % nprocess;

    int comp_proceso = tam_N / nprocess; //El numero de componentes del vector que debe hacer cada proceso

    int *n_comp_proceso = malloc(sizeof(double) * nprocess);
    int *comienzo_proceso = malloc(sizeof(double) * nprocess);
    
    comienzo_proceso[0] = 0;
    for(int i = 0; i < nprocess; i++) {
        n_comp_proceso[i] = comp_proceso;
        if(i != 0 && exceso > 0) {
            n_comp_proceso[i]++;
            exceso--;
        }
        if(i != 0) comienzo_proceso[i] = comienzo_proceso[i-1] + n_comp_proceso[i-1];

        printf("Valor de componentes proceso %d: %d\n", i, n_comp_proceso[i]);
        printf("Valor de comienzo proceso %d: %d\n", i, comienzo_proceso[i]);
    }

    double *vect_aux = malloc(sizeof(double) * n_comp_proceso[myrank]);




    if(myrank == 0) {

        matriz_M = reserva_memoria(matriz_M, tam_N, tam_N);
        matriz_vect_iter = reserva_memoria(matriz_vect_iter, tam_N, nIteraciones);

        obtener_valores(matriz_M, tam_N, tam_N, "mat_150x150_2023.bin");

        for(int i = 1; i < nprocess; i++) {
            for(int j = comienzo_proceso[i]; j < comienzo_proceso[i] + n_comp_proceso[i]; j++){
                MPI_Send(matriz_M[j], tam_N, MPI_DOUBLE, i, 1, MPI_COMM_WORLD);
            }
        }
    } else {
        matriz_M = reserva_memoria(matriz_M, tam_N, n_comp_proceso[myrank]);
        matriz_vect_iter = reserva_memoria(matriz_vect_iter, tam_N, nIteraciones);


        for(int i = 0; i < n_comp_proceso[myrank]; i++){
            MPI_Recv(matriz_M[i], tam_N, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD, &status);
        }

        
    }


    for(int i = 0; i < tam_N; i++) {
        matriz_vect_iter[0][i] = 1.0;
    }

    for(int i = 1; i < nIteraciones; i++){
        sum = 0;
        for(int j = 0; j < n_comp_proceso[myrank]; j++) {
            prod_sum = obtener_Multiplicacion(matriz_M, matriz_vect_iter, tam_N, j, i - 1);
            if(i != 1){
                vect_aux[j] = vect_aux[j-1] - prod_sum;
            } else {
                vect_aux[j] = prod_sum;
            }
            sum += prod_sum * prod_sum;
        }
        MPI_Allreduce(&sum, &sum_general, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
        normalizar_vector(vect_aux, n_comp_proceso[myrank], sum_general);
        MPI_Allgatherv(vect_aux, n_comp_proceso[myrank], MPI_DOUBLE, matriz_vect_iter[i], n_comp_proceso, comienzo_proceso, MPI_DOUBLE, MPI_COMM_WORLD);
    }

    if(myrank == 0) {
        for(int i = 0; i < tam_N; i++) {
            free(matriz_M[i]);
        }
        free(matriz_M);

        for(int i = 0; i < nIteraciones; i++) {
            free(matriz_vect_iter[i]);
        }
        free(matriz_vect_iter);
    } else {
        for(int i = 0; i < n_comp_proceso[myrank]; i++) {
            free(matriz_M[i]);
        }
        free(matriz_M);

        for(int i = 0; i < n_comp_proceso[myrank]; i++) {
            free(matriz_vect_iter[i]);
        }
        free(matriz_vect_iter);
    }


    free(n_comp_proceso);
    free(comienzo_proceso);

    MPI_Finalize();
}

double obtener_sum_cuadrado(double *matriz, double tam) {
    double sum = 0;
    for(int i = 0; i < tam; i++)
        sum += (matriz[i] * matriz[i]);
    return sum;
}


double obtener_Multiplicacion(double **matriz_1, double **matriz_2, int tam, int pos_i, int pos_j){
    double aux = 0;
    for(int k = 0; k < tam; k++){
        aux += matriz_1[pos_i][k] * matriz_2[pos_j][k];
    }
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
    
    double aux = 0;
    if(fichero == NULL) {

        
        // for(int i = 0; i < altura; i++) {
        //     for(int j = 0; j < anchura; j++) {
        //         aux++;
        //         matriz[i][j] = aux;
        //     }
        // }
        // return;



        srand(getpid());
        for(int i = 0; i < altura; i++){
            for(int j = 0; j < anchura; j++){
                if(i == j){
                    matriz[i][j] = 1.0;
                    continue;
                }
                matriz[i][j] = ((double) rand() / RAND_MAX) * 0.01;
            }
        }
           
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

void normalizar_vector(double *vector, int anchura, double suma) {
    double valor;
    // for(int i = 0; i < anchura; i++)
    //     valor += (vector[i] * vector[i]);
    valor = sqrt(suma);
    printf("Norma: %lf\n", valor);
    for(int i = 0; i < anchura; i++){
        // printf("Valor a normalizar: %lf\n", vector[i]);
        vector[i] /= valor;
        // printf("Valor vector normalizado: %lf\n", vector[i]);
    }
}


double **reserva_memoria(double **matriz, int anchura, int altura) {
    matriz = malloc(altura * sizeof(double*));
    for(int i = 0; i < altura; i++) {
        matriz[i] = malloc(anchura * sizeof(double));
    }
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
    printf("Saliendo del programa.......");
    exit(0);
}
