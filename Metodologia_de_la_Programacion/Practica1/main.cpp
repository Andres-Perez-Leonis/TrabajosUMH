#include <iostream>

using namespace std;

int Analizar(int *vector1, int x, int n){

    int nveces = 0;

    for(int i=1; i <= n+1; i++ ){

        if(vector1[i]==x){
            nveces++;
        }
    }

    return nveces;
}

int main ()
{
    int x, n, valor1, valor2, valor3;

    cout << "Introduce el valor de x: ";
    cin >> x ;
    cout << endl;

    cout << "Introcuce el tamano de los vectores: ";
    cin >> n;
    cout << endl;

    int *peor = new int[n+1], *mejor = new int[n+1], *cualquiera = new int[n+1];
    cout << "Peor  Mejor  Cualquiera"<<endl;

    for(int i=1; i < n+1; i++){
        peor[i]=x;
        mejor[i]=x+i+1;
        if(i%2==1){
            cualquiera[i]=x;
        }
        else{
            cualquiera[i]=x+i+1;
        }

        cout<<peor[i]<<"  "<<mejor[i]<<"  "<<cualquiera[i]<<endl;
    }

    valor1 = Analizar(peor, x, n+1);
    valor2 = Analizar(mejor, x, n+1);
    valor3 = Analizar(cualquiera, x, n+1);

    cout << "Solucion Peor: "<< valor1 << endl << "Solucion Mejor: " << valor2 << endl << "Solucion Cualquiera: " << valor3 << endl;

    return 0;
}
