

/*
#include <iostream>
#include <string>
using namespace std;


void VerEvolucion(int n_objetos, int mochila_capacidad, int** T) {

    cout << endl << endl << "Matriz Resultante: " << endl;

    for(int i = 0; i < n_objetos + 1; i++)
    {
        for(int j = 0; j < mochila_capacidad + 1; j++)
        {
            cout << T[i][j] << " ";

        }
        cout << endl;
    }
}



int mochila(int mochila_capacidad, int n_objetos, int* pesos, int* valor_objetos, bool Estado) {
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

    if(Estado) VerEvolucion(n_objetos,mochila_capacidad, T);

    for(i = 1; i <= n_objetos; i++)
    {
        for(j = 1; j <= mochila_capacidad; j++)
        {
            if(Estado) VerEvolucion(n_objetos,mochila_capacidad, T);
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

    if(Estado) VerEvolucion(n_objetos,mochila_capacidad, T);
    return T[aux1][aux2];
}

int main()
{
    int mochila_capacidad,n_objetos,i;
    bool VerEstado;
    string Respuesta;


    cout << "Andres Perez Leonis" << endl << "Emilio Gonzalez" << endl << "Bryan Grisales" << endl;


    cout << "Capacidad de la mochila: " << endl;

    cin >> mochila_capacidad;

    cout << "Numero de objetos: " << endl;

    cin >> n_objetos;

    cout << "Quiere ver la matriz (Si/No): " << endl;
    cin >> Respuesta;
    if(Respuesta == "Si") VerEstado = true;
    else VerEstado = false;

    int* P = new int[n_objetos+1];
    int* V = new int[n_objetos+1];

    for(i=1; i<= n_objetos; i++)
    {
        cout << "Indique el peso del objeto " << i << " : " << endl;

        cin >> P[i];

        cout << "Valor del objeto " << i << " : " << endl;

        cin >> V[i];
    }
    cout << endl << "Valor max posible: " << mochila(mochila_capacidad,n_objetos,P,V, VerEstado) << endl;
}

*/

