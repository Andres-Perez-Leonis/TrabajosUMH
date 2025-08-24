#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <mpi.h>
 

int main(int argc,char *argv[])
{
	
	// Comando de compilacion: mpicc examen.c -o examen
	// Comando de ejecucion: mpirun -np 3 examen
	
    int nprocess, myrank;
    MPI_Status status;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&nprocess);
    MPI_Comm_rank(MPI_COMM_WORLD,&myrank);

    int *vector;

	int dimension = 2000;

	int elementos_proceso_0 = 825;
    int tam_total = dimension - elementos_proceso_0;
	
    int elementos_proceso = tam_total/nprocess;
	int exceso = tam_total % nprocess;
	
    int *elementos_por_proceso, *desplazamientos, *elementos_esperadas;
	
	elementos_por_proceso = malloc(nprocess * sizeof(int));
	desplazamientos = malloc(nprocess * sizeof(int));

	desplazamientos[0] = 0;
	elementos_por_proceso[0] = elementos_proceso + elementos_proceso_0;


	for(int i = 1; i < nprocess; i++) {
		elementos_por_proceso[i] = elementos_proceso;
		
		if(exceso != 0 && i != 0) {
			elementos_por_proceso[i]++;
			exceso--;
		}
		desplazamientos[i] = desplazamientos[i-1] + elementos_por_proceso[i - 1];
	}
	
	if(myrank != 0) {
		vector = malloc(elementos_por_proceso[myrank] * sizeof(int));
	} else {
		vector = malloc(dimension * sizeof(int));
	}
	
	if(vector == NULL){
		printf("Error al reservar memoria\n");
		MPI_Finalize();
	}
	
	if(myrank == 0) {
		FILE *f = fopen("vector2000.bin", "rb");
        fread(vector, sizeof(int), dimension, f);
	}
	
	MPI_Scatterv (vector, elementos_por_proceso, desplazamientos, MPI_INTEGER, vector, elementos_por_proceso[myrank], MPI_INTEGER, 0, MPI_COMM_WORLD);
	
	
	int max_parcial = 0;
	int max_global;
	for(int i = 0; i < elementos_por_proceso[myrank]; i++) {
		if(vector[i] > max_parcial) {
			max_parcial = vector[i];
		}
	}
	
	
	printf("Soy el proceso %d y mi maximo es: %d\n", myrank, max_parcial);
	MPI_Allreduce(&max_parcial, &max_global, 1, MPI_INTEGER, MPI_MAX, MPI_COMM_WORLD);
	printf("Soy el proceso %d y el maximo global es: %d\n", myrank, max_global);
	
	int minimo_parcial = max_global;
	for(int i = 0; i < elementos_por_proceso[myrank]; i++) {
		if(vector[i] < minimo_parcial) {
			minimo_parcial = vector[i];
		}
	}
	
	int minimo_aux, minimo_global;
	
	printf("Soy el proceso %d y mi minimo es: %d\n", myrank, minimo_parcial);
	if(myrank == 0) {
		for(int i = 1; i < nprocess; i++) {
			MPI_Recv( &minimo_aux, 1, MPI_INTEGER, i, i, MPI_COMM_WORLD, &status);
			if(minimo_aux < minimo_global) {
				minimo_global = minimo_aux;
			}
		}
		if(minimo_parcial < minimo_global) {
			minimo_global = minimo_parcial;
		}
	} else {
		MPI_Send( &minimo_parcial, 1, MPI_INTEGER, 0, myrank, MPI_COMM_WORLD);
	}
	
	MPI_Bcast(&minimo_global, 1, MPI_INTEGER, 0, MPI_COMM_WORLD);
	
	printf("Soy el proceso %d y el minimo global es: %d\n", myrank, minimo_global);
	
	double *vector_normalizado;
	
	if(myrank != 0) {
		vector_normalizado = malloc(elementos_por_proceso[myrank] * sizeof(double));
	} else {
		vector_normalizado = malloc(dimension * sizeof(double));
	}
	
	int max_menos_min = max_global - minimo_global;
	for(int i = 0; i < elementos_por_proceso[myrank]; i++) {
		vector_normalizado[i] = (double) vector[i]/max_menos_min;
	}
	
	if(myrank == 0) {
		for(int i = 1; i < nprocess; i++) {
			MPI_Recv(vector_normalizado + desplazamientos[i], elementos_por_proceso[i], MPI_DOUBLE, i, i, MPI_COMM_WORLD, &status);
		}
	} else {
		MPI_Send(vector_normalizado, elementos_por_proceso[myrank], MPI_DOUBLE, 0, myrank, MPI_COMM_WORLD);
	}
	//if(myrank == 0)
	//for(int i = 0; i < 10; i++){
	//	printf("Vector_normalizado[%d]: %lf\n", i, vector_normalizado[i]);
	//}
	
	MPI_Finalize();
	
}