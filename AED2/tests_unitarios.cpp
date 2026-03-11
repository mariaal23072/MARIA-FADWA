#include <iostream>
#include <cassert>
#include "dyv.h"

using namespace std;

void testPrincipio() {
    int n = 8;
    int m = 4;
    char A[] = {'a', 'b', 'c', 'd', 'z', 'y', 'x', 'w'};
    int p = 0;
    
    int resultado = dyv(0, n - 1, m, A, p);
    assert(resultado == 4);
    assert(p == 1);
}

void testFinal() {
    int n = 8;
    int m = 4;
    char A[] = {'z', 'x', 'x', 'w', 'a', 'b', 'c', 'a'};
    int p = 0;
    
    int resultado = dyv(0, n - 1, m, A, p);
    assert(resultado == 3);
    assert(p == 4 );
}

void testMitad() {
    int n = 8;
    int m = 4;
    char A[] = {'z', 'y', 'a', 'b', 'c', 'd', 'x', 'w'};
    int p = 0;
    
    int resultado = dyv(0, n - 1, m, A, p);
    assert(resultado == 4);
    assert(p == 3);
}

void testMejorConstante() {
    int n = 8;
    int m = 4;
    char A[] = {'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a'};
    int p = 0;
    
    int resultado = dyv(0, n - 1, m, A, p);
    assert(resultado == 4);
    assert(p == 1);
}

void testMejorCreciente() {
    int n = 8;
    int m = 4;
    char A[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    int p = 0;
    
    int resultado = dyv(0, n - 1, m, A, p);
    assert(resultado == 4);
    assert(p == 1);
}

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
    
    testPrincipio();
    testFinal();
    testMitad();
    testMejorConstante();
    testMejorCreciente();
    testPeorDecreciente();
    
    cout << "Todos los tests pasaron correctamente." << endl;
    return 0;
}