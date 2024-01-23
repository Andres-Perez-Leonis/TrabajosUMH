#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <math.h>
#include <ctype.h>

#define PARAM_ERROR 0
#define FILE_ERROR 1
#define MEMORY_RESERVE_ERROR 2
#define TAM_ERROR 3
#define FILT_NON_DEFINED 4

#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))

#define FILT_MEDIA 1
#define FILT_SOBEL 2
#define HIST 3



#define WIDTH_ADD 2
#define HEIGHT_ADD 2
#define FILTRATE_SIZE 3

const int C[3][3] = {{-1,0,1}, {-2,0,2} , {-1,0,1}};
const int F[3][3] = {{-1,-2,-1}, {0,0,0}, {1,2,1}};

void show_error(int error);
unsigned char **memory_reserve(unsigned char **matriz, int altura, int anchura);
void show_data(unsigned char **matriz, int width, int height);
void read_file(unsigned char **matriz, FILE *file, int width, int height, int init_X, int init_Y);
void write_file_data(unsigned char **matriz, int width, int height);
void free_memory(unsigned char **matriz, int height);
void simetric_extenxion(unsigned char **matriz, int width, int height);
unsigned char filtrate_media_pixel(unsigned char **matriz, int positionX, int positionY);
unsigned char **filtrate_media(unsigned char **matriz, unsigned char **filtrate_matriz, int width, int height);
unsigned char filtrate_sobel_pixel(unsigned char **matriz, int posicionX, int posicionY);
unsigned char **filtrate_sobel(unsigned char **matriz, unsigned char **filtrate_matriz, int width, int height);

void write_hist(int *hist, int size);
int *realize_hist(unsigned char ** matriz, int *hist, int width, int height);
unsigned char max_element(unsigned char **matriz, int width, int height);

 
int main(int argc,char *argv[])
{



    if(argc != 5) show_error(PARAM_ERROR);

    if( isdigit(*argv[1]) != 0 || isdigit(*argv[2]) == 0 || isdigit(*argv[3]) == 0 || isdigit(*argv[4]) == 0) show_error(PARAM_ERROR);

    FILE *file_imagen = fopen(strcat(argv[1], ".raw"), "rb");

    if(file_imagen == NULL) show_error(FILE_ERROR);

    int width = atoi(argv[2]), height = atoi(argv[3]);

    if(width <= 0 || height <= 0) show_error(PARAM_ERROR);

    unsigned char **image;
    unsigned char **filtrate_image;

    int process = atoi(argv[4]);

    if(process == FILT_MEDIA) {
        image = memory_reserve(image, width  + WIDTH_ADD, height  + HEIGHT_ADD);
        filtrate_image = memory_reserve(filtrate_image, width, height);
        
        read_file(image, file_imagen, width, height, 1, 1);

        //Filtrado por media
        simetric_extenxion(image, width, height);
        /*
        */

        filtrate_image = filtrate_media(image, filtrate_image, width + WIDTH_ADD, height + HEIGHT_ADD);
        //show_data(image, width, height);
    }else if(process == FILT_SOBEL) {

        image = memory_reserve(image, width, height);
        filtrate_image = memory_reserve(filtrate_image, width, height);
        
        read_file(image, file_imagen, width, height, 0, 0);


        //Filttado SOBEL

        //show_data(image, width, height);

        filtrate_image = filtrate_sobel(image, filtrate_image, width, height);
        //show_data(filtrate_image, width, height);
        simetric_extenxion(filtrate_image, width, height);
    
    } else if(process == HIST) {
        //Historiograma
        int *n_element = realize_hist(image, n_element, width + WIDTH_ADD, height + HEIGHT_ADD);

    }else show_error(FILT_NON_DEFINED);

    write_file_data(filtrate_image, width, height);
    free_memory(image, height + HEIGHT_ADD);
    free_memory(filtrate_image, height);
    return 0;    
}

/*
    * simetric_extencion *
    Funcion que realiza la extension simetrica de la matriz para poder procesarla correctamente
    Parametros:
        - matriz (unsigned char): Variable (doble puntero) para realizar 
        - width (int): Variable que indica la anchura de la matriz
        - height (int): Variable que indica la altura de la matriz
*/

void simetric_extenxion(unsigned char **matriz, int width, int height) {
    /*
    memcpy(matriz[0], matriz[2], sizeof(unsigned char) * width);
    memcpy(matriz[height - 1], matriz[height - 3], sizeof(unsigned char) * width);
    for(int i = 1; i < height - 1; i++) 
        for(int j = 1; j < width - 1; j++) {

            if(i == 1 && j == 1) {
                matriz[0][0] = matriz[i+1][j+1];
                matriz[i][j-1] = matriz[i][j+1];
            }
            else if(i == 1 && j == width - 2) {
                matriz[0][width-1] = matriz[i+1][j-1];
                matriz[i][j+1] = matriz[i][j-1];
            }
            else if(i == height - 2 && j == 1){
                matriz[height - 1][0] = matriz[i-1][j+1];
                matriz[i][j-1] = matriz[i][j+1];
            }
            else if( i != 1 && j == 1){
                matriz[i][j-1] = matriz[i][j+1];
            }
            else if(i != height - 2 && j == width - 2){
                matriz[i][j+1] = matriz[i][j-1];
            }
        }
   */
    for(int i = 0; i < height; i++)
        for(int j = 0; j < width; j++) {
            
            if(i > 0 && j > 0 && i < height - 1 && j < width - 1) continue;

            if(i == 0 && j == 0) matriz[i][j] = matriz[i+2][j+2];
            else if(i == 0 && j == width - 1) matriz[i][j] = matriz[i+2][j-2];
            else if(i == height - 1 && j == 0) matriz[i][j] = matriz[i-2][j+2];
            else if(i == height - 1 && j == width - 1) matriz[i][j] = matriz[i-2][j-2];
            else if(i == 0) matriz[i][j] = matriz[i+2][j];
            else if(j == 0) matriz[i][j] = matriz[i][j+2];
            else if(i == height - 1) matriz[i][j] = matriz[i-2][j];
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


unsigned char **filtrate_media(unsigned char **matriz, unsigned char **filtrate_matriz, int width, int height) {
    for(int i = 1; i < height - 1; i++)
        for(int j = 1; j < width - 1; j++) {
            //printf("\nFiltrado del elemento [%d][%d]\n", i-1, j-1);
            filtrate_matriz[i-1][j-1] = filtrate_media_pixel(matriz, i, j);
        }
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
    fclose(file);
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

unsigned char **filtrate_sobel(unsigned char **matriz, unsigned char **filtrate_matriz, int width, int height) {
    
    for(int i = 1; i < height - 1; i++) 
        for(int j = 1; j < width - 1; j++)
            filtrate_matriz[i-1][j-1] = filtrate_sobel_pixel(matriz, i, j);
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
    unsigned char maximo = max_element(matriz, width, height);
    hist = calloc(maximo, sizeof(unsigned char));
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
    * max_element *
    Funcion que ddetermina el mayor elemento de una matriz
    Parametros:
        - matriz (unsigned char): Variable (doble puntero) que contiene los datos
        - width (int): Variable que indica la anchura de la matriz
        - height (int): Variable que indica la altura de la matriz 
*/


unsigned char max_element(unsigned char **matriz, int width, int height) {
    unsigned char maximo = 0;
    for(int i = 0; i < height; i++)
        for(int j = 0; j < width; j++)
            maximo = max(maximo, matriz[i][j]);
    return maximo;
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
    for(int i = 0; i < size; i++) fprintf(file, "Valor %d se repitio %d veces", i, hist[i]);
}

//Probar en la funcion de arriba a usar el mencopy


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
    matriz = (unsigned char **) malloc(height * sizeof(unsigned char*));
    for(int i = 0; i < height; i++) matriz[i] = (unsigned char *) malloc(width * sizeof(unsigned char));
    if(matriz == NULL || matriz[0] == NULL) show_error(MEMORY_RESERVE_ERROR);
    return matriz;
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
        for(int j = 0; j < width; j++)
            printf("Elemento [%d][%d]: %u\n", i, j, matriz[i][j]);
    }
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
    for(int i = init_X; i < height; i++)
        fread(matriz[i] + init_Y, sizeof(unsigned char), width, file);
    fclose(file);
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
    printf("Saliendo del programa.......");
    exit(0);
}