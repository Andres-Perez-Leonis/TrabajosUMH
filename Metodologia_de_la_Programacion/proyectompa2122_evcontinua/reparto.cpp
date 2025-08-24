#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
using namespace std;

float** Lectura_Matriz(char* file,int &n, float** &Matriz, bool ocultar){
     ifstream fDatos;

    char linea[200], *tok;
    int NColumna, NFila;
    float Valor;

    

    // Abrir fichero 
    strcat(file, ".txt");
    
    fDatos.open(file);

    //Lectura de la primera linea
    fDatos.getline(linea, 200);
    tok = strtok(linea, " \t\r\n");

    n = atoi(tok); // convertir el token a entero

    Matriz = new float*[n + 1];


    for(int i = 0; i <= n ; i++) {
        Matriz[i] = new float[n];
    }


    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= n; j++) {
            Matriz[i][j] = 99999;
        }
    }

    //Lectura de la segunda linea
    fDatos.getline(linea, 200);
    if  (ocultar){
        cout << linea << endl;
    }


    while(strcmp(linea, "") != 0) {

        NFila = atoi(strtok(linea, " \t\r\n"));
        NColumna = atoi(strtok(NULL, " \t\r\n"));
        Valor = atof(strtok(NULL, " \t\r\n"));

        Matriz[NFila][NColumna] = Valor;
        fDatos.getline(linea, 200);

        if  (ocultar){
            cout << linea << endl;
        }
        
    }
    
    cout << "clientes = " << n << "\n\n";

    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= n; j++) {
            cout << Matriz[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;


    fDatos.close();

    
    return Matriz;
}

bool Ciclos(int* V, int k)
{
    for(int i=0; i <= k ;i++)
    {
        for(int j=0; j <= k; j++)
        {
            if(j == i)
                continue;
            if(V[i] == V[j])
                return true;
        }
    }
    return false;
}

float CalcularCoste(float** matriz, int* V,int k)
{
    int i, j, l, m, h = 0;
    float costetotal = 0,coste = 0;
    for(i=1; i <= k ; i++){
        l = V[i-1];
        m = V[i];
        coste = matriz[l][m];
        costetotal = costetotal + coste;
    }
    
    coste = matriz[m][h];
    costetotal = costetotal + coste;

    return costetotal;
}


int Viajante(float** matriz, int* &V, int &Voptimo, double &costeoptimo, int k, int n, bool ocultar, int &caminos_encotrados, int *&camino) {
    float costeV = 0;
    int i,j=0,f,aux;
    V[k] = 0;
    // n se lee desde el fichero
    while(V[k] != n)
    {
        V[k] = V[k]+1;
        j++;

        if(matriz[V[k-1]][V[k]] != 99999 &&  Ciclos(V, k) != true)
        {
            if(k == n)
            {
                if(matriz[V[k]][V[0]] != 99999)
                {
                   
                    costeV = CalcularCoste(matriz,V,k);

                    Voptimo = V[k];
                    aux = costeV;

                    if(costeV < costeoptimo){

                        if (ocultar==true){
                            for(f = 0; f <= n; f++) {
                                    camino[f] = V[f];
                                }
                        }
                        costeoptimo = costeV;
                    }

                    if(ocultar==false)
                    {
                        cout << "Camino : " ;
                    
                        for(i = 0; i <= k ; i++){
                            cout << V[i] << " ";
                        }
                        V[k+1]=0;
                        cout << V[k+1] << " ";

                        cout << endl;
                        cout << "Coste optimo: " << aux << endl;
                        cout << endl;
                    }
                }
            }
            else
                Viajante(matriz, V, Voptimo, costeoptimo, k+1, n, ocultar,caminos_encotrados, camino);
        }
    }
    caminos_encotrados=j;
    return costeoptimo;
}

int main()
{
    double costeoptimo = 99999;
    int* V;
    int Voptimo, clientes = 0, k = 1, x = 0, y = 0;
    int caminos_encotrados=0, *camino;
    float **matriz;
    char file[] = "";
    char SN[] = "";
    bool validLectura = false;
    bool ocultar = false;

    cout << "Programa Realizado por: " << endl;
    cout << "Andres Perez" << endl << "Bryan Grisales" << endl << "Emilio Gonzalez" << endl;

    while(x !=  5) {
        cout << endl << "Opciones a elegir (solo puede escoger una opcion)" << endl; 
        cout << "1. Obtener lista de los clientes" << endl;  
        cout << "2. Ocultar recorrido opcion 3" << endl; 
        cout << "3. Lista de recorridos optimos, resaltando el mas corto" << endl; 
        cout << "4. Recorrido mas corto (algoritmo mejorado)" << endl;
        cout << "5. Salir" << endl << endl;
        cin  >> x;


        if(x == 1) {

            printf("Nombre del fichero que desea leer: \n");
            cin >> file;

            Lectura_Matriz(file, clientes, matriz, x);
            validLectura = true;

        }else if(x == 2) {

            cout << "Indica si quiere ocultar el recorrido (S/N): ";
            cin >> SN;

            if(strcmp(SN, "S") == 0) ocultar = true;
            else ocultar = false;

        }else if(x == 3 && validLectura) {

            double costeoptimo = 99999;
            int* V;
            int Voptimo, k = 1;
            int caminos_encotrados=0, *camino;
            
            V = new int[clientes + 1];
            camino = new int[clientes + 1];

            // inicializar el vector de vertices
            for(int i = 0; i <= clientes; i++){
                V[i] = i;
                camino[i]=i;
            }
            
            costeoptimo = Viajante(matriz, V, Voptimo, costeoptimo, k, clientes, ocultar, caminos_encotrados,camino);
            
            if (ocultar==true){
                cout << "caminos encontrados: "  << caminos_encotrados << endl;

                cout << "Camino Utilizado: ";
                for(int k = 0; k <= clientes; k++) {
                    cout << camino[k] << " ";
                }
                camino[k+1]=0;
                cout << camino [k+1] << endl;
            }

            cout << "costeoptimo: "  << costeoptimo << endl;

        }else if(x == 4 && validLectura) {

            cout << "No hemos podido hacer el segundo algoritmo" << endl;

        }else if(!validLectura) {

            cout << "No has leido el fichero" << endl;
        }
    }
}