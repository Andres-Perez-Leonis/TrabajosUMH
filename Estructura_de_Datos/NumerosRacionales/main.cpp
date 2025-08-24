#include <iostream>

using namespace std;

typedef struct {
    int numerador;
    int denominador;
}RACIONAL;


void SimplificarRacional(int numerador, int denominador) {

    int aux = 2;

    if(numerador%denominador == 0) {
        cout << "El resultado es: " << numerador/denominador << endl;
    }else{
        while(aux < denominador) {
            if(numerador%aux == 0 && denominador%aux == 0) {
                numerador = numerador/aux;
                denominador = denominador/aux;
                aux = 2;
            }
            aux++;
        }
        cout << "El resultado es: " << numerador << "/" << denominador << endl;
    }
}

void Equivalencia(int a, int b, int c, int d) {
    if(a*d == b*c) cout << "Los numeros son equivalentes" << endl;
    else cout << "Los numeros no son equivalentes" << endl;
}

void Orden(int a, int b, int c, int d) {
    if(a*d < b*c) cout << a << "/" << b << "<" << c << "/" << d << endl;
    else cout << a << "/" << b << ">" << c << "/" << d << endl;
}

void SumaRacionales(int a, int b, int c, int d) {
    SimplificarRacional(a*d+c*b, b*d);
}

void RestaRacionales(int a, int b, int c, int d) {
    SimplificarRacional(a*d-c*b, b*d);
}

void MultiplicarRacionales(int a, int b, int c, int d) {
    SimplificarRacional(a*c, b*d);
}

void DividirRacionales(int a, int b, int c, int d) {
    SimplificarRacional(a*d, b*c);
}


int main()
{
    int opcion;
    int a, b, c, d;
    cout << "1. Simplificar un racional introducido por teclado" << endl;
    cout << "2. Determinar si dos racionales son equivalentes" << endl;
    cout << "3. Determinar el orden entre dos racionales" << endl;
    cout << "4. Sumar dos racionales introducidos por teclado" << endl;
    cout << "5. Restar dos racionales introducidos por teclado" << endl;
    cout << "6. Multiplicar dos racionales introducidos por teclado" << endl;
    cout << "7. Dividir dos racionales introducidos por teclado" << endl;
    cout << "8. Salir" << endl;

    while(true) {
        cout << "Elige una opcion: ";
        cin >> opcion;
        switch(opcion) {
            case 1:
                cout << "Introduce el numerador: ";
                cin >> a;
                cout << "Introduce el denominador: ";
                cin >> b;
                if(b == 0) {
                    cout << "No coloque un 0 como denominador" << endl;
                    continue;
                }
                SimplificarRacional(a, b);
                break;

            case 2:
                cout << "Introduce el primer numerador: ";
                cin >> a;
                cout << "Introduce el primer denominador: ";
                cin >> b;
                cout << "Introduce el segundo numerador: ";
                cin >> c;
                cout << "Introduce el segundo denominador: ";
                cin >> d;
                if(b == 0 || d == 0) {
                    cout << "No coloque un 0 como denominador" << endl;
                    continue;
                }
                Equivalencia(a,b,c,d);
                break;

            case 3:
                cout << "Introduce el primer numerador: ";
                cin >> a;
                cout << "Introduce el primer denominador: ";
                cin >> b;
                cout << "Introduce el segundo numerador: ";
                cin >> c;
                cout << "Introduce el segundo denominador: ";
                cin >> d;
                if(b == 0 || d == 0) {
                    cout << "No coloque un 0 como denominador" << endl;
                    continue;
                }
                Orden(a,b,c,d);
                break;

            case 4:
                cout << "Introduce el primer numerador: ";
                cin >> a;
                cout << "Introduce el primer denominador: ";
                cin >> b;
                cout << "Introduce el segundo numerador: ";
                cin >> c;
                cout << "Introduce el segundo denominador: ";
                cin >> d;
                if(b == 0 || d == 0) {
                    cout << "No coloque un 0 como denominador" << endl;
                    continue;
                }
                SumaRacionales(a,b,c,d);
                break;

            case 5:
                cout << "Introduce el primer numerador: ";
                cin >> a;
                cout << "Introduce el primer denominador: ";
                cin >> b;
                cout << "Introduce el segundo numerador: ";
                cin >> c;
                cout << "Introduce el segundo denominador: ";
                cin >> d;
                if(b == 0 || d == 0) {
                    cout << "No coloque un 0 como denominador" << endl;
                    continue;
                }
                RestaRacionales(a,b,c,d);
                break;

            case 6:
                cout << "Introduce el primer numerador: ";
                cin >> a;
                cout << "Introduce el primer denominador: ";
                cin >> b;
                cout << "Introduce el segundo numerador: ";
                cin >> c;
                cout << "Introduce el segundo denominador: ";
                cin >> d;
                if(b == 0 || d == 0) {
                    cout << "No coloque un 0 como denominador" << endl;
                    continue;
                }
                MultiplicarRacionales(a,b,c,d);
                break;

            case 7:
                cout << "Introduce el primer numerador: ";
                cin >> a;
                cout << "Introduce el primer denominador: ";
                cin >> b;
                cout << "Introduce el segundo numerador: ";
                cin >> c;
                cout << "Introduce el segundo denominador: ";
                cin >> d;
                if(b == 0 || d == 0) {
                    cout << "No coloque un 0 como denominador" << endl;
                    continue;
                }
                DividirRacionales(a,b,c,d);
                break;

            case 8:
                return 0;
        }
    }
}
