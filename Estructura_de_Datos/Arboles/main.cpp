#include <iostream>
#include "libreria.h"
#include <windows.h>
#include <time.h>
#include <unistd.h>
using namespace std;

/*
typedef struct nodoCola {

};

int GradoArbol(nodoArbol nodo) {
    if(nodo == NULL) return 0;
    else return (1 + GradoArbol(nodo -> izq) + GradoArbol(nodo -> der));
}


void InsertarArbolRandom(Arbol arbol, int valor) {
    int num;
    srand(time(NULL));
    for(int i = 1; i <= valor; i++) {
        num = rand() % (valor*2);
        InsertarClaveArbol(arbol, num);

    }
}

typedef struct nodoA {
    int clave;
    struct nodoA *izq, *der;
}*nodoArbol;

typedef struct Tree {
    struct nodoA *raiz;
}*Arbol;

Arbol CrearArbol() {
    Arbol ar = new struct Tree;
    ar -> raiz = new struct nodoA;
    ar -> raiz -> izq = ar -> raiz -> der = NULL;
    ar -> raiz -> clave = -1;
    return ar;
}

bool ArbolVacio(Arbol arbol) {
    return arbol -> raiz -> clave == -1;
}
void InsertarClaveArbol(Arbol arbol, int clave) {

    struct nodoA *nodoPadre = new struct nodoA, *nodoAux = new struct nodoA;

    nodoPadre = NULL;
    nodoAux = arbol -> raiz;



    if(ArbolVacio(arbol)) {
        arbol -> raiz -> clave = clave;
        return;
    }

    while(nodoAux != NULL && nodoAux -> clave != clave) {
        nodoPadre = nodoAux;
        if(clave < nodoAux -> clave) nodoAux = nodoAux -> izq;
        else nodoAux = nodoAux -> der;
    }

    if(nodoAux != NULL) {
        cout << "No se puede introducir elementos iguales" << endl << endl;
        return;
    }

    struct nodoA *nodo = new struct nodoA;
    if(clave < nodoPadre -> clave) {
        nodoPadre -> izq = nodo;
        nodo -> clave = clave;
        nodo -> izq = nodo -> der = NULL;
    }else {

        nodoPadre -> der = nodo;
        nodo -> clave = clave;
        nodo -> izq = nodo -> der = NULL;

    }

}

bool BusquedaValorArbol(nodoArbol nodo, int valor) {
    if(nodo == NULL) return false;
    else {
        if(nodo -> clave == clave) return true;
        else {
            if(nodo -> clave < clave) return (BusquedaValorArbol(nodo -> der, valor));
            else return (BusquedaValorArbol(nodo -> izq, clave));
        }
    }
}
*/




/*

    A -> REALIZADO
    B -> REALIZADO
    C -> REALIZADO
    D -> REALIZADO
    E -> REALIZADO
    F -> REALIZADO
    G -> REALIZADO
    H -> REALIZADO







*/






int main()
{
    int suceso, eleccion = 0, iteracion = 0, NArbol, NumeroPasajeros, NumeroArbol, alt;
    nodoArbol *nodo, *nodo1, *nodoAux = NULL;
    string PasaporteBusca;
    string Npasaporte;
    string a = "BA1234AA";
    srand(time(NULL));
/*
    nodoArbol *nodo = new nodoArbol;
    Pasajero *pasajero;
    nodo -> Npasaporte = "AA1234AA";
    nodo -> Nombre = "Pedro";
    nodo -> Tipo = 1;
    nodo -> nacionalidad = Espana;
    nodo -> EstadoPasaporte = true;

*/
    Arbol UE = CrearArbol();
    Arbol Britanicos = CrearArbol();
    Arbol AcuerdoUE = CrearArbol();
    Arbol ExtraComunitarios = CrearArbol();

/*

    EntreOrdenArbol(UE -> raiz);
    nodo = BuscarNodoInterno(UE -> raiz);
    ImprimirDatosNodo(nodo);
    cout << endl << endl;
    cout << "Introduce el pasaporte: ";
    cin >> PasaporteBusca;
    nodo1 = EliminarNodoArbol(UE -> raiz, PasaporteBusca);
    delete(nodo1);
    EntreOrdenArbol(UE -> raiz);


*/


    while(eleccion != 8) {







        cout << endl << endl << "Elija una opcion: " << endl;
        cout << "1. Introducir un pasajero en un arbol" << endl;
        cout << "2. Buscar pasajero" << endl;
        cout << "3. Imprimir un arbol " << endl;
        cout << "4. Sacar un pasajero" << endl;
        cout << "5. Introducir un numero y generar pasajeros aleatorios " << endl;
        cout << "6. Introducir un numero y eliminar pasajeros aleatorios " << endl;
        cout << "7. Iniciar Simulacion " << endl;
        cout << "8. Salir de la aplicacion" << endl;
        cout << "[*]:> ";
        cin >> eleccion;
        cout << endl << endl;

        switch(eleccion) {

            case 1:
                cout << "Indique en que arbol quiere introducirlo: " << endl;
                cout << "1. UE" << endl << "2. Britanico" << endl << "3. AcuerdoUE" << endl << "4. ExtraComunitarios" << endl << "[*]:>";
                cin >> eleccion;

                if(eleccion == 1) PedirDatosNodoArbol(UE,Britanicos, AcuerdoUE, ExtraComunitarios, eleccion);
                else if(eleccion == 2) PedirDatosNodoArbol(Britanicos,UE, AcuerdoUE, ExtraComunitarios, eleccion);
                else if(eleccion == 3) PedirDatosNodoArbol(AcuerdoUE,Britanicos, UE, ExtraComunitarios, eleccion);
                else PedirDatosNodoArbol(ExtraComunitarios,Britanicos, AcuerdoUE, UE, eleccion);

                break;

            case 2:

                cout << "Indique de que arbol quiere buscarlo: " << endl;
                cout << "1. UE" << endl << "2. Britanico" << endl << "3. AcuerdoUE" << endl << "4. ExtraComunitarios" << endl << "[*]:>";
                cin >> eleccion;

                cout << endl << "Introduzca el pasaporte que quiere buscar: ";
                cin >> PasaporteBusca;
                cout << endl << endl;
                if(eleccion == 1) {
                    nodo = BusquedaPajero(UE -> raiz, PasaporteBusca);
                    if(nodo == NULL) cout << "No existe el pasajero" << endl;
                    else ImprimirDatosNodo(nodo);
                }else if(eleccion == 2) {
                    nodo = BusquedaPajero(Britanicos -> raiz, PasaporteBusca);
                    if(nodo == NULL) cout << "No existe el pasajero" << endl;
                    else ImprimirDatosNodo(nodo);;
                }else if(eleccion == 3) {
                    nodo = BusquedaPajero(AcuerdoUE -> raiz, PasaporteBusca);
                    if(nodo == NULL) cout << "No existe el pasajero" << endl;
                    else ImprimirDatosNodo(nodo);
                }else {
                    nodo = BusquedaPajero(ExtraComunitarios -> raiz, PasaporteBusca);
                    if(nodo == NULL) cout << "No existe el pasajero" << endl;
                    else ImprimirDatosNodo(nodo);
                }
                break;

            case 3:
                cout << "Indique de que arbol quiere ver: " << endl;
                cout << "1. UE" << endl << "2. Britanico" << endl << "3. AcuerdoUE" << endl << "4. ExtraComunitarios" << endl << "[*]:>";
                cin >> eleccion;
                cout << endl << "Como quiere verlo: " << endl;
                cout << "1. EntreOrden" << endl << "2. PostOrden" << endl << "3. Indorden" <<  endl;
                cout << "[*]:> ";
                cin >> alt;
                if(eleccion == 1) {
                        if(alt == 1) {
                            EntreOrdenArbol3(UE -> raiz);
                        }else if(alt == 2) {
                            EntreOrdenArbol2(UE -> raiz);
                        }else if(alt == 3){
                            EntreOrdenArbol(UE -> raiz);
                        }
                }else if(eleccion == 2) {
                        if(alt == 1) {
                            EntreOrdenArbol3(Britanicos -> raiz);
                        }else if(alt == 2) {
                            EntreOrdenArbol2(Britanicos -> raiz);
                        }else if(alt == 3){
                            EntreOrdenArbol(Britanicos -> raiz);
                        }
                }else if(eleccion == 3) {
                        if(alt == 1) {
                            EntreOrdenArbol3(AcuerdoUE -> raiz);
                        }else if(alt == 2) {
                            EntreOrdenArbol2(AcuerdoUE -> raiz);
                        }else if(alt == 3){
                            EntreOrdenArbol(AcuerdoUE -> raiz);
                        }
                }else if(eleccion == 4) {
                        if(alt == 1) {
                            EntreOrdenArbol3(ExtraComunitarios -> raiz);
                        }else if(alt == 2) {
                            EntreOrdenArbol2(ExtraComunitarios -> raiz);
                        }else if(alt == 3){
                            EntreOrdenArbol(ExtraComunitarios -> raiz);
                        }
                }


                break;

            case 4:

                cout << "Indique de que arbol quiere sacarlo: " << endl;
                cout << "1. UE" << endl << "2. Britanico" << endl << "3. AcuerdoUE" << endl << "4. ExtraComunitarios" << endl << "[*]:>";
                cin >> eleccion;
                cout << "Indique el pasajero que quiere sacar: ";
                cin >> Npasaporte;
                cout << endl;
                if(eleccion == 1) nodoEliminar(UE -> raiz, Npasaporte);
                else if(eleccion == 2) nodoEliminar(Britanicos -> raiz, Npasaporte);
                else if(eleccion == 3) nodoEliminar(AcuerdoUE -> raiz, Npasaporte);
                else if(eleccion == 4) nodoEliminar(ExtraComunitarios -> raiz, Npasaporte);

                break;

            case 5:

                 cout << "Indique cuantos pasajeros quiere generar: ";
                cin >> NumeroPasajeros;

                for(int i = 0; i < NumeroPasajeros; i++) {
                    NumeroArbol = 1 + rand()%4;
                    if(NumeroArbol == 1) GenerarPasajero1(UE,Britanicos, AcuerdoUE, ExtraComunitarios, 1);
                    else if(NumeroArbol == 2) GenerarPasajero1(Britanicos,UE, AcuerdoUE, ExtraComunitarios, 2);
                    else if(NumeroArbol == 3) GenerarPasajero1(AcuerdoUE,Britanicos, UE, ExtraComunitarios, 3);
                    else GenerarPasajero1(ExtraComunitarios,Britanicos, AcuerdoUE, UE, 4);
                }

                break;




            case 6:

                cout << "Indique cuantos pasajeros quiere sacar: ";
                cin >> NumeroPasajeros;

                for(int i = 0; i < NumeroPasajeros; i++) {
                    NumeroArbol = 1 + rand()%4;
                    if(NumeroArbol == 1) delete(EliminarNodoArbol(UE -> raiz, GenerarPasaporte()));
                    else if(NumeroArbol == 2) delete(EliminarNodoArbol(Britanicos -> raiz, GenerarPasaporte()));
                    else if(NumeroArbol == 3) delete(EliminarNodoArbol(AcuerdoUE -> raiz, GenerarPasaporte()));
                    else if(NumeroArbol == 4) delete(EliminarNodoArbol(ExtraComunitarios -> raiz, GenerarPasaporte()));
                }


                break;


            case 7:



                MostrarArboles(UE, Britanicos, AcuerdoUE, ExtraComunitarios);
                sleep(5);
                while(!ArbolVacio(UE) || !ArbolVacio(Britanicos)|| !ArbolVacio(AcuerdoUE) || !ArbolVacio(ExtraComunitarios)) {
                    suceso = 1 + rand()%(4);
                    while(ComprobarArbol(UE,Britanicos,AcuerdoUE,ExtraComunitarios, suceso)) suceso = 1 + rand()%(4);


                        nodo1 = BuscarNodoAleatorio(suceso, UE, Britanicos, AcuerdoUE, ExtraComunitarios);



                        if(nodo1 -> EstadoPasaporte == true) cout << "Procesamiento OK Pasajero " << nodo1 -> Npasaporte << endl;
                        else {
                            cout << "Procesamiento KO Pasajero " << nodo1 -> Npasaporte << endl;
                            nodo1 -> EstadoPasaporte = true;
                            iteracion++;
                            continue;
                        }




                        if(nodo1 == NULL) continue;

                        if(suceso == 1 && !ArbolVacio(UE)) {

                            nodoEliminar(UE -> raiz, nodo1 -> Npasaporte);

                        }else if(suceso == 2 && !ArbolVacio(Britanicos)) {

                            nodoEliminar(Britanicos -> raiz, nodo1 -> Npasaporte);

                        }else if(suceso == 3 && !ArbolVacio(AcuerdoUE)) {

                            nodoEliminar(AcuerdoUE -> raiz, nodo1 -> Npasaporte);

                        }else if(suceso == 4 && !ArbolVacio(ExtraComunitarios))  {

                            nodoEliminar(ExtraComunitarios -> raiz, nodo1 -> Npasaporte);

                        } else {

                            NumeroArbol = 1 + rand()%4;
                            if(NumeroArbol == 1) {
                                Npasaporte = GenerarPasaporte();
                                if(!ComprobarExistenciaPasaporte1(UE, Britanicos, AcuerdoUE, ExtraComunitarios, Npasaporte)) {
                                    MeterNodo(UE -> raiz, NULL, Npasaporte, GenerarNombre(), GenerarNacionalidad(), GenerarEstado(), 1);
                                }
                            }else if(NumeroArbol == 2) {
                                Npasaporte = GenerarPasaporte();
                                if(!ComprobarExistenciaPasaporte1(UE, Britanicos, AcuerdoUE, ExtraComunitarios, Npasaporte)) {
                                    MeterNodo(Britanicos -> raiz, NULL, Npasaporte, GenerarNombre(), GenerarNacionalidad(), GenerarEstado(), 2);
                                }
                            }else if(NumeroArbol == 3) {
                                Npasaporte = GenerarPasaporte();
                                if(!ComprobarExistenciaPasaporte1(UE, Britanicos, AcuerdoUE, ExtraComunitarios, Npasaporte)) {
                                    MeterNodo(AcuerdoUE -> raiz, NULL, Npasaporte, GenerarNombre(), GenerarNacionalidad(), GenerarEstado(), 3);
                                }
                            }else if(NumeroArbol == 4) {
                                Npasaporte = GenerarPasaporte();
                                if(!ComprobarExistenciaPasaporte1(UE, Britanicos, AcuerdoUE, ExtraComunitarios, Npasaporte)) {
                                    MeterNodo(ExtraComunitarios -> raiz, NULL, Npasaporte, GenerarNombre(), GenerarNacionalidad(), GenerarEstado(), 4);
                                }
                            }

                            cout << endl << "Llega un pasajero al Arbol " << DeterminarTipo(NumeroArbol) << endl << endl;
                        }
                    iteracion++;
                    MostrarArboles(UE, Britanicos, AcuerdoUE, ExtraComunitarios);
                    if(iteracion > 12) break;
                    sleep(5);
                }

                break;

        }


    }
    return 0;
}

