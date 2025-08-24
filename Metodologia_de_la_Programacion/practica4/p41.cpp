
#include <string.h>
#include <stack>
using namespace std;

void RepresentacionBinaria(int numero){
    stack <int> pila;
    int dato;
    pila.push((numero%2 == 0 ? 0 : 1));
    numero /= 2;

    if(numero != 0)
        RepresentacionBinaria(numero);
    else
        cout << "La representacion binaria es: ";
         while (! pila.empty() )
         {
            dato = pila.top();
            cout << dato << " ";
            pila.pop();
         }

}



int main()
{

    cout << "Andres Perez" << endl << "Emilio Gonzalez" << endl << "Bryan Grisales" << endl;
    int n;
    cout << "Introduce un numero: ";
    cin >> n;
    if(n < 0)
        cout << "-1" << endl;
    else
        RepresentacionBinaria(n);

    return 0;
}

