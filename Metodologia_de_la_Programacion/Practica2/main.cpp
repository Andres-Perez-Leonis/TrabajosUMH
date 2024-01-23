#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

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
        Cambiar(VOrdenado[i], VOrdenado[posmin]);
    }
    return VOrdenado;
}



int main()
{
    int n;
    int semilla = 47;
    int* aux2;
    clock_t Tinicio, Tfinal;
    double Ttotal;

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
    Ttotal = (double) (Tfinal - Tinicio)/CLOCKS_PER_SEC *1000;
    cout << "El tiempo de ejecucion del algoritmo es: " << Ttotal << endl;
    return 0;
}
