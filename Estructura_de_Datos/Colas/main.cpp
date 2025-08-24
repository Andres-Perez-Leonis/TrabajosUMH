#include <iostream>
#include "libreria.h"
#include <time.h>
#include <string>
#include <Windows.h>
#include <unistd.h>
using namespace std;

int main()
{
    int suceso, eleccion = 0, iteracion = 0, Ncola;
    string Npasaporte;
    srand(time(NULL));
/*
    Pasajero *nodo = new Pasajero;
    Pasajero *pasajero;
    nodo -> Npasaporte = "75hhif23";
    nodo -> Nombre = "Pedro";
    nodo -> Tipo = 1;
    nodo -> nacionalidad = Espana;
    nodo -> EstadoPasaporte = true;
*/
    LaCola UE = CrearCola();
    LaCola Britanicos = CrearCola();
    LaCola AcuerdoUE = CrearCola();
    LaCola ExtraComunitarios = CrearCola();
//    InsertarEnCola(UE,nodo);




    while(eleccion != 6) {

        if(ColaVacia(UE) || ColaVacia(Britanicos)|| ColaVacia(AcuerdoUE) || ColaVacia(ExtraComunitarios)) {
            for(int i = 0; i < 3; i++) GenerarPasajero(UE,Britanicos, AcuerdoUE, ExtraComunitarios,1);
            for(int i = 0; i < 3; i++) GenerarPasajero(Britanicos,UE, AcuerdoUE, ExtraComunitarios,2);
            for(int i = 0; i < 3; i++) GenerarPasajero(AcuerdoUE,Britanicos, UE, ExtraComunitarios,3);
            for(int i = 0; i < 3; i++) GenerarPasajero(ExtraComunitarios,Britanicos, AcuerdoUE, UE,4);
        }


        cout << endl << endl << "Elija una opcion: " << endl;
        cout << "1. Introducir un pasajero en una cola" << endl;
        cout << "2. Sacar el primer pasajero de una cola" << endl;
        cout << "3. Imprimir una cola" << endl;
        cout << "4. Consultar el pasajero de una cola" << endl;
        cout << "5. Iniciar Simulacion" << endl;
        cout << "6. Salir de la aplicacion" << endl;
        cout << "[*]:> ";
        cin >> eleccion;
        cout << endl << endl;
        switch(eleccion) {

            case 1:
                cout << "Indique en que cola quiere introducirlo: " << endl;
                cout << "1. UE" << endl << "2. Britanico" << endl << "3. AcuerdoUE" << endl << "4. ExtraComunitarios" << endl << "[*]:>";
                cin >> eleccion;
                if(eleccion == 1) PedirDatos(UE,Britanicos, AcuerdoUE, ExtraComunitarios, eleccion);
                else if(eleccion == 2) PedirDatos(Britanicos,UE, AcuerdoUE, ExtraComunitarios, eleccion);
                else if(eleccion == 3) PedirDatos(AcuerdoUE,Britanicos, UE, ExtraComunitarios, eleccion);
                else PedirDatos(ExtraComunitarios,Britanicos, AcuerdoUE, UE, eleccion);

                break;

            case 2:
                cout << "Indique de que cola quiere sacarlo: " << endl;
                cout << "1. UE" << endl << "2. Britanico" << endl << "3. AcuerdoUE" << endl << "4. ExtraComunitarios" << endl << "[*]:>";
                cin >> eleccion;
                if(eleccion == 1) SacarDeCola(UE);
                else if(eleccion == 2) SacarDeCola(Britanicos);
                else if(eleccion == 3) SacarDeCola(AcuerdoUE);
                else SacarDeCola(ExtraComunitarios);

                break;

            case 3:
                cout << "Indique cual cola quiere ver: " << endl;
                cout << "1. UE" << endl << "2. Britanico" << endl << "3. AcuerdoUE" << endl << "4. ExtraComunitarios" << endl << "[*]:>";
                cin >> eleccion;
                if(eleccion == 1) VerCola(UE);
                else if(eleccion == 2) VerCola(Britanicos);
                else if(eleccion == 3) VerCola(AcuerdoUE);
                else VerCola(ExtraComunitarios);

                break;

            case 4:
                cout << "Determine el Numero de Pasaporte que quiere buscar: ";
                cin >> Npasaporte;
                cout << endl;
                BuscarPasajero(UE, Britanicos, AcuerdoUE, ExtraComunitarios,Npasaporte);

                break;

            case 5:

                VerTodasCola(UE, Britanicos, AcuerdoUE, ExtraComunitarios);
                sleep(5);
                while(!ColaVacia(UE) || !ColaVacia(Britanicos)|| !ColaVacia(AcuerdoUE) || !ColaVacia(ExtraComunitarios)) {
                    suceso = 1 + rand()%(4);
                while(ComprobarCola(UE,Britanicos,AcuerdoUE,ExtraComunitarios, suceso)) suceso = 1 + rand()%(4);

                    if(suceso == 1 && !ColaVacia(UE)) Suceso(UE);
                    else if(suceso == 2 && !ColaVacia(Britanicos))Suceso(Britanicos);
                    else if(suceso == 3 && !ColaVacia(AcuerdoUE)) Suceso(AcuerdoUE);
                    else if(suceso == 4 && !ColaVacia(ExtraComunitarios)) Suceso(ExtraComunitarios);

                    Ncola = 1 + rand()%4;
                    if(Ncola == 1) GenerarPasajero(UE,Britanicos, AcuerdoUE, ExtraComunitarios,1);
                    else if(Ncola == 2) GenerarPasajero(Britanicos,UE, AcuerdoUE, ExtraComunitarios,2);
                    else if(Ncola == 3) GenerarPasajero(AcuerdoUE,Britanicos, UE, ExtraComunitarios,3);
                    else if(Ncola == 4)GenerarPasajero(ExtraComunitarios,Britanicos, AcuerdoUE, UE,4);

                    cout << endl << "Llega un pasajero a la cola " << DeterminarTipo(Ncola) << endl << endl;
                    iteracion++;

                    VerTodasCola(UE, Britanicos, AcuerdoUE, ExtraComunitarios);
                    if(iteracion > 29) return 0;
                    sleep(5);
                }
                break;
        }


    }

    //InsertarEnCola(UE, nodo);
    //pasajero = PedirPasajero(UE);
    //InsertarEnCola(UE,pasajero);

    return 0;
}
