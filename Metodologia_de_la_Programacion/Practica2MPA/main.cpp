#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <time.h>

using namespace std;


int Analizar(int *vector1, int x, int n){

    int nveces = 0;

    for(int i=1; i <= n+1; i++ ){

        if(vector1[i]==x){
            nveces++;
        }
    }

    return nveces;
}

void Cambiar(int &a, int &b)
{
    int aux;
    aux = a;
    a = b;
    b = aux;
}

int* OrdenacionSelec(int *VOrdenado, int n)
{
    int posmin;
    for(int i = 1; i <= n - 1; i++)
    {
        posmin=i;

        for(int j = i + 1; j <= n; j++)
        {
            if(VOrdenado[j] < VOrdenado[posmin])
            {
                posmin = j;
            }
        }
        cout << "Cambio " << i << " por " << posmin << endl;
        Cambiar(VOrdenado[i], VOrdenado[posmin]);
        cout << "Vector: ";
        for (int k = 1; k <= n; k++) {
            cout << VOrdenado[k] << " ";
        }
        cout << endl;
    }
    return VOrdenado;
}

int* OrdenacionSelecPeor(int *VOrdenado, int n)
{
    int posmin;
    for(int i = 1; i <= n - 1; i++)
    {
        posmin=i;

        for(int j = i + 1; j <= n; j++)
        {
            if(VOrdenado[j] > VOrdenado[posmin])
            {
                posmin = j;
            }
        }
        Cambiar(VOrdenado[i], VOrdenado[posmin]);
    }
    return VOrdenado;
}



int main()
{
    int n;
    int semilla = 47;
    clock_t Tinicio, Tfinal;
    double Ttotal;

    cout << "Andres Perez" << endl << "Bryan Grisales" << endl << "Emilio Gonzalez" << endl;
    cout << "Indique el tamano del vector: ";
    cin >> n;

    int* numeros = new int [n+1];

    srand(semilla);

    for(int i = 1; i <= n; i++)
    {
        numeros[i] = rand()%11;
        cout << "Vector de Numeros (pos: " << i << "): " << numeros[i] << endl;
    }
    Tinicio = clock();
    OrdenacionSelec(numeros, n);
    Tfinal = clock();
    for(int i = 1; i <= n; i++)
    {
        cout << "Vector Ordenado (pos: " << i << "): " << numeros[i]<< endl;
    }

    OrdenacionSelecPeor(numeros, n);

    for(int i = 1; i <= n; i++) {
        cout << "Vector Peor (pos: " << i << "): " << numeros[i] << endl;
    }
    cout << endl;
    Ttotal = (double) (Tfinal - Tinicio)/CLOCKS_PER_SEC *1000;
    cout << "El tiempo de ejecucion del algoritmo es: " << Ttotal << endl;
    return 0;
}
