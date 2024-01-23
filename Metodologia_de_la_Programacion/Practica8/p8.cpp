#include <iostream>
#include <stdlib.h>

//LUIS MARTINEZ PASTOR alu60
//Kaiming Chen alu21
// Samuel Lajara alu47

using namespace std;


int PESO_MAX = 10;
int n;
float voptimo = -1;
float poptimo;
int *xoptimo;

float CalcularSuma(int *X, float *P, int k)
{
    int i;
    float suma=0;
    for ( i = 0; i <= k; i++) {
      suma+=X[i]*P[i+1];
    }
    return suma;
}

void maleta(float *P, float *V, int *X, int k)
{
    int i, j;
    float peso, valor;
    if(k<=n){
      for (i = 0; i <= 1; i++) {
        X[k]=i;

        peso=CalcularSuma(X, P, k);
        if(peso<=PESO_MAX){
          if(k==n){
            valor=CalcularSuma(X,V,k);
            if(valor>voptimo){
              voptimo=valor;
              poptimo=peso;
              for(j=0;j<n;j++)
              {
                xoptimo[j]=X[j];
                }
            }
          }
          else
          {
              maleta(P,V,X,k+1);
          }
        }
      }
    }
}

int main()
{
    int i, peso=0, valor=0;
    float b;
    float a;
    cout << "Introduce el total de objetos (n):" << endl;
    cin >> n;

    cout << "PESOS:" << endl;
    float P[n + 1];
    float V[n + 1];
    int X[n + 1];
    xoptimo=new int[n+1];
    for (i = 1; i <= n; i++)
    {
        cout << "Objeto " << i << ":" << endl;
        cin >> a;
        if (a < 0)
        {
            a = a * -1;
        }
        P[i] = a;
    }
    cout << "VALORES:" << endl;
    for (i = 1; i <= n; i++)
    {
        cout << "Objeto " << i << ":" << endl;
        cin >> b;
        if (b < 0)
        {
            b = b * -1;
        }
        V[i] = b;
    }

    maleta(P, V, X, 0);

    cout << endl;
    cout << "OBJETOS A INTRODUCIR EN LA MALETA" << endl;
    for (i = 1; i <= n; i++) {
      if(xoptimo[i-1]==1){
        cout << i << ": " << P[i] << "kg - Valor: " << V[i] << endl;
        peso+=P[i];
        valor+=V[i];
      }
    }
    cout << endl << "Peso: " << poptimo << endl;
    cout << "Valor: " << voptimo << endl;

    cout << endl << "OBJETOS QUE QUEDAN FUERA:";
    for (i = 1; i <= n; i++) {
      if(xoptimo[i-1]==0){
        cout << " " << i;
      }
    }
    cout << endl;

    return 0;
}
