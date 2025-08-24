
#include <iostream>
#include <string.h>
#include <stack>
using namespace std;

float p42Recursivo(float x, int n) {
    float r;
    if(n == 0) {
        r = 1;
    }else {
        if(n%2 != 0) {
                r = x * p42Recursivo(x, n-1);
        }else {
            r = p42Recursivo(x, n/2);
            r *= r;
        }
    }
    return r;
}

float p42Iterativo(float x, int n) {
    stack <float> pila;
    int i = n;
    float s;
    int dato;
    while(i != 0) {
        pila.push(i);
        if(i%2 != 0)
            i--;
        else
            i /= 2;
    }
    s = 1;
    while(!pila.empty()) {
        dato = pila.top();
        pila.pop();
        if(dato%2 == 0)
            s *= s;
        else
            s *= x;
    }
    return s;
}


int main()
{
    int n;
    float x;

    cout << "Andres Perez" << endl << "Emilio Gonzalez" << endl << "Bryan Grisales" << endl;
    cout << "Introduce un numero: ";
    cin >> x;
    cout << "Introduce n: ";
    cin >> n;
    if(n < 0)
        cout << "ERROR" << endl;
    else {
        cout << "La solucion de forma recursiva: " << p42Recursivo(x,n) << endl;
        cout << "La solucion de forma iterativa: " << p42Iterativo(x,n) << endl;
    }


    return 0;
}

