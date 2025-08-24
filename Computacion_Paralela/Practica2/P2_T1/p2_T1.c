#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>
#include <memory.h>
#include <ctype.h>
#include <unistd.h>
#include <limits.h>


 
#define PARAM_ERROR 0
#define FILE_ERROR 1
#define MEMORY_RESERVE_ERROR 2
#define TAM_ERROR 3
#define FILT_NON_DEFINED 4

#define FILT_MEDIA 1
#define FILT_SOBEL 2
#define HIST 3


#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))

const int C[3][3] = {{-1,0,1}, {-2,0,2} , {-1,0,1}};
const int F[3][3] = {{-1,-2,-1}, {0,0,0}, {1,2,1}};


//Funciones de muestra de errores y datos
void show_error(int error);
void show_data(unsigned char **matriz, int width, int height);

//Funciones de escritura
void write_file_data(unsigned char **matriz, int width, int height);
void write_hist(int *hist, int size, int global_max, int global_min, int rep_max, int rep_min);

//Funciones de lectura
void read_file(unsigned char **matriz, FILE *file, int width, int height, int init_X, int init_Y);

//Funciones de reserva/liberacion de memoria
unsigned char **memory_reserve(unsigned char **matriz, int altura, int anchura);
void free_memory(unsigned char **matriz, int height);

//Funciones de extension simetrica
void simetric_extenxion_filt_media(unsigned char **matriz, int start, int finish , int process, int nprocess, int width, int height);
void simetric_extenxion_sobel(unsigned char **matriz, int width, int height , int process, int nprocess);

//Funciones Filtrado Media
unsigned char filtrate_media_pixel(unsigned char **matriz, int positionX, int positionY);
void filtrate_media(unsigned char **matriz, unsigned char **filtrate_matriz, int width, int height, int myrank, int nprocess, int pos_ini, int myrows);

//Funciones Filtrado SOBEL
unsigned char filtrate_sobel_pixel(unsigned char **matriz, int posicionX, int posicionY);
void filtrate_sobel(unsigned char **matriz, unsigned char **filtrate_matriz, int width, int height, int myrank, int nprocess, int pos_ini, int myrows);

//Funciones de historiograma
int *realize_hist(unsigned char ** matriz, int *hist, int width, int height);


unsigned char max_element(unsigned char **matriz, int width, int height);
void divide_work(int *rows_process, int *pos_ini, int nprocess, int width, int height);

int main(int argc, char *argv[]) {
	
	int myID, nprocess;
	unsigned char **image, **filtrate_matriz;
	
	
	if(argc != 6) 
		show_error(PARAM_ERROR);

	if( isdigit(*argv[1]) != 0 || isdigit(*argv[2]) == 0 || isdigit(*argv[3]) == 0 || 
		isdigit(*argv[4]) == 0 || isdigit(*argv[5]) == 0) 
			show_error(PARAM_ERROR);
    
	FILE *file_imagen = fopen(argv[1], "rb");

	if(file_imagen == NULL) 
		show_error(FILE_ERROR);
	
	int width = atoi(argv[2]), height = atoi(argv[3]);
    
	nprocess = atoi(argv[5]);
	
	if(width <= 0 || height <= 0) show_error(PARAM_ERROR);
	
    int type_process = atoi(argv[4]);
	int *filas_por_proceso, *pos_ini_proceso;

	
	double tiempo_inicio, tiempo_final;
	tiempo_inicio = omp_get_wtime();
	
		
	if(type_process == FILT_MEDIA) {
		image = memory_reserve(image, width + 4, height + 4);
		filtrate_matriz = memory_reserve(filtrate_matriz, width, height);
		read_file(image, file_imagen, width, height, 2, 2);
		
		
		tiempo_inicio = omp_get_wtime();
	
		filas_por_proceso = malloc(nprocess * sizeof(int));
        pos_ini_proceso = malloc(nprocess * sizeof(int));

        
		divide_work(filas_por_proceso, pos_ini_proceso, nprocess, width + 4, height + 4);
		
		#pragma omp parallel num_threads(nprocess) private(myID) shared(image, filtrate_matriz, filas_por_proceso, pos_ini_proceso, nprocess, width, height)
		{
			myID = omp_get_thread_num();
			simetric_extenxion_filt_media(image, pos_ini_proceso[myID], filas_por_proceso[myID] + pos_ini_proceso[myID], myID, nprocess, width, height);
			#pragma omp barrier
			filtrate_media(image, filtrate_matriz, width + 4, height + 4, myID, nprocess, pos_ini_proceso[myID], filas_por_proceso[myID]);
			
		}
		tiempo_final = omp_get_wtime();
		
		write_file_data(filtrate_matriz, width, height);
		free_memory(image, height + 4);
		free_memory(filtrate_matriz, height);
		
	} else if(type_process == FILT_SOBEL) {
		image = memory_reserve(image, width, height);
		filtrate_matriz = memory_reserve(filtrate_matriz, width, height);
		read_file(image, file_imagen, width, height, 0, 0);
		
		
		tiempo_inicio = omp_get_wtime();
		
		
		filas_por_proceso = malloc(nprocess * sizeof(int));
        pos_ini_proceso = malloc(nprocess * sizeof(int));
		
		
		divide_work(filas_por_proceso, pos_ini_proceso, nprocess, width, height);
		
		#pragma omp parallel num_threads(nprocess) private(myID) shared(image, filtrate_matriz, filas_por_proceso, pos_ini_proceso, nprocess, width, height)
		{
			//nprocess = omp_get_num_threads();
			myID = omp_get_thread_num();
			#pragma omp for schedule(static, height/nprocess)
			for(int i = 1; i < height - 1; i++) 
				for(int j = 1; j < width - 1; j++)
					filtrate_matriz[i-1][j-1] = filtrate_sobel_pixel(image, i, j);
			
            //filtrate_sobel(image, filtrate_matriz, width, height, myID, nprocess, pos_ini_proceso[myID], filas_por_proceso[myID]);
            simetric_extenxion_sobel(filtrate_matriz, pos_ini_proceso[myID], filas_por_proceso[myID], myID, nprocess);
		}
		tiempo_final = omp_get_wtime();
		write_file_data(filtrate_matriz, width, height);
		free_memory(image, height);
		free_memory(filtrate_matriz, height);
	} else if(type_process == HIST) {
		
		
		int *hist, *hist_global;
		int aux;
		
		image = memory_reserve(image, width, height);
		
		read_file(image, file_imagen, width, height, 0, 0);
		
		tiempo_inicio = omp_get_wtime();
		hist_global = calloc(UCHAR_MAX, sizeof(int));
		
		
		if(hist_global == NULL) show_error(MEMORY_RESERVE_ERROR);
		
		
		#pragma omp parallel num_threads(nprocess) private(hist, aux) shared(image, height, width, hist_global, nprocess) default(none)
		{
			
			
			
			hist = calloc(UCHAR_MAX, sizeof(int));
			if(hist == NULL) show_error(MEMORY_RESERVE_ERROR);
			
			#pragma omp for schedule(static, height/nprocess)
			for(int i = 0; i < height; i++) 
				for(int j = 0; j < width; j++){
					aux = image[i][j];
					hist[aux]++;
				}
				
			#pragma omp critical (cal_hist)
			{
				for(int i = 0; i < UCHAR_MAX; i++) {
					hist_global[i] += hist[i];
				}
			}
			free(hist);
		}
		
		int max = 0, min = UCHAR_MAX;
		int global_min = UCHAR_MAX, global_max = 0;
		
		
		filas_por_proceso = malloc(nprocess * sizeof(int));
        pos_ini_proceso = malloc(nprocess * sizeof(int));
		
		pos_ini_proceso[0] = 0;
		int bloq_hist = (UCHAR_MAX + 1)/nprocess;
		filas_por_proceso[0] = bloq_hist;
		
		int exceso = (UCHAR_MAX + 1)%nprocess;
		
		for(int i = 1; i < nprocess; i++) {
			filas_por_proceso[i] = bloq_hist;
			
			if(exceso != 0 && i != 0) {
				filas_por_proceso[i]++;
				exceso--;
			}
			pos_ini_proceso[i] = pos_ini_proceso[i-1] + filas_por_proceso[i-1];
		} 
		
		
		#pragma omp parallel num_threads(nprocess) private(min, max, myID) shared(global_max, global_min, nprocess, hist_global, filas_por_proceso, pos_ini_proceso) default(none)
		{
			
			myID = omp_get_thread_num();
			max=0;  
			min=255;
			for(int i = pos_ini_proceso[myID]; i < filas_por_proceso[myID] + pos_ini_proceso[myID]; i++) {
				if(hist_global[max] < hist_global[i])
					max = i;
				if(hist_global[min] > hist_global[i])
					min = i;
			}
			
			
			#pragma omp critical (cal_max_min)
			{
				if(hist_global[global_max] < hist_global[max])
					global_max = max;
				if(hist_global[global_min] > hist_global[min])
					global_min = min;
			}
		}
		
		free(filas_por_proceso);
		free(pos_ini_proceso);
		
		int rep_max = 0, rep_min = 0;
		int rep_max_global = 0, rep_min_global = 0;
		int count = 0;
		#pragma omp parallel num_threads(nprocess) private(rep_max, rep_min) shared(count, hist_global, global_max, global_min, rep_max_global, rep_min_global, nprocess) default(none)
		{
			rep_max = rep_min = 0;
			#pragma omp for schedule(dynamic, UCHAR_MAX/(nprocess*2))
			for(int i = 0; i < UCHAR_MAX; i++) {
				if(hist_global[global_max] == hist_global[i]) {
					rep_max++;
				}
				if(hist_global[global_min] == hist_global[i]) {
					count++;
					rep_min++;
				}
			}
			
			#pragma omp critical (cal_reps)
			{
				rep_max_global += rep_max;
				rep_min_global += rep_min;
			}
		}
		
		
		tiempo_final = omp_get_wtime();
		write_hist(hist_global, UCHAR_MAX, global_max, global_min, rep_max_global, rep_min_global);
		 
		free(hist_global);
		
		
	} else show_error(FILT_NON_DEFINED);
	
	
	printf("Tiempo tardado en ejecucion: %lf\n", tiempo_final - tiempo_inicio);
	return 0;
}

/*
	* divide_work *
	Funcion que divide el trabajo (datos a procesar) entre los procesos
	- rows_process (int): Vector que guarda el numero de filas que le toca procesar a cada proceso
	- pos_ini (int): Vector que guarda donde deben empezar a procesar a cada proceso
	- nprocess (int): Variable que indica el numero de procesos que hay en la region paralela
	- width (int): Variable que indica la anchura de la matriz
	- height (int): Variable que indica la altura de la matriz
	
*/

void divide_work(int *rows_process, int *pos_ini, int nprocess, int width, int height) {

	int fila_proceso = height / nprocess;
	int exceso = height % nprocess;


	pos_ini[0] = 0;
	rows_process[0] = fila_proceso;

	for(int i = 1; i < nprocess; i++) {
		rows_process[i] = fila_proceso;
		
		if(exceso != 0 && i != 0) {
			rows_process[i]++;
			exceso--;
		}


		pos_ini[i] = pos_ini[i-1] + rows_process[i-1];
	} 
}




/*
    * show_data *
    Funcion para mostar algunos elementos de la matriz
    Parametros:
        - matriz (unsigned char): Variable (doble puntero) donde se encuentrar los elementos a mostrar
        - n_element_show (int): Variable donde se indica el numero de elementos que queremos mostrar
*/

void show_data(unsigned char **matriz, int width, int height) {
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            printf("%d\t", matriz[i][j]);
        }
        printf("\n");
    }
}

/*
    * simetric_extencion_sobel *
    Funcion que realiza la extension simetrica para el filtrado por sobel de la matriz para poder procesarla correctamente
    Parametros:
        - matriz (unsigned char): Variable (doble puntero) para realizar 
        - width (int): Variable que indica la anchura de la matriz
        - height (int): Variable que indica la altura de la matriz
		- process (int): Variable que indica el proceso que ejecuta la funcion
		- nprocess (int): Variable que indica el numero de procesos que hay en la region paralela
*/

void simetric_extenxion_sobel(unsigned char **matriz, int width, int height , int process, int nprocess) {
	#pragma omp for
    for(int i = 0; i < height; i++)
        for(int j = 0; j < width; j++) {
            
            if(i > 0 && j > 0 && i < height - 1 && j < width - 1) continue;

            if(i == 0 && j == 0 && process == 0) matriz[i][j] = matriz[i+2][j+2];
            else if(i == 0 && j == width - 1 && process == 0) matriz[i][j] = matriz[i+2][j-2];
            else if(i == height - 1 && j == 0) matriz[i][j] = matriz[i-2][j+2];
            else if(i == height - 1 && j == width - 1 && process == nprocess - 1) matriz[i][j] = matriz[i-2][j-2];
            else if(i == 0 && process == 0) matriz[i][j] = matriz[i+2][j];
            else if(j == 0) matriz[i][j] = matriz[i][j+2];
            else if(i == height - 1 && process == nprocess - 1) matriz[i][j] = matriz[i-2][j];
            else if(j == width - 1) matriz[i][j] = matriz[i][j-2];
            
            //printf("Elemento [%d][%d]: %u\n", i, j, matriz[i][j]);
        }
}


/*
    * simetric_extenxion_filt_media *
    Funcion que realiza la extension simetrica para el filtrado por media de la matriz para poder procesarla correctamente
    Parametros:
        - matriz (unsigned char): Variable (doble puntero) para realizar 
        - start (int): Variable que indica donde comienza el proceso a procesar sobre la matriz
        - finish (int): Variable que indica donde termina el proceso a procesar sobre la matriz
		- process (int): Variable que indica el proceso que ejecuta la funcion
		- nprocess (int): Variable que indica el numero de procesos que hay en la region paralela
        - width (int): Variable que indica la anchura de la matriz
        - height (int): Variable que indica la altura de la matriz
*/


void simetric_extenxion_filt_media(unsigned char **matriz, int start, int finish , int process, int nprocess, int width, int height) {
	/*
		Hay que tener en cuenta que las matrices por ejempllo de 515x512
		Su altura y su anchura sera de 512 pero a nivel de programacion sera [0,511]
		Por eso en algunos casos como en la extension del bloque final se hace un -1 para "empezar" en el 511
	*/
	if(process == 0) {
		memcpy(matriz[0], matriz[4], width);
		memcpy(matriz[1], matriz[3], width);
		//Extension del bloque 2x2 inicial (de la fila 0 y 1)
		//matriz[0][0] = matriz[4][4];
		//matriz[1][0] = matriz[3][4];
		//matriz[0][1] = matriz[4][3];
		//matriz[1][1] = matriz[3][3];
		//
		////Extesion del bloque 2x2 final (de las filas 0 y 1)
		//matriz[0][width - 1] = matriz[4][width - 4 - 1];
		//matriz[0][width - 2] = matriz[4][width - 3 - 1];
		//matriz[1][width - 1] = matriz[3][width - 4 - 1];
		//matriz[1][width - 2] = matriz[3][width - 3 - 1];

	}
	
	if(process == nprocess - 1) {
		memcpy(matriz[height - 1], matriz[height - 4 - 1], width);
		memcpy(matriz[height - 2], matriz[height - 3 - 1], width);
		
		//matriz[height - 1][0] = matriz[height - 4 - 1][4];
		//matriz[height - 2][0] = matriz[height - 3 - 1][4];
		//matriz[height - 1][1] = matriz[height - 4 - 1][3];
		//matriz[height - 2][1] = matriz[height - 3 - 1][3];
		//
		//
		//
		//matriz[height - 1][width - 1] = matriz[height - 4 - 1][width - 4 - 1];
		//matriz[height - 1][width - 2] = matriz[height - 4 - 1][width - 3 - 1];
		//matriz[height - 2][width - 1] = matriz[height - 3 - 1][width - 4 - 1];
		//matriz[height - 2][width - 2] = matriz[height - 3 - 1][width - 3 - 1];
		
		
	}
	
	for(int i = start; i < finish; i++) {
			matriz[i][0] = matriz[i][4];
			matriz[i][1] = matriz[i][3];
			matriz[i][width - 1] = matriz[i][width - 4 - 1];
			matriz[i][width - 2] = matriz[i][width - 3 - 1];
	}
}


/*
    * filtrate_media_pixel *
    Funcion que obtiene la media del pixel indicado por los parametros
    Parametros:
        - matriz (unsigned char): Variable (puntero doble) que contiene los elementos
        - filtrate_matriz (unsigned char): Variable (puntero doble) donde se guardaran todos los pixeles procesados
        - width (int): Variable que indica la anchura de la matriz
        - height (int): Variable que indica la altura de la matriz
*/


void filtrate_media(unsigned char **matriz, unsigned char **filtrate_matriz, int width, int height, int myrank, int nprocess, int pos_ini, int myrows) {

    /*
        Segun el bryan hay que hacer que el proceso 0 itere hasta el tamaño de las filas y no hasta filas - 1
        Es decir que segun el hay que cambiar height - 1 por heigth para el proceso 0
    */
	
	if(nprocess == 1) {
        for(int i = 2; i < height - 2; i++)
            for(int j = 2; j < width - 2; j++) {
                //printf("\nFiltrado del elemento [%d][%d]\n", i-1, j-1);
                filtrate_matriz[i-2][j-2] = filtrate_media_pixel(matriz, i, j);
            }
		return;
   }
	

    if(myrank == 0)
        for(int i = 2; i < myrows; i++)
            for(int j = 2; j < width - 2; j++)
                filtrate_matriz[i-2][j-2] = filtrate_media_pixel(matriz, i, j);
	else if(nprocess - 1 == myrank)
		for(int i = pos_ini; i < myrows + pos_ini - 2; i++)
            for(int j = 2; j < width - 2; j++)
                filtrate_matriz[i-2][j-2] = filtrate_media_pixel(matriz, i, j);
    else
        for(int i = pos_ini; i < pos_ini + myrows; i++)
            for(int j = 2; j < width - 2; j++)
                filtrate_matriz[i-2][j-2] = filtrate_media_pixel(matriz, i, j);


    return;
}

/* 
    * filtrate_media_pixel *
    Funcion que obtiene la media del pixel indicado por los parametros
    Parametros:
        - matriz (unsigned char): Variable (puntero doble) que contiene los elementos
        - posicionX (int): Variable que indica la posicion en el eje x del pixel
        - posicionY (int): Variable que indica la posicion en  el eje y del pixel
    Devolucion filtrate_vaule/9

*/

unsigned char filtrate_media_pixel(unsigned char **matriz, int posicionX, int posicionY) {
    int filtrate_value = 0;
	
	int max = 0, min = 9999999;
	int max_i, max_j, min_i, min_j;
	
	for(int i = posicionX - 2; i <= posicionX + 2; i++) {
        for(int j = posicionY - 2; j <= posicionY + 2; j++) {
			if(max < matriz[i][j]) {
				max = matriz[i][j];
				max_i = i;
				max_j = j;
			}
			if(min > matriz[i][j]){
				min = matriz[i][j];
				min_i = i;
				min_j = j;
			}
        }
    }
	
	//printf("MAX_I: %d \nMAX_J: %d\n", max_i, max_j);
	//printf("min_i: %d \nmin_j: %d\n", min_i, min_j);
	//int contador = 0;
	
    for(int i = posicionX - 2; i <= posicionX + 2; i++) {
        for(int j = posicionY - 2; j <= posicionY + 2; j++) {
			
			if( i != max_i || j != max_j) {
				if(i != min_i || j != min_j) {
				//printf("ENTRA CON LOS VALORES i: %d y j: %d\n", i, j);
					filtrate_value += matriz[i][j];
					//contador++;
				}
			}
			
			
			//if( (i != max_i && j != max_j) == 0 || (i != min_i && j != min_j) == 0) {
			//	printf("ENTRA CON LOS VALORES i: %d y j: %d\n", i, j);
			//	filtrate_value += matriz[i][j];
			//	contador++;
			//}
        }
		
        //printf("\n");
    }
	//printf("Se ha sumado %d vces\n", contador);
    return filtrate_value/23;
}

/*
    * write_file_data *
    Funcion que escribe los datos de una matriz en un fichero
    Parametros:
        - matriz (unsigned char): Variable (doble puntero) qque contiene los datos a escribir
        - width (int): Variable que indica la anchura de la matriz
        - height (int): Variable que indica la altura de la matriz
*/

void write_file_data(unsigned char **matriz, int width, int height) {
    FILE *file = fopen("resultado.raw", "wb");
    for(int i = 0; i < height; i++) fwrite(matriz[i], sizeof(unsigned char), width, file);
}

/*
    * filtrate_sobel *
    Funcion que filtra una imagen usando SOBEL
    Parametros:
        - matriz (unsigned char): Variable (doble puntero) que contiene los datos
        - filtrate_matriz (unsigned char): Variable (doble puntero) donde se guardaran los datos filtrados
        - width (int): Variable que indica la anchura de la matriz
        - height (int): Variable que indica la altura de la matriz
*/

void filtrate_sobel(unsigned char **matriz, unsigned char **filtrate_matriz, int width, int height, int myrank, int nprocess, int pos_ini, int myrows) {
    
    if(nprocess == 1) {
        for(int i = 1; i < height - 1; i++) 
            for(int j = 1; j < width - 1; j++)
                filtrate_matriz[i-1][j-1] = filtrate_sobel_pixel(matriz, i, j);
        return;
    }


    if(myrank == nprocess - 1) {
        printf("entro en el primero soy el proceso %d procesare [%d,%d]\n", myrank, pos_ini, myrows + pos_ini - 1);
        for(int i = pos_ini; i < pos_ini + myrows - 1; i++) 
            for(int j = 1; j < width - 1; j++)
                filtrate_matriz[i-1][j-1] = filtrate_sobel_pixel(matriz, i, j);
	} else {
        printf("Aqui entro soy el proceso %d procesare [%d,%d]\n", myrank, pos_ini, myrows + pos_ini);
        for(int i = pos_ini + 1; i <= pos_ini + myrows; i++)  
            for(int j = 1; j < width - 1; j++)
                filtrate_matriz[i-1][j-1] = filtrate_sobel_pixel(matriz, i, j);
	}
    return;
}

/*
    * filtrate_sobel_pixel *
    Funcion que filtra el pixel de una imagen usando SOBEL
    Parametros:
        - matriz (unsigned char): Variable (doble puntero) donde se guardaran los datos filtrados
        - posicionX (int): Variable que indica la posicion del dato en la matriz
        - posicionY (int): Variable que indica la posicion del dato en la matriz
*/

unsigned char filtrate_sobel_pixel(unsigned char **matriz, int posicionX, int posicionY) {
    unsigned char filtrate_pixel = 0;
    unsigned long sum_c = 0, sum_f = 0;
    int aux = 0, aux2 = 0;
    for(int i = posicionX - 1; i <= posicionX + 1 && aux < 3; i++) {
        aux2 = 0;
        for(int j = posicionY - 1; j <= posicionY + 1 && aux2 < 3; j++) {
            sum_c += matriz[i][j] * C[aux][aux2];
            sum_f += matriz[i][j] * F[aux][aux2];
            aux2++;
        }
        aux++;
    }

    filtrate_pixel = sqrt(sum_c * sum_c + sum_f * sum_f);
    return  filtrate_pixel;
}


/*
    * write_hist *
    Funcion que realiza el historiograma de los datos de  una matriz
    Parametros:
        - hist (int): Variable (puntero) donde se guardara el historiograma
        - size (int): Variable que indica el tamaño del historiograma
*/

void write_hist(int *hist, int size, int global_max, int global_min, int rep_max, int rep_min) {
    FILE *file = fopen("hist.txt", "w");

	//fprintf(file, "El elemento que mas se repite es %d un total de %d veces\n", maxi_ind, maxi);
	//fprintf(file, "El elemento que menos se repite es %d un total de %d veces\n", mini_ind, mini);
	//
	fprintf(file, "El numero que mas se repite es %d y se repite %d veces\n", global_max, hist[global_max]); 
	fprintf(file, "El numero que menos se repite es %d y se repite %d veces\n", global_min, hist[global_min]);
	fprintf(file, "Hay %d elementos que se repiten el mismo numero que veces que el maximo\n", rep_max - 1);
	fprintf(file, "Hay %d elementos que se repiten el mismo numero que veces que el minimo\n", rep_min - 1);
    fprintf(file, "--------------------------------\n");
    fprintf(file, "Historiograma\n");
    for(int i = 0; i < size; i++) fprintf(file, "Valor %d se repitio %d veces\n", i, hist[i]);
	fclose(file);
}


/*
    * memory_reserve *
    Función para reservar memoria en la matriz (imagen)
    Parametros:
        - matriz (unsigned char): Variable (doble puntero)
        - width (int): Variable que indica la anchura de la matriz
        - height (int): Variable que indica la altura de la matriz

    Devolución: Matriz
*/

unsigned char **memory_reserve(unsigned char **matriz, int width, int height) {
    matriz = (unsigned char **) calloc(width, sizeof(unsigned char*));
    for(int i = 0; i < width; i++) matriz[i] = (unsigned char *) calloc(height, sizeof(unsigned char));
    if(matriz == NULL || matriz[0] == NULL) show_error(MEMORY_RESERVE_ERROR);
    return matriz;
}


/*
    * read_file *
    Funcion para leer los datos de un documento e introducirlos en la matriz
    Parametros:
        - matriz (unsigned char): Variable (doble puntero) donde se guardaran los datos
        - file (FILE): Puntero al documento de donde se leeran los datos
        - width (int): Variable que indica la anchura de matriz
        - height (int): Variable que indica la altura de matriz
*/

void read_file(unsigned char **matriz, FILE *file, int width, int height, int init_X, int init_Y) {
    /*
        Aqui hay que tener en cuenta que lo que estamos haciendo es escribir la matriz empezando por la posicion [1,1] ó [0,0]
        Por eso se utiliza la estructura matriz[i] para mover el puntero de las filas y luego
        se usa aritmetica de punteros para saltarse la primer columna
        
        De este modo dejamos en blanco la primera columna y fila 
        Y luego como le pasamos el tamaño de matriz reducida (el tamaño de la matriz filtrada), dejamos en blanco la ultima fila y columna
    */
    for(int i = init_X; i <= height; i++)
        fread(matriz[i] + init_Y, sizeof(unsigned char), width, file);

}



/*
    * free_memory *´
    La función libera la memoria dinámica asignada a una matriz
    Parámetros:
        - matriz (unsigned char): Puntero a una matriz de bytes
        - height (int): Altura de la matriz

*/

void free_memory(unsigned char **matriz, int height) {
    for(int i = 0; i < height; i++) free(matriz[i]);
    free(matriz);
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
        printf("Son 4 parametros: \n[Nombre del fichero imagen]:String [Altura]:Entero positivo [Anchura]:Entero positivo [Tipo filtrado]:Entero positivo [Numero de procesos]:Entero > 0\n");
        printf("Posibles valores para [Tipo filtrado]:\n1 --> Filtrado por media\n2 --> Filtrado SOBEL\n");
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
    printf("Saliendo del programa.......\n");
    exit(0);
}