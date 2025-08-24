
/*

#include <iostream>
using namespace std;

int mochila(int mochila_capacidad, int n_objetos, int* pesos, int* valor_objetos) {
    int i,j;
    int aux1, aux2;
    int suma, resta;
    //matriz=filas*columnas
    //filas= n_objetos
    //columnas=mochila_capacidad

    int** T = new int*[n_objetos + 1];
    for (i = 0; i < n_objetos + 1; i++)
    {
        T[i] = new int[mochila_capacidad + 1];
    }
    for(i = 0; i < n_objetos + 1; i++)
    {
        for(j = 0; j < mochila_capacidad + 1; j++)
        {
            T[i][j] = 0;

        }
    }
    for(i = 1; i <= n_objetos; i++)
    {
        for(j = 1; j <= mochila_capacidad; j++)
        {
            if(pesos[i] > j)
            {
                T[i][j] = T[i-1][j];
                aux1 = i;
                aux2 = j;
            }
            else
            {
                resta = j - pesos[i];
                suma = valor_objetos[i] + T[i-1][resta];
                if(T[i-1][j] > suma)
                {
                    T[i][j] = T[i-1][j];
                    aux1 = i;
                    aux2 = j;
                }
                else
                {
                    T[i][j] = suma;
                    aux1 = i;
                    aux2 = j;
                }
            }
        }
    }
    return T[aux1][aux2];
}
int main()
{
    int mochila_capacidad,n_objetos,i;

    cout << "Andres Perez Leonis" << endl << "Emilio Gonzalez" << endl << "Bryan Grisales" << endl;



    cout << "Capacidad de la mochila: " << endl;

    cin >> mochila_capacidad;

    cout << "Numero de objetos: " << endl;

    cin >> n_objetos;

    int* P = new int[n_objetos+1];
    int* V = new int[n_objetos+1];

    for(i=1; i<= n_objetos; i++)
    {
        cout << "Indique el peso del objeto " << i << " : " << endl;

        cin >> P[i];

        cout << "Valor del objeto " << i << " : " << endl;

        cin >> V[i];
    }
    cout << "valor max posible: " << mochila(mochila_capacidad,n_objetos,P,V) << endl;
}

*/
