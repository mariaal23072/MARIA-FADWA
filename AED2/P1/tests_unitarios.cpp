#include <iostream>
#include <cassert>
#include "dyv.h"

using namespace std;

// Pruebas unitarias para el algoritmo DyV

// Cuando la cadena ordenada más larga está al principio
void testPrincipio() {
    int n = 8; // longitud de la cadena
    int m = 4; // longitud mínima de la subcadena ordenada
    char A[] = {'a', 'b', 'c', 'd', 'z', 'y', 'x', 'w'}; // cadena de prueba
    int p = 0; // variable para almacenar la posición de inicio de la subcadena ordenada más larga
    
    int resultado = dyv(0, n - 1, m, A, p); // llamamos a la función DyV con los parámetros adecuados
    assert(resultado == 4); // verificamos que sea 4, longitud de la subcadena ordenada más larga
    assert(p == 1); // verificamos que la posición sea 1 (empezamos en 1, como se pide)
}

// Cuando la cadena ordenada más larga está al final
void testFinal() {
    int n = 8;
    int m = 4;
    char A[] = {'z', 'x', 'x', 'w', 'a', 'b', 'c', 'a'};
    int p = 0;
    
    int resultado = dyv(0, n - 1, m, A, p);
    assert(resultado == 3);
    assert(p == 4 );
}

// Cuando la cadena ordenada más larga está en la mitad
void testMitad() {
    int n = 8;
    int m = 4;
    char A[] = {'z', 'y', 'a', 'b', 'c', 'd', 'x', 'w'};
    int p = 0;
    
    int resultado = dyv(0, n - 1, m, A, p);
    assert(resultado == 4);
    assert(p == 3);
}

// Cuando la cadena ordenada más larga es constante (todos los caracteres iguales)
void testMejorConstante() {
    int n = 8;
    int m = 4;
    char A[] = {'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a'};
    int p = 0;
    
    int resultado = dyv(0, n - 1, m, A, p);
    assert(resultado == 4);
    assert(p == 1);
}

// Cuando la cadena ordenada más larga es creciente
void testMejorCreciente() {
    int n = 8;
    int m = 4;
    char A[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    int p = 0;
    
    int resultado = dyv(0, n - 1, m, A, p);
    assert(resultado == 4);
    assert(p == 1);
}

// Cuando la cadena ordenada más larga es decreciente
void testPeorDecreciente() {
    int n = 8;
    int m = 4;
    char A[] = {'z', 'y', 'x', 'w', 'v', 'u', 't', 's'};
    int p = 0;
    
    int resultado = dyv(0, n - 1, m, A, p);
    assert(resultado == 1);
    assert(p == 1);
}

int main() {
    
    // Ejecutamos cada prueba unitaria
    testPrincipio();
    testFinal();
    testMitad();
    testMejorConstante();
    testMejorCreciente();
    testPeorDecreciente();
    
    // Si llegamos aquí, todas las pruebas pasaron correctamente
    cout << "Todos los tests pasaron correctamente." << endl;
    return 0;
}