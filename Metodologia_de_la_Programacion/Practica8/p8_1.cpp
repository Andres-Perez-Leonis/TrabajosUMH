/*
#include <iostream>

using namespace std;

int CalcularSuma(int *x, int *Vvalores,int k) {
    int valor = 0;
    for(int i = 1; i <= k; i++) {
        if(x[i] == 1) valor += Vvalores[i];
    }
    return valor;
}

void Mochila(int pesoTotal, int *pesos, int *valores, int *x, int k, int *Xoptimo, int &Voptimo, int n) {
    int peso, valor;
    if(k <= n) {
        for (int i = 0; i <= 1; i++) {
            x[k] = i;
            for(int j = 1; j <= n; j++) {
                cout << " " << x[j];
            }
            cout << endl;
            peso = CalcularSuma(x,pesos, k);
            if(peso <= pesoTotal) {
                if(k == n) {
                    valor = CalcularSuma(x, valores, k);
                    if(valor > Voptimo) {
                        for(int i = 1; i <= n; i++) {
                            Xoptimo[i] = x[i];
                        }
                        Voptimo = valor;
                    }
                } else {
                    Mochila(pesoTotal, pesos, valores, x, k+1, Xoptimo, Voptimo, n);
                }
            }
        }
    }
}

int main()
{
    int Nobjetos, pesoTotal;
    int k = 1;
    int mejorValor = -1;
    int *pesos, *valores, *x;
    cout << endl << "Andres Perez - " << "Emilio Gonzalez - " << "Bryan Grisales" << endl;
    cout << "Indique la cantidad de objetos que hay: ";
    cin >> Nobjetos;
    pesos = new int[Nobjetos + 1];
    valores = new int[Nobjetos + 1];
    for(int i = 1; i <= Nobjetos; i++) {
        cout << "Indique el peso del objeto " << i << ": ";
        cin >> pesos[i];
        cout << "Indique el valor del objeto " << i << ": ";
        cin >> valores[i];
    }
    cout << "Indique el peso que aguanta la mochila: ";
    cin >> pesoTotal;
    x = new int[Nobjetos + 1];
    int *Xoptimo = new int[Nobjetos + 1];
    Mochila(pesoTotal,pesos, valores,x,k,Xoptimo, mejorValor, Nobjetos);

    for(int i = 1; i <= Nobjetos; i++) {
        if(Xoptimo[i] == 1) {
            cout << "Se ha introducido el objeto " << i << endl;
        }
    }
    cout << "El valor optimo es: " << mejorValor << endl;
}
*/
