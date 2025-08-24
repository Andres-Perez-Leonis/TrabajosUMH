#include <iostream>
#include <iterator>
#include <time.h>

#include <sstream>

using namespace std;

void Numeros1A10() {
    for(int i = 0; i < 10; i++) {
        cout << rand()%(10 + 1) << endl;
    }
}

void Numeros100A200() {
    for(int i = 0; i < 10; i++) {
        cout <<  100 + rand()%(200-100+1) << endl;
    }
}

void Numeros1A100000() {
    for(int i = 0; i < 1000; i++) {
        cout << rand()%(100000 + 1) << endl;
    }
}

void NumeroAleatorioDeterminado()
 {
     int posiblesNumeros[10] = {8, 34, 89, 3, 126, 87, 987, 32, 10000, 665};
     cout << posiblesNumeros[rand()%(10+1)] << endl;
 }


bool Primo(int n) {
    for (int i = 2; i < (n/2)+1; i++) {
        if(n % i == 0) return false;
    }
    return true;
}

void NumerosPrimos(){
    int numero;
    for(int i = 0; i < 10; i++) {
        numero = rand()%(1000 + 1);
        if(!Primo(numero)) {
            i--;
            continue;
        }
        cout << numero << endl;
    }
}

void AdivinaElNumero() {
    int numero, intento = 0, numeroElegido, nIntentos = 3;

    numero = 1 + rand()%(10 + 1);

    for(int i = 0; i < nIntentos; i++) {
        cout << "Elige un numero: " << endl;
        cin >> numeroElegido;
        if(numero != numeroElegido)
            cout << "Fallaste. Vuelve a intentarlo." << endl;
            if(i == 3) cout << "El numero era: " << numero << endl;
        else {
            cout << "Felicidades Acertaste" << endl;
            break;
        }
    }
}

void ApuestaQuinela() {
    int num;
    for(int i = 0; i <= 14; i++) {
        num = rand()%3;

        switch(num){
        case 0:
            cout << "X" << endl;
            break;

        case 1:
            cout << "1" << endl;
            break;

        case 2:
            cout << "2" << endl;
            break;
        }
    }
}


void BonoLoto() {
    int numeros[6], numero, numeroReintegro, contador = 0;
    int aux = 0;
    numeroReintegro = rand()%(49 + 1);
    while(contador != 6) {
        numero = rand()%(49 + 1);
        for(int i = 0; i < 6; i++) {
            if(numero == numeros[i] || numero == numeroReintegro)
                aux++;
        }

        if(aux == 0)
            numeros[contador] = numero;
        else
            contador--;

        contador++;
        aux = 0;

    }

    cout << "La Apuesta sera: " << endl;
    for(int i = 0; i < 6; i++) {
        cout << numeros[i] << "  ";
    }
    cout << endl << "Y el numero Reintegro sera: " << numeroReintegro;

}

void Matriculas() {

    char letras[20] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'O','P','Q','R','S','T'};

    cout << "Las matriculas generadas son: " << endl;





}


int main()
{
    int opcion;
    cout << "1. 10 numeros aleatorios de 1 a N" << endl;
    cout << "2. 10 numeros aleatorios entre 100 y 200" << endl;
    cout << "3. 1000 numeros aleatorios entre 1 y 100000" << endl;
    cout << "4. Numero aleatorio con valor determinado" << endl;
    cout << "5. 10 numeros primos aleatorios entre 1 y 1000" << endl;
    cout << "6. Adivinar el numero entre 1 y 10" << endl;
    cout << "7. 14 Quinelas" << endl;
    cout << "8. Apuesta de quinela" << endl;
    cout << "9. Generar 10 matriculas de coche" << endl;
    cout << "10. Salir" << endl;

    srand(time(NULL));

    while(true){

        cout << endl << "Cual es su opcion: " << endl;
        cin >> opcion;

        switch(opcion){
            case 1:
                Numeros1A10();
                break;

            case 2:
                Numeros100A200();
                break;

            case 3:
                Numeros1A100000();
                break;

            case 4:
                NumeroAleatorioDeterminado();
                break;

            case 5:
                NumerosPrimos();
                break;

            case 6:
                AdivinaElNumero();
                break;

            case 7:
                ApuestaQuinela();
                break;

            case 8:
                BonoLoto();
                break;

            case 9:
                Matriculas();
                break;

            case 10:
                return 0;
        }
    }

}
