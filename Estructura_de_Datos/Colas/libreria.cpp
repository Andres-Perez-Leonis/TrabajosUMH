#include <iostream>
#include "libreria.h"
using namespace std;


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


void InsertarEnCola(LaCola cola, string pasaporte, string nombre, Nacionalidad nacionalidad, int tipo, bool estado) {
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
    InsertarEnCola(cola,Npasaporte,Nombre, nacionalidad, tipo,EstadoPasaporte);

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
    if(!ColaVacia(cola)) LlamarPasajero(cola);
}

/**
    Comprueba el estado del pasaporte del pasajero, si esta correcto se saca de la cola
    sino se mueve al final de la cola
*/

void LlamarPasajero(LaCola cola) {
    //cout<<"estado: "<<cola -> primero -> EstadoPasaporte<<endl;
    if(cola -> primero -> sig -> EstadoPasaporte != 0) SacarDeCola(cola);
    else MoverPasajero(cola);
}

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
    Genera aleatoriamente un Numero de pasaporte para un Pasajero
*/

string GenerarPasaporte() {
    char Npasaporte[10];

    for(int i = 0; i < 2; i++) Npasaporte[i] = (char) (rand()%26+65);
    for(int i = 2; i < 7; i++) Npasaporte[i] = (char) (rand()%10+48);
    for(int i = 7; i < 9; i++) Npasaporte[i] = (char) (rand()%26+65);
    Npasaporte[9] = '\0';
    string tmp_string(Npasaporte);
    return tmp_string;
}


/**
    Genera aleatoriamente un Nombre para un Pasajero
*/

string GenerarNombre() {
    char Nombre[20];

    for(int i = 0; i < 20; i++) Nombre[i] = (char) (rand()%26+65);
    string tmp_string(Nombre);
    return tmp_string;
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



/**
    Borra de la cola al primer pasajero
*/

void SacarDeCola(LaCola cola) {
    Pasajero *nodoaux;
    nodoaux = cola -> primero -> sig;

    if(!ColaVacia(cola) && nodoaux != NULL) {
        cola -> primero -> sig = cola -> primero -> sig -> sig;
        cola  -> cardinalidad--;
        cout << endl << endl << "Procesamiento OK " << nodoaux -> Npasaporte << endl << endl;
        delete(nodoaux);
        if(cola -> primero -> sig == NULL) cola -> ultimo = NULL;

    }
}

