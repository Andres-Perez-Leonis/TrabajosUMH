#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>
#include <ctype.h>
#include <limits.h>
#include <unistd.h>
#include <omp.h>
 
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
    double tiempo_inicio, tiempo_final; 
    int data_error = 0;
    double **matriz_M, **matriz_vect_iter;



    if(argc != 5) 
        show_error(PARAM_ERROR);
    
    
    if( isdigit(*argv[1]) != 0 || isdigit(*argv[2]) == 0 || isdigit(*argv[3]) == 0 || isdigit(*argv[4]) == 0) 
        show_error(PARAM_ERROR);

    int tam_N = atoi(argv[3]), nIteraciones = atoi(argv[2]) + 1;
	nprocess = atoi(argv[4]);

    data_error = comrpoabar_valores(tam_N, nIteraciones - 1, argv[1]);
   
    int exceso = tam_N % nprocess;

    int comp_proceso = tam_N / nprocess; //El numero de componentes del vector que debe hacer cada proceso

	matriz_M = reserva_memoria(matriz_M, tam_N, tam_N);
    matriz_vect_iter = reserva_memoria(matriz_vect_iter, tam_N, nIteraciones);


	printf("Comienza la generacion de matriz\n");
	generar_matriz(matriz_M, tam_N, tam_N, argv[1], data_error, 0);
	printf("Termina la generacion de matriz\n");


    tiempo_inicio = omp_get_wtime();
	printf("Comienzan las iteraciones\n");
	#pragma omp parallel num_threads(nprocess) shared(tam_N, matriz_vect_iter, nprocess) default(none)
	{
		#pragma omp for schedule(static, tam_N/nprocess)
		for(int i = 0; i < tam_N; i++) {
			matriz_vect_iter[0][i] = 1.0;
		}
	}
	
	
    // Vector auxiliar que guardara los elementos de los productos de cada iteracion
    //double *vect_aux; //vect_aux = malloc(sizeof(double) * n_comp_proceso[myrank]);
	
    double prod_sum, sum, sum_general;
	double norma;
	int aux = 0;
	double *vect_aux = malloc(sizeof(double) * tam_N);
	
	for(int i =  1; i < nIteraciones; i++) {
		sum_general = 0;
		#pragma omp parallel num_threads(nprocess) private(sum, myrank, prod_sum, aux, norma) shared(vect_aux, nprocess, sum_general, tam_N, matriz_M, matriz_vect_iter, i) default(none)
		{
			
			myrank = omp_get_thread_num();
			sum = norma = aux = prod_sum = 0;
			#pragma omp for schedule(dynamic, tam_N/(nprocess*2))
			for(int j = 0; j < tam_N; j++) {
				prod_sum = obtener_Multiplicacion(matriz_M, matriz_vect_iter, tam_N, j, i - 1);
				//printf("PROD_SUM: %lf\n", prod_sum);
				if(i != 1){
					vect_aux[j] = vect_aux[j] - prod_sum;
				} else {
					vect_aux[j] = prod_sum;
				}
				// vect_aux[j] = matriz_vect_iter[i][j];
				//printf("VEC_AUX: %lf\n", vect_aux[j]);
				sum +=  (vect_aux[j] *  vect_aux[j]);
			}
			//printf("SUM: %lf\n",sum);
			#pragma omp critical
			{
				sum_general += sum;
			}
			#pragma omp barrier
			//sleep(1);
			//printf("SUM_GLOBAL: %lf\n",sum_general);
			norma = sqrt(sum_general);
			
			if(myrank == 0) {
				printf("Norma: %lf\n", norma);
			}
			
			#pragma omp for schedule(dynamic, tam_N/(nprocess*2))
			for(int j = 0; j < tam_N; j++){
				//printf("VALOR: %lf\n", norma);
				//printf("Valor a normalizar: %lf\n", vect_aux[j]);
				vect_aux[j] /= norma;
				//printf("Valor vector normalizado: %lf\n", vect_aux[j]);
			}
			
			
			//normalizar_vector(vect_aux, n_comp_proceso[myrank], sum_global, myrank);
			
			//printf("Soy el proceso: %d\n Comienzo en: %d\n Termino en: %d\n Estoy en la iteracion:: %d\n", myrank, comienzo_proceso[myrank], n_comp_proceso[myrank] + comienzo_proceso[myrank], i);
			#pragma omp for schedule(dynamic, tam_N/(nprocess*2))
			for(int j =  0; j < tam_N; j++) {
				//printf("Vector aux: %lf    i: %d\n", vect_aux[aux], aux);
				matriz_vect_iter[i][j] = vect_aux[j];
				//printf("VALOR: %lf    i: %d j: %d\n", matriz_vect_iter[i][j], i, j);
			}
		}
	}
	printf("Terminan las iteraciones\n");

	
	liberar_memoria(matriz_M, tam_N);

    liberar_memoria(matriz_vect_iter, nIteraciones);

    free(n_comp_proceso);
    free(comienzo_proceso);
	free(vect_aux);


    
    tiempo_final = omp_get_wtime();
	printf("El tiempo tardado fue: %lf\n", tiempo_final - tiempo_inicio);

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
		printf("GENERO LA MATRIZ YO MISMO\n");
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
	printf("Valor: %lf\n", suma);
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
        printf("Son 3 parametros: \n[Nombre del fichero imagen]:String [Numero de Iteraciones]:Entero positivo [Numero de Datos]:Entero positivo [Numero de procesos]:Entero positivo\n");
    }
    else if(error == FILE_ERROR) {
        printf("Error al abrir el archivo\n");
        printf("El nombre del archivo hay que colocarlo con extension\n");
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
