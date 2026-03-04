#include <iostream>
#include "dyv.h"

int main () {

    char A[] = {'c', 'd', 'd', 'a', 'b', 'c', 'd', 'a', 'c', 'c', 'a', 'a','a', 'a','a', 'a', 'a' };
    int n = sizeof(A); // actualizo n con la longitud real de la cadena A
    
    // Algoritmo iterativo
    int pIt = 0;
    int maxIt = iterativo(n,m,A,pIt);

    cout << "Solucion: B, posicion de inicio igual a " << pIt << ", y numero de caracteres en C igual a " << maxIt << "." << endl;
    
    return 0;
}