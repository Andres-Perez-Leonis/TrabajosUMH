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

//Funciones de escritura
void write_file_data(unsigned char **matriz, int width, int height);
void write_hist(int *hist, int size);

//Funciones de lectura
void read_file(unsigned char **matriz, FILE *file, int width, int height, int init_X, int init_Y);

//Funciones de reserva/liberacion de memoria
unsigned char **memory_reserve(unsigned char **matriz, int altura, int anchura);
void free_memory(unsigned char **matriz, int height);

//Funciones de extension simetrica
void simetric_extenxion(unsigned char **matriz, int width, int height , int process, int nprocess);

//Funciones Filtrado Media
unsigned char filtrate_media_pixel(unsigned char **matriz, int positionX, int positionY);
unsigned char **filtrate_media(unsigned char **matriz, unsigned char **filtrate_matriz, int width, int height, int myrank, int nprocess);

//Funciones Filtrado SOBEL
unsigned char filtrate_sobel_pixel(unsigned char **matriz, int posicionX, int posicionY);
unsigned char **filtrate_sobel(unsigned char **matriz, unsigned char **filtrate_matriz, int width, int height, int myrank, int nprocess);

//Funciones de historiograma
int *realize_hist(unsigned char ** matriz, int *hist, int width, int height);



int main(int argc,char *argv[])
{
    int nprocess, myrank;
    MPI_Status status;
    int aux = 1;
    double tiempo_inicio, tiempo_final; 
    MPI_Init(&argc,&argv);
    //
    //    PROGRAMA A DESARROLLAR CON 
    //    LLAMADAS A RUTINAS MPI
    //
    MPI_Comm_size(MPI_COMM_WORLD,&nprocess);
    MPI_Comm_rank(MPI_COMM_WORLD,&myrank);



    tiempo_inicio = MPI_Wtime();

    unsigned char **image;
    unsigned char **filtrate_image;
    if(myrank == 0) {
        if(argc != 5) show_error(PARAM_ERROR);

        if( isdigit(*argv[1]) != 0 || isdigit(*argv[2]) == 0 || isdigit(*argv[3]) == 0 || isdigit(*argv[4]) == 0) show_error(PARAM_ERROR);
    }


    int width = atoi(argv[2]), height = atoi(argv[3]);
    int height_process = height/nprocess;
    
    int type_process = atoi(argv[4]);
    /*
        Creo 5 vectores
            El primero contiene el numero de filas que procesará cada proceso
            El segundo contiene la posicion inicial que se enviaran a los demas procesoscal
            El tercero contendra las filas que esperara cada proceso (extras y necesarias para procesar imagenes)
            El primer histograma es para guardar los valores que se repiten en la imagen 
            El segundo histograma es para guardar los datos que le envian al proceso 0 desde otros procesos
    */
    int *filas_por_proceso, *pos_ini_proceso, *filas_esperadas;
    int *histograma, *histograma_aux;
    if(type_process == FILT_MEDIA || type_process == FILT_SOBEL){
        filas_por_proceso = malloc(nprocess * sizeof(int));
        pos_ini_proceso = malloc(nprocess * sizeof(int));
        filas_esperadas = malloc(nprocess * sizeof(int));

        pos_ini_proceso[0] = 0;
        filas_esperadas[0] = 0;

        int fila_proceso = height / nprocess;
        int exceso = height % nprocess;

        for(int i = 0; i < nprocess; i++) {
            filas_por_proceso[i] = fila_proceso;
            
            if(exceso != 0 && i != 0) {
                filas_por_proceso[i]++;
                exceso--;
            }
            if(i != 0 && i != nprocess - 1) filas_esperadas[i] = filas_por_proceso[i] + 2;
            else if(i == nprocess - 1) filas_esperadas[i] = filas_por_proceso[i] + 1;


            if(i == 1) pos_ini_proceso[i] = pos_ini_proceso[i-1] + filas_por_proceso[i - 1] - 1;
            else pos_ini_proceso[i] = pos_ini_proceso[i-1] + filas_por_proceso[i-1];
    } 
    }else if(type_process == HIST) {

        filas_por_proceso = malloc(nprocess * sizeof(int));
        pos_ini_proceso = malloc(nprocess * sizeof(int));

        pos_ini_proceso[0] = 0;

        int fila_proceso = height / nprocess;
        int exceso = height % nprocess;

        for(int i = 0; i < nprocess; i++) {
            filas_por_proceso[i] = fila_proceso;
            
            if(exceso != 0 && i != 0) {
                filas_por_proceso[i]++;
                exceso--;
            }


            if(i == 1) pos_ini_proceso[i] = pos_ini_proceso[i-1] + filas_por_proceso[i - 1] - 1;
            else pos_ini_proceso[i] = pos_ini_proceso[i-1] + filas_por_proceso[i-1];
        }


    }

    if(myrank == 0) {
        

        FILE *file_imagen = fopen(argv[1], "rb");

        if(file_imagen == NULL) show_error(FILE_ERROR);

        if(width <= 0 || height <= 0) show_error(PARAM_ERROR);

        if(type_process == FILT_MEDIA) {

            image = memory_reserve(image, width + 2, height + 2);
            filtrate_image = memory_reserve(filtrate_image, width, height);

            read_file(image, file_imagen, width, height, 1, 1);
            
            //La variable aux la uso para que envie los datos desde la posicion 1 hasta la posicion 513 (envio 512 elementos) 
            for(int i = 1; i < nprocess; i++) {
                for(int j = pos_ini_proceso[i]; j < pos_ini_proceso[i] + filas_esperadas[i]; j++) {
                    MPI_Send(image[j] + aux, width, MPI_UNSIGNED_CHAR, i, 1, MPI_COMM_WORLD);
                    //printf("Le envio al proceso %d la fila %d\n", i, j);
                }
            }

            simetric_extenxion(image, width + 2, height_process + 2, myrank, nprocess);
            filtrate_image = filtrate_media(image, filtrate_image, width + 2, filas_por_proceso[myrank] + 2, myrank, nprocess);
            for(int i = 1; i < nprocess; i++) {
                // printf("Empezamos en la posicion %d para el proceso %d\n", pos_ini_proceso[i] + aux, i);
                // printf("Terminamos en la posicion %d para el proceso %d\n",  filas_por_proceso[i] + pos_ini_proceso[i], i);
                for(int j = pos_ini_proceso[i] + aux; j <= filas_por_proceso[i] + pos_ini_proceso[i]; j++) {
                    MPI_Recv(filtrate_image[j], width, MPI_UNSIGNED_CHAR, i, 2, MPI_COMM_WORLD, &status);
                    //printf("He recibido la fila %d del proceso %d\n", j, i);
                }
            }

        } else if(type_process == FILT_SOBEL) {

            image = memory_reserve(image, width, height);
            filtrate_image = memory_reserve(filtrate_image, width, height);
            read_file(image, file_imagen, width, height, 0, 0);

            for(int i = 1; i < nprocess; i++)
                for(int j = pos_ini_proceso[i]; j < pos_ini_proceso[i] + filas_esperadas[i]; j++)
                    MPI_Send(image[j], width, MPI_UNSIGNED_CHAR, i, 1, MPI_COMM_WORLD);

            filtrate_image = filtrate_sobel(image, filtrate_image, width, filas_por_proceso[myrank], myrank, nprocess);
            simetric_extenxion(filtrate_image, width, filas_por_proceso[myrank], myrank, nprocess);

            for(int i = 1; i < nprocess; i++)
                for(int j = pos_ini_proceso[i] + aux; j <= pos_ini_proceso[i] + filas_por_proceso[i]; j++)
                    MPI_Recv(filtrate_image[j], width, MPI_UNSIGNED_CHAR, i, 2, MPI_COMM_WORLD, &status);

        } else if(type_process == HIST) {
            image = memory_reserve(image, width, height);
            read_file(image, file_imagen, width, height, 0, 0);
            for(int i = 1; i < nprocess; i++)
                for(int j = pos_ini_proceso[i]; j < pos_ini_proceso[i] + filas_por_proceso[i]; j++)
                    MPI_Send(image[j], width, MPI_UNSIGNED_CHAR, i, 1, MPI_COMM_WORLD);
            
            histograma = realize_hist(image, histograma, width, height);
            histograma_aux = malloc(sizeof(int) * UCHAR_MAX);
            for(int i = 1; i < nprocess; i++) {
                MPI_Recv(histograma_aux, UCHAR_MAX, MPI_INT, MPI_ANY_SOURCE, 2, MPI_COMM_WORLD, &status);
                for(int j = 0; j < UCHAR_MAX; j++)
                    histograma[j] += histograma_aux[j];
            }
        } else show_error(FILT_NON_DEFINED);


        if(type_process == FILT_MEDIA || type_process == FILT_SOBEL) write_file_data(filtrate_image, width, height);
        else if(type_process == HIST) write_hist(histograma, UCHAR_MAX);
        
        if(type_process == FILT_MEDIA) {
            free_memory(image, height + 2);
            free_memory(filtrate_image, height);
            free(filas_por_proceso);
            free(pos_ini_proceso);
            free(filas_esperadas);
        } else if(type_process == FILT_SOBEL) {
            free_memory(image, height);
            free_memory(filtrate_image, height);
            free(filas_por_proceso);
            free(pos_ini_proceso);
            free(filas_esperadas);
        } else if(type_process == HIST) {
            free_memory(image, height);
            free(histograma);
            free(histograma_aux);
            free(filas_por_proceso);
            free(pos_ini_proceso);
        }
    
    } else {
        
        if(type_process == FILT_MEDIA) {
            image = memory_reserve(image, width + 2, filas_esperadas[myrank]);
            filtrate_image = memory_reserve(filtrate_image, width, filas_por_proceso[myrank]);

            for(int i = 0; i < filas_esperadas[myrank]; i++) {
                MPI_Recv(image[i] + aux, width, MPI_UNSIGNED_CHAR, 0, 1, MPI_COMM_WORLD, &status);
            }

            simetric_extenxion(image, width + 2, filas_esperadas[myrank], myrank, nprocess);

            filtrate_image = filtrate_media(image, filtrate_image, width + 2, filas_esperadas[myrank], myrank, nprocess);

            for(int i = 0; i < filas_por_proceso[myrank]; i++)  {
                MPI_Send(filtrate_image[i], width, MPI_UNSIGNED_CHAR, 0, 2, MPI_COMM_WORLD);
            }
            
            free_memory(image, filas_esperadas[myrank]);
            free_memory(filtrate_image, filas_por_proceso[myrank]);
            free(filas_esperadas);
            free(filas_por_proceso);
            free(pos_ini_proceso);

        } else if(type_process == FILT_SOBEL) {
            image = memory_reserve(image, width, filas_esperadas[myrank]);
            filtrate_image = memory_reserve(filtrate_image, width, filas_por_proceso[myrank]);
            
            for(int i = 0; i < filas_esperadas[myrank]; i++)
                MPI_Recv(image[i], width, MPI_UNSIGNED_CHAR, 0, 1, MPI_COMM_WORLD, &status);
            
            printf("Soy el proceso %d y he terminado de recibir\n", myrank);
            filtrate_image = filtrate_sobel(image, filtrate_image, width, filas_por_proceso[myrank], myrank, nprocess);
            simetric_extenxion(filtrate_image, width, filas_por_proceso[myrank], myrank, nprocess);

            for(int i = 0; i < filas_por_proceso[myrank]; i++)
                MPI_Send(filtrate_image[i], width, MPI_UNSIGNED_CHAR, 0, 2, MPI_COMM_WORLD);
            
            
            free_memory(image, filas_esperadas[myrank]);
            free_memory(filtrate_image, filas_por_proceso[myrank]);
            free(filas_esperadas);
            free(filas_por_proceso);
            free(pos_ini_proceso);

        } else if(type_process == HIST) {
            image = memory_reserve(image, width, filas_por_proceso[myrank]);
            for(int i = 0; i < filas_por_proceso[myrank]; i++)
                MPI_Recv(image[i], width, MPI_UNSIGNED_CHAR, 0, 1, MPI_COMM_WORLD, &status);

            histograma = realize_hist(image, histograma, width, filas_por_proceso[myrank]);
            MPI_Send(histograma, UCHAR_MAX, MPI_INT, 0, 2, MPI_COMM_WORLD);

            free_memory(image, filas_por_proceso[myrank]);
            free(histograma);
            free(filas_por_proceso);
            free(pos_ini_proceso);

        }


    }

    tiempo_final = MPI_Wtime();
    if(myrank == 0){ 
        printf("Tiempo tardado: %lf\n", tiempo_final - tiempo_inicio);
    }
    printf("TERMINA PROCESO %d\n", myrank);
    MPI_Finalize();
}

/*
    * simetric_extencion *
    Funcion que realiza la extension simetrica de la matriz para poder procesarla correctamente
    Parametros:
        - matriz (unsigned char): Variable (doble puntero) para realizar 
        - width (int): Variable que indica la anchura de la matriz
        - height (int): Variable que indica la altura de la matriz
*/

void simetric_extenxion(unsigned char **matriz, int width, int height , int process, int nprocess) {
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
    * filtrate_media_pixel *
    Funcion que obtiene la media del pixel indicado por los parametros
    Parametros:
        - matriz (unsigned char): Variable (puntero doble) que contiene los elementos
        - filtrate_matriz (unsigned char): Variable (puntero doble) donde se guardaran todos los pixeles procesados
        - width (int): Variable que indica la anchura de la matriz
        - height (int): Variable que indica la altura de la matriz
*/


unsigned char **filtrate_media(unsigned char **matriz, unsigned char **filtrate_matriz, int width, int height, int myrank, int nprocess) {

   if(nprocess == 1) {
        for(int i = 1; i < height - 1; i++)
            for(int j = 1; j < width - 1; j++) {
                //printf("\nFiltrado del elemento [%d][%d]\n", i-1, j-1);
                filtrate_matriz[i-1][j-1] = filtrate_media_pixel(matriz, i, j);
            }
        return filtrate_matriz;
   }

    if(myrank != 0 && nprocess != 1){
        for(int i = 1; i < height - 1; i++)
            for(int j = 1; j < width - 1; j++)
                filtrate_matriz[i-1][j-1] = filtrate_media_pixel(matriz, i, j);
    }else
        for(int i = 1; i < height; i++)
            for(int j = 1; j < width - 1; j++)
                filtrate_matriz[i-1][j-1] = filtrate_media_pixel(matriz, i, j);


    return filtrate_matriz;
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
    for(int i = posicionX - 1; i <= posicionX + 1; i++) {
        for(int j = posicionY - 1; j <= posicionY + 1; j++) {
            //printf("%d\t", matriz[i][j]);
            filtrate_value += matriz[i][j];
        }
        //printf("\n");
    }
        //printf("\nValor filtrado: %u\t", filtrate_value/9);
    return filtrate_value/9;
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

unsigned char **filtrate_sobel(unsigned char **matriz, unsigned char **filtrate_matriz, int width, int height, int myrank, int nprocess) {
    
    if(nprocess == 1) {
        for(int i = 1; i < height - 1; i++) 
            for(int j = 1; j < width - 1; j++)
                filtrate_matriz[i-1][j-1] = filtrate_sobel_pixel(matriz, i, j);
        return filtrate_matriz;
    }


    if(myrank == nprocess - 1)
        for(int i = 1; i < height - 1; i++) 
            for(int j = 1; j < width - 1; j++)
                filtrate_matriz[i-1][j-1] = filtrate_sobel_pixel(matriz, i, j);
    else {
        printf("Aqui entro soy el proceso %d\n", myrank);
        for(int i = 1; i <= height; i++) 
            for(int j = 1; j < width - 1; j++)
                filtrate_matriz[i-1][j-1] = filtrate_sobel_pixel(matriz, i, j);
                }
    return filtrate_matriz;
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
    * realize_hist *
    Funcion que realiza el historiograma de los datos de  una matriz
    Parametros:
        - matriz (unsigned char): Variable (doble puntero) que contiene los datos
        - hist (int): Variable (puntero) donde se guardara el historiograma
        - width (int): Variable que indica la anchura de la matriz
        - height (int): Variable que indica la altura de la matriz
*/

int *realize_hist(unsigned char ** matriz, int *hist, int width, int height) {
    hist = calloc(UCHAR_MAX, sizeof(int));
    if(hist == NULL) show_error(MEMORY_RESERVE_ERROR);
    unsigned char aux;
    for(int i = 0; i < height; i++) 
        for(int j = 0; j < width; j++){
            aux = matriz[i][j];
            hist[aux]++;
        }
    
    return hist;
}


/*
    * write_hist *
    Funcion que realiza el historiograma de los datos de  una matriz
    Parametros:
        - hist (int): Variable (puntero) donde se guardara el historiograma
        - size (int): Variable que indica el tamaño del historiograma
*/

void write_hist(int *hist, int size) {
    FILE *file = fopen("hist.txt", "w");
    int maxi_ind, mini_ind;
    int maxi = 0, mini = 9999999;
    for(int i = 0; i < size; i++) {
        if(maxi < hist[i]) {
            maxi = hist[i];
            maxi_ind = i;
        }
        if(mini > hist[i]) {
            mini = hist[i];
            mini_ind = i;
        }
    }

    fprintf(file, "El elemento que mas se repite es %d un total de %d veces\n", maxi_ind, maxi);
    fprintf(file, "El elemento que menos se repite es %d un total de %d veces\n", mini_ind, mini);

    fprintf(file, "--------------------------------\n");
    fprintf(file, "Historiograma\n");
    for(int i = 0; i < size; i++) fprintf(file, "Valor %d se repitio %d veces\n", i, hist[i]);
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
    matriz = (unsigned char **) calloc(height, sizeof(unsigned char*));
    for(int i = 0; i < height; i++) matriz[i] = (unsigned char *) calloc(width, sizeof(unsigned char));
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
        printf("Son 4 parametros: \n[Nombre del fichero imagen]:String [Altura]:Entero positivo [Anchura]:Entero positivo [Tipo filtrado]:Entero positivo\n");
        printf("Posibles valores para [Tipo filtrado]:\n1 --> Filtrado por media\n2 --> Filtrado SOBEL\n3 --> Histograma\n");
    }
    else if(error == FILE_ERROR) {
        printf("Error al abrir el archivo\n");
        printf("El nombre del archivo hay que colocarlo con extension\n");
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
    MPI_Finalize();
}