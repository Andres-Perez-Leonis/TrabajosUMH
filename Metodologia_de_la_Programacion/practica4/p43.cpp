
#include <iostream>
#include <string.h>
#include <stack>
using namespace std;


int p43Recursiva(int x, int y){
    if (x <= 4){
        return x+y;
    }
    else{
        x=x-4;
        y=y/3;
    }
    return p43Recursiva(x, y) + x*y;
}

int p43Iterativa(int x, int y) {
    int resultado;
    stack <float> pilay;

    if(x <= 4)
        return resultado;

    while(!(x <= 4)) {
        pilay.push(y);
        x -= 4;
        y /= 3;
    }
    resultado = x + y;
    while(!pilay.empty()) {
        resultado += x * y;
        x += 4;
        y = pilay.top();
        pilay.pop();
    }
    return resultado;
}


int main(){
    int x;
    int y;

    cout << "Andres Perez" << endl << "Emilio Gonzalez" << endl << "Bryan Grisales" << endl;
    cout << "Introduzca un numero 'x': ";
    cin>> x;
    cout<< "Introduzca un numero 'y': ";
    cin>> y;
    cout << "Solucion Recursiva: " << p43Recursiva(x,y) << endl;
    cout << "Solucion Iterativa: " << p43Iterativa(x,y) << endl;

    return(0);
}

