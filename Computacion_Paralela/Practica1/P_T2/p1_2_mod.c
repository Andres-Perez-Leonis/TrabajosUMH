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
#define NUM_DATA_FILE_ERROR 4


double obtener_Multiplicacion(double **matriz_1, double **matriz_2, int tam, int pos_i, int pos_j);
void normalizar_vector(double *vector, int anchura, double suma, int myrank);
void show_error(int error);
double **reserva_memoria(double **matriz, int anchura, int altura);
int comrpoabar_valores(int anchura, int altura, char* nombre);
void liberar_memoria(double **matriz, int tam) ;
void generar_matriz(double **matriz, int anchura, int altura, char *nombre, int data_error, int comienzo);




int main(int argc,char *argv[])
{



    int nprocess, myrank;
    MPI_Status status;
    double tiempo_inicio, tiempo_final; 
    int data_error = 0;
    MPI_Init(&argc,&argv);
    //
    //    PROGRAMA A DESARROLLAR CON 
    //    LLAMADAS A RUTINAS MPI
    //
    MPI_Comm_size(MPI_COMM_WORLD,&nprocess);
    MPI_Comm_rank(MPI_COMM_WORLD,&myrank);

    double **matriz_M, **matriz_vect_iter;
    double prod_sum, sum, sum_general;

    tiempo_inicio = MPI_Wtime();


    if(argc != 4) 
        show_error(PARAM_ERROR);
    
    
    if( isdigit(*argv[1]) != 0 || isdigit(*argv[2]) == 0 || isdigit(*argv[3]) == 0) 
        show_error(PARAM_ERROR);

    int tam_N = atoi(argv[3]), nIteraciones = atoi(argv[2]) + 1;

    if(myrank == 0) data_error = comrpoabar_valores(tam_N, nIteraciones - 1, argv[1]);

    int exceso = tam_N % nprocess;

    int comp_proceso = tam_N / nprocess; //El numero de componentes del vector que debe hacer cada proceso



    /*
        Genero dos vectores para saber las posiciones y el numero de componentes del vector iteracion que tendrá que realizar cada proceso
            - n_comp_proceso --> Numero de componenetes del vector iteraacion que realizara cada proceso
            - comienzo_proceso --> Posicion en la que tiene que colocar el componente del vector iteracion
    */
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
    }

    // Vector auxiliar que guardara los elementos de los productos de cada iteracion
    double *vect_aux = malloc(sizeof(double) * n_comp_proceso[myrank]);



    /*
        Dependiendo de cada proceso y si el documento indicado no es correcto, se determina una reserva de memoria distinta para cada proceso
    */
    if(myrank == 0) {

        if(data_error == 1) 
            matriz_M = reserva_memoria(matriz_M, tam_N, n_comp_proceso[myrank]);
        else
            matriz_M = reserva_memoria(matriz_M, tam_N, tam_N);
        
        
    } else {
        matriz_M = reserva_memoria(matriz_M, tam_N, n_comp_proceso[myrank]);
    }

    matriz_vect_iter = reserva_memoria(matriz_vect_iter, tam_N, nIteraciones);


    // Para que todos los procesos sepan si el documento introducido es correcto
    MPI_Allreduce(&data_error, &data_error, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);



    
    //Determinar si el documento fue correcto y si la ha generado el mismo proceso
    //Si no es correcto cada proceso genera su parte de la matriz
    //Si es correcto se enviaran las filas a cada proceso y los procesos esperaran a recibirlo
    if(myrank == 0) {
        if(data_error != 1) {
            generar_matriz(matriz_M, tam_N, tam_N, argv[1], data_error, comienzo_proceso[myrank]);
            // printf("Enviando matriz\n");
            for(int i = 1; i < nprocess; i++) {
                for(int j = comienzo_proceso[i]; j < comienzo_proceso[i] + n_comp_proceso[i]; j++){
                    MPI_Send(matriz_M[j], tam_N, MPI_DOUBLE, i, 1, MPI_COMM_WORLD);
                }
            }
        }else {
            generar_matriz(matriz_M, tam_N, n_comp_proceso[myrank], argv[1], data_error, comienzo_proceso[myrank]);
        }

    } else {

        if(data_error == 0) {
            for(int i = 0; i < n_comp_proceso[myrank]; i++){
                MPI_Recv(matriz_M[i], tam_N, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD, &status);
            }
            // printf("TERMINE DE RECIBIR %d\n", myrank);
        }else {
            generar_matriz(matriz_M, tam_N, n_comp_proceso[myrank], argv[1], data_error, comienzo_proceso[myrank]);
        }

    }



    for(int i = 0; i < tam_N; i++) {
        matriz_vect_iter[0][i] = 1.0;
    }

    for(int i = 1; i < nIteraciones; i++){
        sum = 0;
        for(int j = 0; j < n_comp_proceso[myrank]; j++) {
            prod_sum = obtener_Multiplicacion(matriz_M, matriz_vect_iter, tam_N, j, i - 1);
            // printf("VALOR DE MI PRODUCTO SOY %d: %lf\n", myrank, prod_sum);
            if(i != 1){
                vect_aux[j] = vect_aux[j] - prod_sum;
            } else {
                vect_aux[j] = prod_sum;
            }
            // vect_aux[j] = matriz_vect_iter[i][j];
            sum +=  (vect_aux[j] *  vect_aux[j]);
        }
        MPI_Allreduce(&sum, &sum_general, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
        // if(myrank == 0) printf("VALOR: %lf\n", sum_general);
        normalizar_vector(vect_aux, n_comp_proceso[myrank], sum_general, myrank);
        MPI_Allgatherv(vect_aux, n_comp_proceso[myrank], MPI_DOUBLE, matriz_vect_iter[i], n_comp_proceso, comienzo_proceso, MPI_DOUBLE, MPI_COMM_WORLD);
    }

    //Liberamos memoria
    if(myrank == 0) {
        liberar_memoria(matriz_M, n_comp_proceso[myrank]);
    } else {
        liberar_memoria(matriz_M, n_comp_proceso[myrank]);
    }

    liberar_memoria(matriz_vect_iter, nIteraciones);

    free(n_comp_proceso);
    free(comienzo_proceso);


    
    tiempo_final = MPI_Wtime();
    if(myrank == 0) 
        printf("El tiempo tardado fue: %lf\n", tiempo_final - tiempo_inicio);

    MPI_Finalize();
}

/*
    * liberar_memoria *
    Funcion para liberar la memoria de las matrices 
    Parametros:
        - matriz --> Variable doble puntero donde se guardaran todos los valores
        - tam --> Variable que determina el tamaño de la matriz
*/

void liberar_memoria(double **matriz, int tam) {
    for(int i = 0; i < tam; i++) {
            free(matriz[i]);
        }
        free(matriz);
}

/*
    * obtener_Multiplicacion *
    Funcion para multiplicar una fila y columna de da dos matrices
    Parametros:
        - matriz_1 --> Primera matriz a multiplicar
        - matriz_2 --> Segunda matriz a multiplicar
        - tam --> Variable que determina el tamaño de las matrices
        - pos_i --> Variable que determina en que fila se posicionara la primera matriz
        - pos_j --> Variable que determina en que "columna" (fila) se posicionara la segunda matriz
*/

double obtener_Multiplicacion(double **matriz_1, double **matriz_2, int tam, int pos_i, int pos_j){
    double aux = 0;
    for(int k = 0; k < tam; k++){
        aux += matriz_1[pos_i][k] * matriz_2[pos_j][k];
    }
    return aux;
}



/*
    * comprobar_valores *
    Funcion que comprueba si el fichero que se va a leer es adecuado
    Parametros:
        - anchura --> Variable que determina el ancho de la matriz
        - altura --> Variable que determina la altura de la matriz
        - nombre --> Nombre del fichero donde obtener los datos
*/


int comrpoabar_valores(int anchura, int altura, char* nombre) {
    FILE *fichero = fopen(nombre, "rb");
    
    double aux = 0;
    int data_error = 0;

    if(fichero != NULL) {
        fseek(fichero, 0, SEEK_END);
        aux = ftell(fichero) / sizeof(double);
        fseek(fichero, 0, SEEK_SET);
        if(aux < (anchura * altura)) {
            show_error(NUM_DATA_FILE_ERROR);
            data_error = 1;
        } 
        
        fclose(fichero);
    } else {
        printf("ERROR: No se ha encontrado el archivo\n");
        data_error = 1;
    }

    return data_error;
}


/*
    * generar_matriz *
    Funcion que obtiene los valores para las iteraciones, si no encuentra el documento genera los numeros
    Parametros:
        - matriz --> Variable doble puntero donde se guardaran todos los valores
        - anchura --> Variable que determina el ancho de la matriz
        - altura --> Variable que determina la altura de la matriz
        - nombre --> Nombre del fichero donde obtener los datos
        - data_error --> Variable que determina si el documento es adecuado
        - comienzo --> Variable necesaria para realizar la diagonal correcta de la matriz general
*/

void generar_matriz(double **matriz, int anchura, int altura, char *nombre, int data_error, int comienzo) {
    if(data_error == 1) {
        // printf("\nGenerando matriz...\n\n");

        srand(getpid());
        for(int i = 0; i < altura; i++){
            for(int j = 0; j < anchura; j++){
                if(comienzo == j){
                    matriz[i][j] = 1.0;
                    continue;
                }
                matriz[i][j] = ((double) rand() / RAND_MAX) * 0.01;
            }
            comienzo++;
        }
    } else {
        // printf("\nRecogiendo matriz....\n\n");
        FILE *fichero = fopen(nombre, "rb");
        if(fichero == NULL) 
            show_error(FILE_ERROR);
        for(int i = 0; i < altura; i++){
            fread(matriz[i], sizeof(double), anchura, fichero);
        }
        fclose(fichero);
    }
           
}


/*
    * normalizar_vector *
    Funcion que normaliza los valores de un vector
    Parametros:
        - vector --> Valores a normalizar
        - anchura --> Numero de elementos que hay que normalizar
*/

void normalizar_vector(double *vector, int anchura, double suma, int myrank) {
    double valor;
    // for(int i = 0; i < anchura; i++)
    //     valor += (vector[i] * vector[i]);
    valor = sqrt(suma);
    if(myrank == 0) 
        printf("Norma: %lf\n", valor);
    for(int i = 0; i < anchura; i++){
        // printf("Valor a normalizar: %lf\n", vector[i]);
        vector[i] /= valor;
        // printf("Valor vector normalizado: %lf\n", vector[i]);
    }
}




/*
    * reserva_memoria *
    Funcion que reserva memoria de forma dinamica para matrices
    Parametros:
        - matriz --> Variable doble puntero donde se guardaran todos los valores
        - anchura --> Variable que determina el ancho de la matriz
        - altura --> Variable que determina la altura de la matriz
*/


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
        printf("Son 3 parametros: \n[Nombre del fichero imagen]:String [Numero de Iteraciones]:Entero positivo [Numero de Datos]:Entero positivo\n");
    }
    else if(error == FILE_ERROR) {
        printf("Error al abrir el archivo\n");
        printf("El nombre del archivo hay que colocarlo sin extension\n");
    }
    else if(error == MEMORY_RESERVE_ERROR) printf("Error al reservar memoria\n");
    else if(error == TAM_ERROR) {
        printf("Error: Dimensiones de matriz indicados incorrectos\n");
        printf("Se esta reservando matriz que pixeles hay en la imagen\n");
    } else if(error == NUM_DATA_FILE_ERROR) {
        printf("Error: Numero de datos dentro del fichero insuficiente para los parametros introducidos\n");
        return;
    }
    printf("Saliendo del programa.......");
    exit(0);
}
