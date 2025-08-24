#ifndef _LIBRERIA
#define _LIBRERIA
#include <string>
#include <iostream>

using namespace std;

typedef enum Datos { Espana, Francia, Inglaterra, Alemania, Noruega, Suiza, EstadosUnidos } Nacionalidad;

typedef struct nodoA {
    struct nodoA *Padre;
    string Npasaporte;
    string Nombre;
    Nacionalidad nacionalidad;
    int Tipo;
    bool EstadoPasaporte;
    struct nodoA *izq, *der;
}nodoArbol;

typedef struct Tree {
    struct nodoA *raiz;
}*Arbol;


typedef struct Nodo {
    string Npasaporte;
    string Nombre;
    Nacionalidad nacionalidad;
    int Tipo;
    bool EstadoPasaporte;
    struct Nodo *sig;
} Pasajero;

typedef struct Cola {
    Pasajero *primero;
    Pasajero *ultimo;
    int cardinalidad = 0;
}*LaCola;

/*

    Colas

*/

LaCola CrearCola();
bool ColaVacia(LaCola cola);
void MoverPasajero(LaCola cola);
void VerCola(LaCola cola);
void VerCola(LaCola cola, Nodo *nodo);
void SacarDeCola(LaCola cola);
void VerTodasCola(LaCola UE, LaCola Britanicos, LaCola AcuerdosUE, LaCola Extracomunitarios);
void InsertarEnCola(LaCola cola, Pasajero *nodoaux);
void BuscarPasajero(LaCola cola, LaCola cola2,LaCola cola3,LaCola cola4, string Npasaporte);
void GenerarPasajero(LaCola cola, LaCola cola2, LaCola cola3, LaCola cola4, int Tipo);
void LlamarPasajero(LaCola);
void MostrarPasaporte(LaCola cola);
Nacionalidad GenerarNacionalidad();
bool GenerarEstado();
void PedirDatos(LaCola cola, LaCola cola2, LaCola cola3, LaCola cola4, int Tipo);
void Suceso(LaCola cola);
bool ComprobarCola(LaCola cola, LaCola cola2, LaCola cola3, LaCola cola4, int numero);
bool ComprobarExistenciaPasaporte(LaCola cola, LaCola cola2,LaCola cola3,LaCola cola4, string Npasaporte);
string GenerarPasaporte();
string DeterminarTipo(int Tipo);
string DeterminarNacionalidad(Nacionalidad nacionalidad);
string GenerarNombre();
bool GenerarEstado();
Nacionalidad GenerarNacionalidad();
int GenerarTipo();
Nacionalidad DeterminarSeleccion(int eleccion);

/*

        Arboles

*/


bool ComprobarExistenciaPasaporte1(Arbol arbol, Arbol arbol2, Arbol arbol3, Arbol arbol4, string Npasajero);
void GenerarPasajero1(Arbol arbol, Arbol arbol2, Arbol arbol3, Arbol arbol4, int Tipo);
bool BusquedaValorArbol(nodoArbol *nodo, string Npasaporte);
int GradoArbol(nodoArbol *nodo);
int AlturaArbol(nodoArbol *nodo);
void EntreOrdenArbol(nodoArbol *nodo);
void EntreOrdenArbol2(nodoArbol *nodo);
void EntreOrdenArbol3(nodoArbol *nodo);
void InsertarArbolRandom(Arbol arbol, nodoArbol *nodo);
Arbol CrearArbol();
bool ArbolVacio(Arbol arbol);
void InsertarClaveArbol(Arbol arbol, string Npasaporte, string Nombre, Nacionalidad nacionalidad, int Tipo, bool EstadoPasaporte);
void InsertarClaveArbol(Arbol arbol, nodoArbol *nodo);
void ImprimirDatosNodo(nodoArbol *nodo);
nodoArbol* BusquedaPajero(nodoArbol *nodo, string Npasaporte);
void PedirDatosNodoArbol(Arbol arbol, Arbol arbol2, Arbol arbol3, Arbol arbol4, int Tipo);




nodoArbol* BusquedaMenorValor(nodoArbol *nodo);
nodoArbol* NodoMenor(nodoArbol *nodo, nodoArbol *nodo2);
nodoArbol* EliminarNodoArbol(nodoArbol *nodo, string Npasaporte);
nodoArbol* BusquedaMayorValor(nodoArbol *nodo);
nodoArbol* NodoMayor(nodoArbol *nodo, nodoArbol *nodo2);
void InterCambioValores(nodoArbol *&nodoCambio, nodoArbol *&nodoPadre);



nodoArbol* BuscarNodoHoja(nodoArbol *nodo);
nodoArbol* BuscarNodoConUnHijo(nodoArbol *nodo);
nodoArbol* BuscarNodoInterno(nodoArbol *nodo);
void MostrarArboles(Arbol UE, Arbol Britanicos, Arbol AcuerdosUE, Arbol Extracomunitarios);

bool ComprobarArbol(Arbol cola1, Arbol cola2, Arbol cola3, Arbol cola4, int numero);
nodoArbol* Suceso(nodoArbol *nodoRaiz, nodoArbol *nodoEliminar);
nodoArbol* BuscarNodoAleatorio(int Narbol, Arbol UE, Arbol Britanicos, Arbol AcuerdosUE, Arbol Extracomunitarios);
nodoArbol* EliminarNodoArbol1(nodoArbol *nodo, string Npasaporte);
nodoArbol* BusquedaPadre(nodoArbol *nodoPadre, string Npasaporte);
nodoArbol* BusquedaIgualValor(nodoArbol *nodo, string Npasaporte);
nodoArbol* NodoIgual(nodoArbol *nodo, nodoArbol *nodo2, string Npasaporte);



void EliminarNodo(nodoArbol *&nodo);
void nodoEliminar(nodoArbol *&nodo, string Npasaporte);
nodoArbol* MinimoNodo(nodoArbol *&nodo);
void RemplazarNodo(nodoArbol *nodo, nodoArbol *nodo1);
void DestruirNodo(nodoArbol *nodo);
void VisualizarArbol(nodoArbol *nodo, int n);
nodoArbol *CrearNodo(nodoArbol *Padre, string Npasaporte, string Nombre, Nacionalidad nacionalidad, bool EstadoPasaporte, int Tipo);

void MeterNodo(nodoArbol* &nodoAr, nodoArbol *Padre, string Npasaporte, string Nombre, Nacionalidad nacionalidad, bool EstadoPasaporte,int Tipo);

#endif

