#include <iostream>
#include <time.h>
using namespace std;



typedef struct nodo {
    int numero;
    int cardinalidad = 0;
    struct nodo *sig;
}*Lista;

bool ListaVacia(Lista lista);
Lista CrearLista();
void MostrarElementos(Lista lista);
void InsetarNumerosRandom(Lista lista, int numero);
void InsetarNumeroOrdenado(Lista lista, int v);
void InsertarElemento(Lista lista, int numero);
int ContarElemento(Lista lista, int n);
void EliminarNodo(Lista lista);
bool EncontrarElemento(Lista lista, int n);

Lista CrearLista() {
    Lista lit = new struct nodo;
    lit -> sig = NULL;
    return lit;
}

bool ElementInSet(Lista lista) {

    struct nodo *nodoAux = new struct nodo;
    nodo

}

bool IgualdadDeConjuntos(Lista lista1, Lista lista2) {
    struct nodo *nodoAux = new struct nodo, *nodoAux2 = new struct nodo;
    nodoAux = lista1 -> sig;
    nodoAux2 = lista2 -> sig;



}

Lista InterseccionDeListas(Lista lista1, Lista lista2) {

}



void MostrarElementos(Lista lista) {
    cout << "----------------------------------" << endl << endl;
    struct nodo *nodoAux = new struct nodo;
    nodoAux = lista -> sig;
    while(nodoAux -> sig != NULL) {
        cout << nodoAux -> numero << " ";
        nodoAux = nodoAux -> sig;
    }
    cout << endl;
}

void InsetarNumerosRandom(Lista lista, int numero) {
    srand(time(NULL));
    for(long int i = 1; i <= numero; i++)
        InsertarElemento(lista, rand()%1000);
}

void InsetarNumeroOrdenado(Lista lista, int v) {
    struct nodo *nodoAux = new struct nodo;
    nodoAux = lista;
    while((nodoAux -> sig != NULL) && (nodoAux -> sig -> numero < v))
        nodoAux = nodoAux -> sig;
    struct nodo *nodoAux2 = new struct nodo;
    nodoAux2 -> numero = v;
    nodoAux2 -> sig = nodoAux -> sig;
    nodoAux -> sig = nodoAux2 -> sig;

}

void InsertarElemento(Lista lista, int numero) {
    struct nodo *nodoAux = new struct nodo;
    nodoAux -> numero = numero;
    nodoAux -> sig = lista -> sig;
    lista -> cardinalidad++;
    lista -> sig = nodoAux;
    lista -> cardinalidad

}

int ContarElemento(Lista lista, int n) {
    int i = 0;
    struct nodo *nodoAux = new struct nodo;
    while(nodoAux -> sig != NULL) {
        if(nodoAux -> numero == n) i++;
        nodoAux = nodoAux -> sig;
    }
    return i;
}

void EliminarNodo(Lista lista) {
    struct nodo *nodoAux = new struct nodo;

}


bool EncontrarElemento(Lista lista, int n) {
    struct nodo *nodoAux = new struct nodo;
    nodoAux = lista;
    while((nodoAux -> sig != NULL) && (nodoAux -> sig -> numero != n))
        nodoAux = nodoAux -> sig;
    if(nodoAux -> sig == NULL) return false;
    else return true;
}

bool ListaVacia(Lista lista) {
    return (lista -> sig == NULL) ? true : false;
}

int main()
{
    Lista lista;
    lista = CrearLista();


    return 0;
}
