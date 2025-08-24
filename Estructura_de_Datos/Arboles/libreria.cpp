#include "libreria.h"
#include <time.h>
#include <conio.h>
#include <string.h>


int GradoArbol(nodoArbol *nodo) {
    if(nodo == NULL) return 0;
    else return (1 + GradoArbol(nodo -> izq) + GradoArbol(nodo -> der));
}



void EntreOrdenArbol(nodoArbol *nodo) {
    if(nodo -> izq != NULL) EntreOrdenArbol(nodo -> izq);
    cout << nodo -> Npasaporte << " ";
    if(nodo -> der != NULL) EntreOrdenArbol(nodo -> der);
}

void EntreOrdenArbol2(nodoArbol *nodo) {
    if(nodo -> izq != NULL) EntreOrdenArbol(nodo -> izq);
    if(nodo -> der != NULL) EntreOrdenArbol(nodo -> der);
    cout << nodo -> Npasaporte << " ";
}


void EntreOrdenArbol3(nodoArbol *nodo) {
    cout << nodo -> Npasaporte << " ";
    if(nodo -> izq != NULL) EntreOrdenArbol(nodo -> izq);
    if(nodo -> der != NULL) EntreOrdenArbol(nodo -> der);
}

void InsertarArbolRandom(Arbol arbol, int valor) {
    srand(time(NULL));
    string Npasaporte;
    for(int i = 1; i <= valor; i++) {
        Npasaporte = GenerarPasaporte();
        //InsertarClaveArbol(arbol, num);

    }
}
/*
typedef struct nodoA {
    int clave;
    struct nodoA *izq, *der;
}*nodoArbol;

typedef struct Tree {
    struct nodoA *raiz;
}*Arbol;
*/
Arbol CrearArbol() {
    Arbol ar = new struct Tree;
    //ar -> raiz = new struct nodoA;
    //ar -> raiz -> izq = ar -> raiz -> der = NULL;
    ar -> raiz = NULL;
    //ar -> raiz -> Padre = NULL;
    return ar;
}


nodoArbol* BuscarNodoAleatorio(int Narbol, Arbol UE, Arbol Britanicos, Arbol AcuerdosUE, Arbol Extracomunitarios) {
    int TipoNodo;
    TipoNodo = 1 + rand()%3;
    if(Narbol == 1) {
        if(TipoNodo == 1) return BuscarNodoHoja(UE -> raiz);
        else if(TipoNodo == 2) return BuscarNodoConUnHijo(UE -> raiz);
        else return BuscarNodoInterno(UE -> raiz);
    }else if(Narbol == 2) {
        if(TipoNodo == 1) return BuscarNodoHoja(Britanicos -> raiz);
        else if(TipoNodo == 2) return BuscarNodoConUnHijo(Britanicos -> raiz);
        else return BuscarNodoInterno(Britanicos -> raiz);
    }else if(Narbol == 3) {
        if(TipoNodo == 1) return BuscarNodoHoja(AcuerdosUE -> raiz);
        else if(TipoNodo == 2) return BuscarNodoConUnHijo(AcuerdosUE -> raiz);
        else return BuscarNodoInterno(AcuerdosUE -> raiz);
    }else {
        if(TipoNodo == 1) return BuscarNodoHoja(Extracomunitarios -> raiz);
        else if(TipoNodo == 2) return BuscarNodoConUnHijo(Extracomunitarios -> raiz);
        else return BuscarNodoInterno(Extracomunitarios -> raiz);
    }
}



nodoArbol* Suceso(nodoArbol *nodoRaiz, nodoArbol *nodoEliminar) {
    return EliminarNodoArbol1(nodoRaiz, nodoEliminar -> Npasaporte);
}



/**
    Genera aleatoriamente la Nacionalidad para un Pasajero
*/

Nacionalidad GenerarNacionalidad() {
    int nacionalidad = rand() % (6+1);
    if(nacionalidad == 1) return Espana;
    else if(nacionalidad == 2) return Francia;
    else if(nacionalidad == 3) return Inglaterra;
    else if(nacionalidad == 4) return Alemania;
    else if(nacionalidad == 5) return Noruega;
    else if(nacionalidad == 6) return Suiza;
    return EstadosUnidos;
}

/**
    Determina a que Cola se introduce el pasajero
*/
int GenerarTipo() {
    return 1 + rand()%(4-1);
}

/**
    Determina aleatoriamente el Estado del Pasaporte del Pasajero
*/

bool GenerarEstado() {
    if(1 + rand()%2 == 1) return true;
    else return false;
}



/**
    Genera aleatoriamente un Numero de pasaporte para un Pasajero
*/

string GenerarPasaporte() {
    char Npasaporte[10];
    //char *aux;
    for(int i = 0; i < 2; i++) Npasaporte[i] = (char) (rand()%26+65);
    for(int i = 2; i < 7; i++) Npasaporte[i] = (char) (rand()%10+48);
    for(int i = 7; i < 9; i++) Npasaporte[i] = (char) (rand()%26+65);
    Npasaporte[9] = '\0';
    string tm(Npasaporte);
    return tm;
}


/**
    Genera aleatoriamente un Nombre para un Pasajero
*/
string GenerarNombre() {
    char Nombre[20];

    for(int i = 0; i < 20; i++) Nombre[i] = (char) (rand()%26+65);
    return Nombre;
}







bool ArbolVacio(Arbol arbol) {
    return (arbol -> raiz == NULL);
}

void InsertarClaveArbol(Arbol arbol, string Npasaporte, string Nombre, Nacionalidad nacionalidad, int Tipo, bool EstadoPasaporte) {

    struct nodoA *nodoPadre = new struct nodoA, *nodoAux = new struct nodoA;

    nodoPadre = NULL;
    nodoAux = arbol -> raiz;



    if(ArbolVacio(arbol)) {
            cout << "deberia entrar aqui" << endl << endl;
        nodoArbol *nodo = new nodoArbol;
        arbol -> raiz = nodo;
        nodo -> Npasaporte = Npasaporte;
        nodo -> Nombre = Nombre;
        nodo -> nacionalidad = nacionalidad;
        nodo -> Tipo = Tipo;
        nodo -> EstadoPasaporte = EstadoPasaporte;
        return;
    }

    while(nodoAux != NULL && nodoAux -> Npasaporte != Npasaporte) {
        nodoPadre = nodoAux;
        if(Npasaporte < nodoAux -> Npasaporte) nodoAux = nodoAux -> izq;
        else nodoAux = nodoAux -> der;
    }

    if(nodoAux != NULL || nodoAux -> Npasaporte == Npasaporte) {
        cout << "No se puede introducir elementos iguales" << endl << endl;
        return;
    }

    struct nodoA *nodo = new struct nodoA;
    if(Npasaporte < nodoPadre -> Npasaporte) {
        nodoPadre -> izq = nodo;
        nodo -> Npasaporte = Npasaporte;
        nodo -> Nombre = Nombre;
        nodo -> nacionalidad = nacionalidad;
        nodo -> Tipo = Tipo;
        nodo -> EstadoPasaporte = EstadoPasaporte;
        nodo -> izq = nodo -> der = NULL;
    }else {

        nodoPadre -> der = nodo;
        nodo -> Npasaporte = Npasaporte;
        nodo -> Nombre = Nombre;
        nodo -> nacionalidad = nacionalidad;
        nodo -> Tipo = Tipo;
        nodo -> EstadoPasaporte = EstadoPasaporte;
        nodo -> izq = nodo -> der = NULL;

    }

}

void ImprimirDatosNodo(nodoArbol *nodo) {
    cout << endl << "Pasaporte: " << nodo ->Npasaporte;
    cout << endl << "Nombre: " << nodo -> Nombre;
    cout << endl << "Nacionalidad: " << DeterminarNacionalidad(nodo -> nacionalidad);
    cout << endl << "Tipo: " << DeterminarTipo(nodo ->Tipo);
    cout << endl << "Estado: " << nodo  ->EstadoPasaporte;
}










void InsertarClaveArbol(Arbol arbol, nodoArbol *nodo) {

    nodoArbol *nodoPadre, *nodoAux;
    //string s1,s2;
    nodoPadre = NULL;
    nodoAux = arbol -> raiz;

    if(ArbolVacio(arbol)) {
        arbol -> raiz = nodo;
        nodo -> der = nodo -> izq = NULL;
        nodo -> Padre = nodo;
        return;
    }
    while(nodoAux != NULL && nodoAux -> Npasaporte != nodo -> Npasaporte) {

        nodoPadre = nodoAux;
        if(nodoPadre -> Npasaporte < nodo -> Npasaporte) nodoAux = nodoAux -> der;
        else nodoAux = nodoAux -> izq;
    }


    if(nodoAux != NULL || nodoPadre -> Npasaporte == nodo -> Npasaporte) {
        cout << "No se puede introducir elementos iguales" << endl << endl;
        return;
    }
    //struct nodoA *nodo = new struct nodoA;
    if(nodoPadre -> Npasaporte < nodo -> Npasaporte) {
        nodoPadre -> der = nodo;
        nodo -> izq = nodo -> der = NULL;
    }else {
        nodoPadre -> izq = nodo;
        nodo -> izq = nodo -> der = NULL;

    }
    nodo -> Padre = nodoPadre;
}


void VisualizarArbol(nodoArbol *nodo, int n) {
    if(nodo == NULL) return;
    else {
        VisualizarArbol(nodo -> der, n + 1);
        for(int i = 0; i < n; i++) {
            cout << "       ";
        }
        cout << nodo -> Npasaporte << endl;
        VisualizarArbol(nodo -> izq, n + 1);
    }
}





nodoArbol* BuscarNodoInterno(nodoArbol *nodo) {
    if(nodo -> der != NULL &&  nodo -> izq != NULL) return nodo;
    else if(nodo -> der == NULL && nodo -> izq != NULL) return BuscarNodoHoja(nodo -> izq);
    else return BuscarNodoHoja(nodo -> der);
}

nodoArbol* BuscarNodoConUnHijo(nodoArbol *nodo) {
    if((nodo -> der != NULL ||  nodo -> izq != NULL) && !(nodo -> der != NULL && nodo -> izq != NULL)) return nodo;
    else if(nodo -> der == NULL && nodo -> izq != NULL) return BuscarNodoHoja(nodo -> izq);
    else return BuscarNodoHoja(nodo -> der);
}

nodoArbol* BuscarNodoHoja(nodoArbol *nodo) {
    if(nodo -> der == NULL &&  nodo -> izq == NULL) return nodo;
    else if(nodo -> der == NULL && nodo -> izq != NULL) return BuscarNodoHoja(nodo -> izq);
    else return BuscarNodoHoja(nodo -> der);
}


void MostrarArboles(Arbol UE, Arbol Britanicos, Arbol AcuerdosUE, Arbol Extracomunitarios) {
    cout << endl << endl;
    cout << "Arbol 1: "<< endl;
    if(!ArbolVacio(UE)) EntreOrdenArbol(UE -> raiz);
    cout << endl;
    cout << "Arbol 2: "<< endl;
    if(!ArbolVacio(Britanicos)) EntreOrdenArbol(Britanicos -> raiz);
    cout << endl;
    cout << "Arbol 3: "<< endl;
    if(!ArbolVacio(AcuerdosUE)) EntreOrdenArbol(AcuerdosUE -> raiz);
    cout << endl;
    cout << "Arbol 4: "<< endl;
    if(!ArbolVacio(Extracomunitarios)) EntreOrdenArbol(Extracomunitarios -> raiz);
    cout << endl;
}


nodoArbol* EliminarNodoArbol1(nodoArbol *nodo, string Npasaporte) {

    nodoArbol *nodoPadre, *nodoAux, *nodoCambio;


    nodoPadre = NULL;
    nodoAux = nodo;
    if(nodo == NULL) return NULL;

    while(nodoAux != NULL && nodoAux -> Npasaporte != Npasaporte) {

        nodoPadre = nodoAux;
        if(nodoPadre -> Npasaporte < Npasaporte) nodoAux = nodoAux -> der;
        else nodoAux = nodoAux -> izq;
    }

    if(nodoAux == NULL) {
        cout << "No existe ese pasajero " << endl << endl;
        return NULL;
    }

    if(nodoAux -> EstadoPasaporte == true) cout << "Procesamiento OK del pasajero " << nodoAux -> Npasaporte << endl;
    else {
        cout << "Procesamiento KO del pasajero " << nodoAux -> Npasaporte << endl;
        nodoAux -> EstadoPasaporte = true;
        return NULL;
    }

    if(nodoAux -> izq == NULL && nodoAux -> der == NULL) {
        if(nodoPadre -> der != NULL && nodoPadre -> izq != NULL) {
            if(nodoPadre -> der -> Npasaporte == nodoAux -> Npasaporte) {
                nodoPadre -> der = NULL;
                return(nodoAux);
            }else {
                nodoPadre -> izq = NULL;
                return(nodoAux);
            }
        }else if(nodoPadre -> der == NULL && nodoPadre -> izq != NULL) {
            if(nodoPadre -> izq -> Npasaporte == nodoAux -> Npasaporte) {

                nodoPadre -> izq = NULL;
                return(nodoAux);
            }
        } else if(nodoPadre -> der != NULL && nodoPadre -> izq == NULL) {
            if(nodoPadre -> der -> Npasaporte == nodoAux -> Npasaporte) {

                nodoPadre -> der = NULL;
                return(nodoAux);
            }
        }
    }else if(nodoAux -> der != NULL && nodoAux -> izq != NULL) {
        while(nodoAux -> der != NULL || nodoAux -> izq != NULL) {
            nodoPadre = nodoAux;
            if(nodoAux -> der != NULL) nodoCambio = BusquedaMenorValor(nodoAux -> der);
            else nodoCambio = BusquedaMayorValor(nodoAux -> izq);


            InterCambioValores(nodoCambio, nodoAux);



            nodoAux = nodoCambio;
        }
        if(nodoAux -> der != NULL && nodoAux -> izq != NULL) cout << "No llega" << endl;

        if(nodoPadre -> der -> Npasaporte == nodoAux -> Npasaporte) nodoPadre -> der = NULL;
        else nodoPadre -> izq = NULL;

        return nodoAux;
    }else if(nodoAux -> der == NULL && nodoAux -> izq != NULL){


        if(nodoPadre -> der -> Npasaporte == nodoAux -> Npasaporte) {
            nodoPadre -> der = nodoAux -> izq;
        }else {
            nodoPadre -> izq = nodoAux -> izq;
        }

        return nodoAux;




    }else if(nodoAux -> der != NULL && nodoAux -> izq == NULL){

        if(nodoPadre -> der -> Npasaporte == nodoAux -> Npasaporte) {
            nodoPadre -> der = nodoAux -> der;
        }else {
            nodoPadre -> izq = nodoAux -> der;
        }

        return nodoAux;


    }
}




nodoArbol* EliminarNodoArbol(nodoArbol *nodo, string Npasaporte) {

    nodoArbol *nodoPadre, *nodoAux, *nodoCambio;


    //cout << nodo -> Npasaporte << endl << endl;
    nodoPadre = NULL;
    nodoAux = nodo;

    if(nodo == NULL) cout << "ALGO HA PASADO" << endl;
    if(nodo == NULL) return NULL;

    while(nodoAux != NULL && nodoAux -> Npasaporte != Npasaporte) {
        //cout << "AAAAAAAA" << endl;
        nodoPadre = nodoAux;
        if(nodoPadre -> Npasaporte < Npasaporte) nodoAux = nodoAux -> der;
        else nodoAux = nodoAux -> izq;
    }

    if(nodoAux == NULL) {
        cout << "No existe ese pasajero " << endl << endl;
        return NULL;
    }
    if(nodoAux -> izq == NULL && nodoAux -> der == NULL) {
        if(nodoPadre -> der != NULL && nodoPadre -> izq != NULL) {
            if(nodoPadre -> der -> Npasaporte == nodoAux -> Npasaporte) {
                nodoPadre -> der = NULL;
                return(nodoAux);
            }else {
                nodoPadre -> izq = NULL;
                return(nodoAux);
            }
        }else if(nodoPadre -> der == NULL && nodoPadre -> izq != NULL) {
            if(nodoPadre -> izq -> Npasaporte == nodoAux -> Npasaporte) {

                nodoPadre -> izq = NULL;
                return(nodoAux);
            }
        } else if(nodoPadre -> der != NULL && nodoPadre -> izq == NULL) {
            if(nodoPadre -> der -> Npasaporte == nodoAux -> Npasaporte) {

                nodoPadre -> der = NULL;
                return(nodoAux);
            }
        }
    }else if(nodoAux -> der != NULL && nodoAux -> izq != NULL) {



        cout << "Algo" << endl;

        while(!(nodoAux -> der == NULL && nodoAux -> izq == NULL)) {
            nodoPadre = nodoAux;
            if(nodoAux -> der != NULL) nodoCambio = BusquedaMenorValor(nodoAux -> der);
            else if(nodoAux -> izq != NULL) nodoCambio = BusquedaMenorValor(nodoAux -> izq);

            VisualizarArbol(nodo, 0);

            InterCambioValores(nodoPadre ,nodoCambio);

            nodoAux = nodoCambio;
        }

            if(nodoAux -> Padre -> der != NULL) if(nodoAux -> Padre -> der -> Npasaporte == nodoAux -> Npasaporte) cout << "Desde la derecha" << endl;
            if(nodoAux -> Padre -> izq != NULL) if(nodoAux -> Padre -> izq -> Npasaporte == nodoAux -> Npasaporte) cout << "Desde la izquierda" << endl;


            if(nodoAux -> Padre-> der -> Npasaporte == nodoAux -> Npasaporte) nodoPadre -> der = NULL;
            if(nodoAux -> Padre -> izq -> Npasaporte == nodoAux -> Npasaporte) nodoPadre -> izq = NULL;
            return nodoAux;

    }else if(nodoAux -> der == NULL && nodoAux -> izq != NULL){


        if(nodoPadre -> der -> Npasaporte == nodoAux -> Npasaporte) {
            nodoPadre -> der = nodoAux -> izq;
        }else {
            nodoPadre -> izq = nodoAux -> izq;
        }

        return nodoAux;




    }else if(nodoAux -> der != NULL && nodoAux -> izq == NULL){

        if(nodoPadre -> der -> Npasaporte == nodoAux -> Npasaporte) {
            nodoPadre -> der = nodoAux -> der;
        }else {
            nodoPadre -> izq = nodoAux -> der;
        }

        return nodoAux;


    }
}




void nodoEliminar(nodoArbol *&nodo, string Npasaporte) {
    if(nodo == NULL) return;
    else if (Npasaporte < nodo -> Npasaporte) nodoEliminar(nodo -> izq, Npasaporte);
    else if(Npasaporte > nodo -> Npasaporte) nodoEliminar(nodo -> der, Npasaporte);
    else EliminarNodo(nodo);
}

void EliminarNodo(nodoArbol *&nodo) {
    if(nodo -> der && nodo -> izq) {
        nodoArbol *nodo1 = MinimoNodo(nodo -> der);
        nodo -> Npasaporte = nodo1 -> Npasaporte;
        nodo -> Nombre = nodo1 -> Nombre;
        nodo -> nacionalidad = nodo1 -> nacionalidad;
        nodo -> EstadoPasaporte = nodo1 -> EstadoPasaporte;


        EliminarNodo(nodo1);
    }else if(nodo -> izq){
        RemplazarNodo(nodo, nodo -> izq);
    }else if(nodo -> der) {
        RemplazarNodo(nodo, nodo -> der);
    }else {
        RemplazarNodo(nodo, NULL);
    }
}

nodoArbol *CrearNodo(nodoArbol *Padre, string Npasaporte, string Nombre, Nacionalidad nacionalidad, bool EstadoPasaporte, int Tipo) {

        nodoArbol *nodo = new nodoArbol;
        nodo -> Npasaporte = Npasaporte;
        nodo -> Nombre = Nombre;
        nodo -> nacionalidad = nacionalidad;
        nodo -> EstadoPasaporte = EstadoPasaporte;
        //cout << endl << endl << pasajero ->   EstadoPasaporte << endl << endl;
        nodo -> Tipo = Tipo;
        nodo -> Padre = Padre;
        nodo -> der = nodo -> izq = NULL;
        return nodo;
   }


void MeterNodo(nodoArbol* &nodoAr, nodoArbol *Padre, string Npasaporte, string Nombre, Nacionalidad nacionalidad, bool EstadoPasaporte,int Tipo) {

    if(nodoAr == NULL) {
        nodoArbol *nodo = CrearNodo(Padre, Npasaporte, Nombre, nacionalidad, EstadoPasaporte, Tipo);
        nodoAr = nodo;
        //if(nodo -> Padre == NULL) nodoAr -> Padre = nodoAr;
    }else {
        if(Npasaporte < nodoAr -> Npasaporte) MeterNodo(nodoAr -> izq, nodoAr, Npasaporte, Nombre, nacionalidad, EstadoPasaporte, Tipo);
        else MeterNodo(nodoAr -> der, nodoAr, Npasaporte, Nombre, nacionalidad, EstadoPasaporte, Tipo);
    }
}




void RemplazarNodo(nodoArbol *nodo, nodoArbol *nodo1) {
    if(nodo -> Padre) {
        if(nodo -> Padre -> izq != NULL) {
            if(nodo -> Npasaporte == nodo -> Padre -> izq -> Npasaporte) {
                nodo -> Padre -> izq = nodo1;
            }
        }
        if(nodo -> Padre -> der != NULL) {
            if(nodo -> Npasaporte == nodo -> Padre -> der -> Npasaporte) {
                    nodo -> Padre -> der = nodo1;
                }
        }
    }
    if(nodo1) {
        nodo1 -> Padre = nodo -> Padre;
    }
    DestruirNodo(nodo);
}

void DestruirNodo(nodoArbol *nodo)  {
    nodo -> der = nodo -> izq = nodo -> Padre = NULL;
    delete(nodo);
}


nodoArbol* MinimoNodo(nodoArbol *&nodo) {
    if(nodo == NULL) return NULL;
    else if(nodo -> izq) return MinimoNodo(nodo -> izq);
    else return nodo;
}



void InterCambioValores(nodoArbol *&nodoCambio, nodoArbol *&nodoPadre) {
    //nodoArbol *nodoPadreAux;
    string Npasap;
    string Nombre;
    Nacionalidad nacionalidad;
    int Tipo;
    bool EstadoPasaporte;



    Npasap = nodoCambio -> Npasaporte;
    Nombre = nodoCambio -> Nombre;
    nacionalidad = nodoCambio -> nacionalidad;
    EstadoPasaporte = nodoCambio -> EstadoPasaporte;
    Tipo = nodoCambio -> Tipo;
    //nodoPadreAux = nodoCambio -> Padre;


    nodoCambio -> Tipo = nodoPadre -> Tipo;
    nodoCambio -> Npasaporte = nodoPadre -> Npasaporte;
    nodoCambio -> Nombre = nodoPadre -> Nombre;
    nodoCambio -> nacionalidad = nodoPadre -> nacionalidad;
    nodoCambio -> EstadoPasaporte = nodoPadre -> EstadoPasaporte;
    //nodoCambio -> Padre = nodoPadre -> Padre;


    nodoPadre -> Npasaporte = Npasap;
    nodoPadre -> Nombre = Nombre;
    nodoPadre -> nacionalidad = nacionalidad;
    nodoPadre -> Tipo = Tipo;
    nodoPadre -> EstadoPasaporte = EstadoPasaporte;
    //nodoPadre -> Padre = nodoPadreAux;
}



/**
    Comprueba si un arbol esta vacia dependiendo del parametro "numero"
*/

bool ComprobarArbol(Arbol cola1, Arbol cola2, Arbol cola3, Arbol cola4, int numero) {
    if(numero == 1 && ArbolVacio(cola1)) return true;
    else if(numero == 2 && ArbolVacio(cola2)) return true;
    else if(numero == 3 && ArbolVacio(cola3)) return true;
    else if(numero == 4 && ArbolVacio(cola4)) return true;
    else return false;
}




nodoArbol* BusquedaMenorValor(nodoArbol *nodo) {
    if(nodo -> izq == NULL && nodo -> der == NULL) return nodo;
    else if(nodo -> izq != NULL && nodo -> der == NULL) return NodoMenor(nodo, BusquedaMenorValor(nodo -> izq));
    else if(nodo -> izq == NULL && nodo -> der != NULL) return NodoMenor(nodo, BusquedaMenorValor(nodo -> der));
    else return NodoMenor(BusquedaMenorValor(nodo -> der), BusquedaMenorValor(nodo -> izq));
}

nodoArbol* NodoMenor(nodoArbol *nodo, nodoArbol *nodo2) {
    if(nodo2 == NULL && nodo == NULL) return NULL;
    if(nodo2 == NULL && nodo != NULL) return nodo;
    if(nodo == NULL && nodo2 != NULL) return nodo2;
    if(nodo -> Npasaporte < nodo2 -> Npasaporte) return nodo;
    else return nodo2;
}


nodoArbol* BusquedaMayorValor(nodoArbol *nodo) {
    if(nodo -> izq == NULL && nodo -> der == NULL) return nodo;
    else if(nodo -> izq != NULL && nodo -> der == NULL) return NodoMayor(nodo, BusquedaMayorValor(nodo -> izq));
    else if(nodo -> izq == NULL && nodo -> der != NULL) return NodoMayor(nodo, BusquedaMayorValor(nodo -> der));
    else return NodoMayor(BusquedaMayorValor(nodo -> der), BusquedaMayorValor(nodo -> izq));
}



nodoArbol* BusquedaIgualValor(nodoArbol *nodo, string Npasaporte) {
    if(nodo -> izq -> Npasaporte == Npasaporte || nodo -> der -> Npasaporte == Npasaporte) return nodo;
    else if(nodo -> izq != NULL && nodo -> der == NULL) return BusquedaIgualValor(nodo -> izq, Npasaporte);
    else if(nodo -> izq == NULL && nodo -> der != NULL) return BusquedaIgualValor(nodo -> der, Npasaporte);
    else return BusquedaIgualValor(nodo -> der, Npasaporte);
}

nodoArbol* NodoIgual(nodoArbol *nodo, nodoArbol *nodo2, string Npasaporte) {
    if(nodo2 == NULL && nodo == NULL) return NULL;
    if(nodo2 == NULL && nodo != NULL) return nodo;
    if(nodo == NULL && nodo2 != NULL) return nodo2;
    if(nodo -> Npasaporte == Npasaporte) return nodo;
    else return nodo2;
}



nodoArbol* NodoMayor(nodoArbol *nodo, nodoArbol *nodo2) {
    if(nodo2 == NULL && nodo == NULL) return NULL;
    if(nodo2 == NULL && nodo != NULL) return nodo;
    if(nodo == NULL && nodo2 != NULL) return nodo2;
    if(nodo -> Npasaporte > nodo2 -> Npasaporte) return nodo;
    else return nodo2;
}






int Max(int numero, int numero1) {
    if(numero > numero1) return numero;
    else return numero1;
}

int AlturaArbol(nodoArbol *nodo) {
    if(nodo == NULL) return 0;
    else return (1 + Max(AlturaArbol(nodo -> izq), AlturaArbol(nodo -> der)));
}


bool BusquedaValorArbol(nodoArbol *nodo, string Npasaporte) {
    if(nodo == NULL) return false;
    else {
        if(nodo -> Npasaporte == Npasaporte) return true;
        else {
            if(nodo -> Npasaporte < Npasaporte) return (BusquedaValorArbol(nodo -> der, Npasaporte));
            else return (BusquedaValorArbol(nodo -> izq, Npasaporte));
        }
    }
}



nodoArbol* BusquedaPajero(nodoArbol *nodo, string Npasaporte) {
    if(nodo == NULL) return NULL;
    else {
        if(nodo -> Npasaporte == Npasaporte) return nodo;
        else {
            if(nodo -> Npasaporte < Npasaporte) return (BusquedaPajero(nodo -> der, Npasaporte));
            else return (BusquedaPajero(nodo -> izq, Npasaporte));
        }
    }
}



nodoArbol* BusquedaPadre(nodoArbol *nodo, string Npasaporte) {
    nodoArbol *nodoPadre, *nodoAux;


    nodoPadre = NULL;
    nodoAux = nodo;
    while(nodoAux != NULL && nodoAux -> Npasaporte != Npasaporte) {
        //cout << "AAAAAAAA" << endl;
        nodoPadre = nodoAux;
        if(nodoPadre -> Npasaporte < Npasaporte) nodoAux = nodoAux -> der;
        else nodoAux = nodoAux -> izq;
    }
    return nodoPadre;
}








void GenerarPasajero1(Arbol arbol, Arbol arbol2, Arbol arbol3, Arbol arbol4, int Tipo) {
        string pasap = GenerarPasaporte();
    if(!ComprobarExistenciaPasaporte1(arbol,arbol2,arbol3,arbol4,pasap)){
        nodoArbol *nodo = new nodoArbol;
        nodo -> Npasaporte = pasap;
        nodo -> Nombre = GenerarNombre();
        nodo -> nacionalidad = GenerarNacionalidad();
        nodo -> EstadoPasaporte = GenerarEstado();
        //cout << endl << endl << pasajero -> EstadoPasaporte << endl << endl;
        nodo -> Tipo = Tipo;

        InsertarClaveArbol(arbol, nodo);
   }

}




void PedirDatosNodoArbol(Arbol arbol, Arbol arbol2, Arbol arbol3, Arbol arbol4, int Tipo) {
    nodoArbol *nodo = new nodoArbol;
    string estado, Npasaporte, Nombre;
    Nacionalidad nacionalidad;
    int eleccion;
    bool EstadoPasaporte;
    cout << endl << "Introduce el Numero de pasaporte: ";
    cin >> Npasaporte;
    cout << endl << "Introduce el nombre del Pasajero: ";
    cin >> Nombre;
    cout << endl << "Introduce la Nacionalidad del pasajero: ";
    cout << endl << "1. Espana" << endl << "2. Francia" << endl << "3. Inglaterra" << endl << "4. Alemania" << endl << "5. Noruega" << endl << "6. Suiza" << endl << "7. EstadosUnidos" << endl << "[*]>";
    cin >> eleccion;
    nacionalidad = DeterminarSeleccion(eleccion);
    //cout << endl << "Tipo de Pasajero: " << endl << "1. Union Europea (UE)" << endl << "2. Britanico" << endl << "3. Acuerdo con la UE (Noruega, Suiza..)" << endl << "4. Extracomunitarios" << endl << "[*]>";
    //cin >> Tipo;
    cout << "Estado del Pasaporte (OK/KO): ";
    cin >> estado;
    if(estado == "OK") EstadoPasaporte = true;
    else EstadoPasaporte = false;
    if(ComprobarExistenciaPasaporte1(arbol, arbol2,arbol3,arbol4,Npasaporte)) {
        cout << endl << "No puedes introducir un pasajero ya exitente" <<endl;
        return;
    }

    nodo -> Npasaporte = Npasaporte;
    nodo -> Nombre = Nombre;
    nodo -> Tipo = Tipo;
    nodo -> EstadoPasaporte = EstadoPasaporte;
    nodo -> nacionalidad = nacionalidad;


    InsertarClaveArbol(arbol,nodo);

}




/**
    Determina por el parametro introducido el tipo de dato Enum (llamado Nacionalidad)
*/


Nacionalidad DeterminarSeleccion(int eleccion) {
    if(eleccion == 1) return Espana;
    else if(eleccion == 2) return Francia;
    else if(eleccion == 3) return Inglaterra;
    else if(eleccion == 4) return Alemania;
    else if(eleccion == 5) return Noruega;
    else if(eleccion == 6) return Suiza;
    return EstadosUnidos;
}

/**
    Determina por el parametro introducido el tipo de Pasajero (En que cola está)
*/

string DeterminarTipo(int tipo) {
    if(tipo == 1) return "UE";
    else if(tipo == 2) return "Britanico";
    else if(tipo == 3) return "Acuerdo UE";
    return "ExtraComunitario";
}

/**
    Dependiendo de la "Nacionalidad" devuelve el mismo pero en tipo char
*/

string DeterminarNacionalidad(Nacionalidad nacionalidad) {
    if(nacionalidad == Espana) return "Espana";
    else if(nacionalidad == Francia) return "Francia";
    else if(nacionalidad == Inglaterra) return "Inglaterra";
    else if(nacionalidad == Alemania) return "Alemania";
    else if(nacionalidad == Noruega) return "Noruega";
    else if(nacionalidad == Suiza) return "Suiza";
    else return "EstadosUnidos";
}




bool ComprobarExistenciaPasaporte1(Arbol arbol, Arbol arbol2, Arbol arbol3, Arbol arbol4, string Npasaporte) {
    if(BusquedaValorArbol(arbol -> raiz, Npasaporte) || BusquedaValorArbol(arbol2 -> raiz, Npasaporte) ||
       BusquedaValorArbol(arbol3 -> raiz, Npasaporte) || BusquedaValorArbol(arbol4 -> raiz, Npasaporte)) return true;
    else return false;
}


































































































/**
    Guarda memoria para la estructura definida como Cola
*/


LaCola CrearCola() {

    LaCola cola = new struct Cola;
    cola -> ultimo = cola -> primero = new Pasajero;
    cola -> ultimo = cola -> primero -> sig = NULL;
    return cola;
}


/**
    Inserta en la cola una estructura definida como Pasajero/nodo dentro de una cola
    con los parametros introducidos
*/


void InsertarEnCola(LaCola cola, char* pasaporte, char* nombre, Nacionalidad nacionalidad, int tipo, bool estado) {
    Pasajero *nodoaux = new Pasajero;
    nodoaux -> Npasaporte = pasaporte;
    nodoaux -> Nombre = nombre;
    nodoaux -> nacionalidad = nacionalidad;
    nodoaux -> Tipo = tipo;
    nodoaux -> EstadoPasaporte = estado;
    cola -> cardinalidad++;
    if(cola -> primero -> sig == NULL) {
        cola -> primero -> sig = nodoaux;
        nodoaux -> sig = NULL;
        cola -> ultimo = nodoaux;
    }else {
        cola -> ultimo -> sig = nodoaux;
        cola -> ultimo = nodoaux;
        cola -> ultimo -> sig = NULL;
    }

}


/**
    Inserta en la cola una estructura definida como Pasajero/nodo dentro de una cola

*/

void InsertarEnCola(LaCola cola, Pasajero *nodoaux) {
    cola -> cardinalidad++;
    if(cola -> primero -> sig == NULL) {
        cola -> primero -> sig = nodoaux;
        nodoaux -> sig = NULL;
        cola -> ultimo = nodoaux;
    }else {
        cola -> ultimo -> sig = nodoaux;
        cola -> ultimo = nodoaux;
        cola -> ultimo -> sig = NULL;
    }

}





/**
    Pide por teclado los datos para un pasajero
*/

Pasajero* PedirPasajero(LaCola cola) {
    Pasajero *nodoAux = new Pasajero;
    int eleccion;
    cout << endl << "Introduce el Numero de pasaporte: ";
    cin >> nodoAux -> Npasaporte;
    cout << endl << "Introduce el nombre del Pasajero: ";
    cin >> nodoAux -> Nombre;



    cout << endl << "Introduce la Nacionalidad del pasajero: ";
    cout << endl << "1. Espana" << endl << "2. Francia" << endl << "3. Inglaterra" << endl << "4. Alemania" << endl << "5. Noruega" << endl << "6. Suiza" << endl << "7. EstadosUnidos" << endl << "[*]>";
    cin >> eleccion;
    //nodoAux -> nacionalidad = DeterminarSeleccion(eleccion);



    nodoAux -> nacionalidad = Espana;



    cout << endl << "Tipo de Pasajero: " << endl << "1. Union Europea (UE)" << endl << "2. Britanico" << endl << "3. Acuerdo con la UE (Noruega, Suiza..)" << endl << "4. Extracomunitarios" << endl << "[*]>";
    cin >> nodoAux -> Tipo;




    cout << "Estado del Pasaporte (0/1): ";
    cin >> nodoAux -> EstadoPasaporte;
    return nodoAux;
}


/**
    Busca en una cola al "Pasajero" con el Numero de Pasaporte determinado
*/

void BuscarPasajero(LaCola cola, LaCola cola2,LaCola cola3,LaCola cola4, string Npasaporte) {

    Pasajero *nodo = cola -> primero -> sig;
    bool PasajeroEncontrado = false;
    if(ColaVacia(cola)) {
        cout << "La cola esta vacia" << endl;
        return;
    }
    while(nodo != NULL) {
        if(Npasaporte == nodo -> Npasaporte) {
            cout << "Datos del Pasajero (Encontrado en la cola UE): " << endl;
            cout << "Numero Pasaporte: " << nodo -> Npasaporte << endl;
            cout << "Nombre: " << nodo -> Nombre << endl;
            cout << "Nacionalidad: " << DeterminarNacionalidad(nodo -> nacionalidad) << endl;
            cout << "Tipo: " << DeterminarTipo(nodo -> Tipo) << endl;
            if(nodo -> EstadoPasaporte) cout << "Estado Pasaporte: OK" << endl;
            else cout << "Estado Pasaporte: KO" << endl;
            PasajeroEncontrado = true;
        }
        nodo = nodo -> sig;
    }

    nodo = cola2 -> primero -> sig;
    if(ColaVacia(cola2)) {
        cout << "La cola esta vacia" << endl;
        return;
    }
    while(nodo != NULL) {
        if(Npasaporte == nodo -> Npasaporte) {
            cout << "Datos del Pasajero (Encontrado en la cola Britanicos): " << endl;
            cout << "Numero Pasaporte: " << nodo -> Npasaporte << endl;
            cout << "Nombre: " << nodo -> Nombre << endl;
            cout << "Nacionalidad: " << DeterminarNacionalidad(nodo -> nacionalidad) << endl;
            cout << "Tipo: " << DeterminarTipo(nodo -> Tipo) << endl;
            if(nodo -> EstadoPasaporte) cout << "Estado Pasaporte: OK" << endl;
            else cout << "Estado Pasaporte: KO" << endl;
            PasajeroEncontrado = true;
        }
        nodo = nodo -> sig;
    }


    nodo = cola3 -> primero -> sig;
    if(ColaVacia(cola3)) {
        cout << "La cola esta vacia" << endl;
        return;
    }
    while(nodo != NULL) {
        if(Npasaporte == nodo -> Npasaporte) {
            cout << "Datos del Pasajero (Encontrado en la cola AcuerdosUE): " << endl;
            cout << "Numero Pasaporte: " << nodo -> Npasaporte << endl;
            cout << "Nombre: " << nodo -> Nombre << endl;
            cout << "Nacionalidad: " << DeterminarNacionalidad(nodo -> nacionalidad) << endl;
            cout << "Tipo: " << DeterminarTipo(nodo -> Tipo) << endl;
            if(nodo -> EstadoPasaporte) cout << "Estado Pasaporte: OK" << endl;
            else cout << "Estado Pasaporte: KO" << endl;
            PasajeroEncontrado = true;
        }
        nodo = nodo -> sig;
    }


    nodo = cola4 -> primero -> sig;
    if(ColaVacia(cola4)) {
        cout << "La cola esta vacia" << endl;
        return;
    }
    while(nodo != NULL) {
        if(Npasaporte == nodo -> Npasaporte) {
            cout << "Datos del Pasajero (Encontrado en la cola ExtraComunitarios): " << endl;
            cout << "Numero Pasaporte: " << nodo -> Npasaporte << endl;
            cout << "Nombre: " << nodo -> Nombre << endl;
            cout << "Nacionalidad: " << DeterminarNacionalidad(nodo -> nacionalidad) << endl;
            cout << "Tipo: " << DeterminarTipo(nodo -> Tipo) << endl;
            if(nodo -> EstadoPasaporte) cout << "Estado Pasaporte: OK" << endl;
            else cout << "Estado Pasaporte: KO" << endl;
            PasajeroEncontrado = true;
        }
        nodo = nodo -> sig;
    }

    if(!PasajeroEncontrado) cout << endl << "No se encontro el pasajero" << endl;

}


/**
    Pide por teclado los datos para un pasajero
*/


void PedirDatos(LaCola cola, LaCola cola2, LaCola cola3, LaCola cola4, int tipo) {
    string estado, Npasaporte, Nombre;
    Nacionalidad nacionalidad;
    int eleccion;
    bool EstadoPasaporte;
    cout << endl << "Introduce el Numero de pasaporte: ";
    cin >> Npasaporte;
    cout << endl << "Introduce el nombre del Pasajero: ";
    cin >> Nombre;
    cout << endl << "Introduce la Nacionalidad del pasajero: ";
    cout << endl << "1. Espana" << endl << "2. Francia" << endl << "3. Inglaterra" << endl << "4. Alemania" << endl << "5. Noruega" << endl << "6. Suiza" << endl << "7. EstadosUnidos" << endl << "[*]>";
    cin >> eleccion;
    nacionalidad = DeterminarSeleccion(eleccion);
    //cout << endl << "Tipo de Pasajero: " << endl << "1. Union Europea (UE)" << endl << "2. Britanico" << endl << "3. Acuerdo con la UE (Noruega, Suiza..)" << endl << "4. Extracomunitarios" << endl << "[*]>";
    //cin >> Tipo;
    cout << "Estado del Pasaporte (OK/KO): ";
    cin >> estado;
    if(estado == "OK") EstadoPasaporte = true;
    else EstadoPasaporte = false;
    if(ComprobarExistenciaPasaporte(cola, cola2,cola3,cola4,Npasaporte)) {
        cout << endl << "No puedes introducir un pasajero ya exitente" <<endl;
        return;
    }
    //InsertarEnCola(cola,Npasaporte,Nombre, nacionalidad, tipo,EstadoPasaporte);

}



/**
    Comprueba si una cola esta vacia
*/


bool ColaVacia(LaCola cola) {
    return cola -> cardinalidad == 0;
}


/**
    Visualiza los pasajeros que hay en una cola determinada
*/

void VerCola(LaCola cola) {
    Pasajero *nodo = cola -> primero -> sig;
    int i = 1;
    while(nodo != NULL) {
        cout << "Pasajero " << i << endl;
        cout << "Numero Pasaporte: " << nodo -> Npasaporte << endl;
        cout << "Nombre: " << nodo -> Nombre << endl;
        cout << "Nacionalidad: " << DeterminarNacionalidad(nodo -> nacionalidad) << endl;
        cout << "Tipo: " << DeterminarTipo(nodo -> Tipo) << endl;
        cout << "num_est:"<< nodo->EstadoPasaporte<<endl;
        if(nodo -> EstadoPasaporte) cout << "Estado Pasaporte: OK" << endl;
        else cout << "Estado Pasaporte: KO" << endl;
        i++;
        cout << endl << endl;
        nodo = nodo -> sig;
    }
}


/**
    Visualiza los pasajeros que hay en una cola determinada
*/

void VerCola(LaCola cola, Pasajero *nodo) {
    //Pasajero *nodo = new Pasajero;
    nodo = cola -> primero -> sig;
    int i = 1;
    while(nodo != NULL) {
        cout << "Pasajero " << i << endl;
        cout << "Numero Pasaporte: " << nodo -> Npasaporte << endl;
        cout << "Nombre: " << nodo -> Nombre << endl;
        cout << "Nacionalidad: " << DeterminarNacionalidad(nodo -> nacionalidad) << endl;
        cout << "Tipo: " << DeterminarTipo(nodo -> Tipo) << endl;
        if(nodo -> EstadoPasaporte) cout << "Estado Pasaporte: Correcto" << endl;
        else cout << "Estado Pasaporte: KO" << endl;
        nodo = nodo -> sig;
    }
}

/**
    Comprueba si una cola esta  vacia y si no lo esta llama al primer pasajero de la cola
*/

void Suceso(LaCola cola) {
    //if(!ColaVacia(cola)) LlamarPasajero(cola);
}

/**
    Comprueba el estado del pasaporte del pasajero, si esta correcto se saca de la cola
    sino se mueve al final de la cola
*/
/*
void LlamarPasajero(LaCola cola) {
    //cout<<"estado: "<<cola -> primero -> EstadoPasaporte<<endl;
    if(cola -> primero -> sig -> EstadoPasaporte != 0) SacarDeCola(cola);
    else MoverPasajero(cola);
}
*/
/**
    Imprime por pantalla todas las colas
*/

void VerTodasCola(LaCola UE, LaCola Britanicos, LaCola AcuerdosUE, LaCola Extracomunitarios) {
    cout << "COLA 1: ";
    MostrarPasaporte(UE);
    cout << "COLA 2: ";
    MostrarPasaporte(Britanicos);
    cout << "COLA 3: ";
    MostrarPasaporte(AcuerdosUE);
    cout << "COLA 4: ";
    MostrarPasaporte(Extracomunitarios);
}

/**
    Muestra la por pantalla los Numeros de Pasaporte de todos los Pasajeros de la cola
*/

void MostrarPasaporte(LaCola cola) {
    Pasajero *nodo;
    nodo = cola -> primero -> sig;
    while(nodo != NULL && !ColaVacia(cola)) {
        cout << nodo -> Npasaporte << " ";
        //cout << nodo -> Nombre << " " << nodo -> EstadoPasaporte << " ";
        nodo = nodo -> sig;
    }
    cout << endl;
}

/**
    Genera aleatoriamente un Pasajero comprueba si existe y si no lo hace se introduce en
    la primera cola colocada como parametro
*/

void GenerarPasajero(LaCola cola, LaCola cola2, LaCola cola3, LaCola cola4, int Tipo) {
    string pasap = GenerarPasaporte();
    if(!ComprobarExistenciaPasaporte(cola,cola2,cola3,cola4,pasap)){
        Pasajero *pasajero = new Pasajero;
        pasajero -> Npasaporte = pasap;
        pasajero -> Nombre = GenerarNombre();
        pasajero -> nacionalidad = GenerarNacionalidad();
        pasajero -> EstadoPasaporte = GenerarEstado();
        //cout << endl << endl << pasajero -> EstadoPasaporte << endl << endl;
        pasajero -> Tipo = Tipo;
        InsertarEnCola(cola, pasajero);
    }
    /*******
    Pasajero *pasajero = new Pasajero;
    pasajero -> Npasaporte = GenerarPasaporte();
    pasajero -> Nombre = GenerarNombre();
    pasajero -> nacionalidad = GenerarNacionalidad();
    pasajero -> EstadoPasaporte = GenerarEstado();
    pasajero -> Tipo = Tipo;
    if(!ComprobarExistenciaPasaporte(cola,cola2,cola3,cola4,pasajero -> Npasaporte))InsertarEnCola(cola, pasajero);
    ************/
    else GenerarPasajero(cola,cola2,cola3,cola4,Tipo);
}


/**
    Comprueba si existe en alguna de las cola un pasajero con el Numero de Pasaporte determinado
*/

bool ComprobarExistenciaPasaporte(LaCola cola1, LaCola cola2, LaCola cola3, LaCola cola4, string Npasajero) {
    int i = 0;
    Pasajero *pasajero;
    pasajero = cola1 -> primero -> sig;
    while(pasajero != NULL) {
        if(pasajero -> Npasaporte == Npasajero) i++;
        pasajero = pasajero -> sig;
    }
    pasajero = cola2 -> primero -> sig;
    while(pasajero != NULL) {
        if(pasajero -> Npasaporte == Npasajero) i++;
        pasajero = pasajero -> sig;
    }
    pasajero = cola3 -> primero -> sig;
    while(pasajero != NULL) {
        if(pasajero -> Npasaporte == Npasajero) i++;
        pasajero = pasajero -> sig;
    }
    pasajero = cola4 -> primero -> sig;
    while(pasajero != NULL) {
        if(pasajero -> Npasaporte == Npasajero) i++;
        pasajero = pasajero -> sig;
    }
    if(i != 0) return true;
    else return false;
}


/**
    Comprueba si una cola esta vacia dependiendo del parametro "numero"
*/

bool ComprobarCola(LaCola cola1, LaCola cola2, LaCola cola3, LaCola cola4, int numero) {
    if(numero == 1 && ColaVacia(cola1)) return true;
    else if(numero == 2 && ColaVacia(cola2)) return true;
    else if(numero == 3 && ColaVacia(cola3)) return true;
    else if(numero == 4 && ColaVacia(cola4)) return true;
    else return false;
}

/**
    Mueve al final de la cola al primer pasajero
*/

void MoverPasajero(LaCola cola) {
    Pasajero *nodo;
    nodo = cola -> primero -> sig;
    cout << endl << endl << "Procesamiento KO pasajero " << nodo -> Npasaporte << endl << endl;
    nodo -> EstadoPasaporte = true;
    cola -> primero -> sig = nodo -> sig;
    cola -> ultimo -> sig = nodo;
    cola -> ultimo = nodo;
    nodo -> sig = NULL;
}



