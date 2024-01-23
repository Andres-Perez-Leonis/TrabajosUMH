#include <iostream>

using namespace std;

void combinar(int v1[], int v2[], int v[], int n1, int n2) {
    int i1 = 1, i2 = 1;
    v1[n1 + 1] = 999999999;
    v2[n2 + 1] = 999999999;
    for(int i = 1; i < n1 + n2; i++) {
        if(v1[i1] < v2[i2]) {
            v[i] = v1[i1];
            i1++;
        }else {
            v[i] = v2[i2];
            i2++;
        }
    }
}


void mergesort(int v[], int n) {
    int nInf = n/2;
    int nSup = n - nInf, aux, k = 1;
    int v1[nInf + 1], v2[nSup + 1];

    cout << nInf << " " << nSup;
    if(n < 3) {
            if(v1[1] > v2[1]) {
                aux = v1[1];
                v[1] = v[2];
                v[2] = aux;
            }
    }else {
        for(int i = 1; i <= nInf; i++) {
            v1[i] = v[i];
        }
        for(int i = nInf + 1; i <= n; i++) {
            v2[k] = v[i];
            k++;
        }

        cout << endl << endl;

        for(int i = 1; i <= nInf; i++) {
            cout << v1[i] << " ";
        }
        cout << endl;
        for(int i = 1; i <= nSup; i++) {
            cout << v2[i] << " ";
        }



        mergesort(v1, nInf);
        mergesort(v2, nSup);
        combinar(v1,v2,v, nInf, nSup);

    }



}




int main()
{

    int n;
    cout << "Tamano del vector: ";
    cin >> n;
    int numeros[n+1];

    for(int i = 1; i < n + 1; i++) {
        cout << endl << "Introduce un numero: ";
        cin >> numeros[i];
    }
    cout << endl << "El vector introducido es: " << endl;
    for(int i = 1; i < n + 1; i++) {
        cout << numeros[i] << " ";
    }
    cout << endl;
    mergesort(numeros, n);
    cout << endl << "El vector ordenado es: " << endl;
    for (int i = 1; i < n + 1; i++) {
        cout << numeros[i] << " ";
    }


    return 0;
}
