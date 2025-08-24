#ifndef _LIBRERIA
#define _LIBRERIA
#include <iostream>
#include <string>
using namespace std;

typedef enum Datos { Espana, Francia, Inglaterra, Alemania, Noruega, Suiza, EstadosUnidos } Nacionalidad;

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


LaCola CrearCola();
bool ColaVacia(LaCola cola);
void LlamarPasajero(LaCola cola);
void Suceso(LaCola cola) ;
void MoverPasajero(LaCola cola);
void VerCola(LaCola cola);
void VerCola(LaCola cola, Pasajero *nodo);
void SacarDeCola(LaCola cola);
void MostrarPasaporte(LaCola cola);
void VerTodasCola(LaCola UE, LaCola Britanicos, LaCola AcuerdosUE, LaCola Extracomunitarios);
string DeterminarNacionalidad(Nacionalidad nacionalidad);
void InsertarEnCola(LaCola cola, string pasaporte, string nombre, Nacionalidad nacionalidad, int tipo, bool estado);
void InsertarEnCola(LaCola cola, Pasajero *nodoaux);
Nacionalidad DeterminarSeleccion(int eleccion);
string DeterminarTipo(int tipo);
Pasajero* PedirPasajero(LaCola cola);
void PedirDatos(LaCola cola, LaCola cola2, LaCola cola3, LaCola cola4, int tipo);
void BuscarPasajero(LaCola cola, LaCola cola2,LaCola cola3,LaCola cola4, string Npasaporte);
string GenerarPasaporte();
string GenerarNombre();
Nacionalidad GenerarNacionalidad();
bool GenerarEstado();
int GenerarTipo();
void GenerarPasajero(LaCola cola, LaCola cola2, LaCola cola3, LaCola cola4,int Tipo);
bool ComprobarExistenciaPasaporte(LaCola cola1, LaCola cola2, LaCola cola3, LaCola cola4, string Npasajero);
bool ComprobarCola(LaCola cola1, LaCola cola2, LaCola cola3, LaCola cola4, int numero);


#endif
