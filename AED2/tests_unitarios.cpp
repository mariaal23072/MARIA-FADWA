#include <iostream>
#include "dyv.h"

int main () {

    char A[] = {'c', 'd', 'd', 'a', 'b', 'c', 'd', 'a', 'c', 'c', 'a', 'a','a', 'a','a', 'a', 'a' };
    int n = sizeof(A); // actualizo n con la longitud real de la cadena A
    
    // Algoritmo iterativo
    int pIt = 0;
    int maxIt = iterativo(n,m,A,pIt);

    // Algoritmo recursivo dyv
    int pDyv = 0;
    int maxDyv = dyv(0, n, m, A, pDyv);

    // Iterativo:
    cout << "Iterativo:\nSolucion: B, posicion de inicio igual a " << pIt << ", y numero de caracteres en C igual a " << maxIt << "." << endl;
    
    // DyV:
    cout << "Divide y Venceras:\nSolucion: B, posicion de inicio igual a " << pDyv << ", y numero de caracteres en C igual a " << maxDyv << "." << endl;

    return 0;
}