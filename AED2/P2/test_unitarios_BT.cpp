#include <iostream>
#include <vector>
#include <cassert>
#include "mi_camiseta_BT.h"

using namespace std;

// ejemplo 1 del enunciado (Debe devolver YES / true)
void testEjemplo1() {
    int N = 18;
    int M = 6;
    vector<int> stock(6, N / 6); // 18 / 6 = 3 camisetas de cada talla iniciales

    // Preferencias orig: L XL, XL L, XXL XL, S XS, M S, M L
    // Convertidas a enteros:
    vector<Voluntario> voluntarios = {
        {2, 1}, {1, 2}, {0, 1}, {4, 5}, {3, 4}, {3, 2}
    };

    bool esPosible = asignarCamisetas(voluntarios, stock, 0);
    assert(esPosible == true);
}

// ejemplo 2 del enunciado (Debe devolver NO / false)
void testEjemplo2() {
    int N = 6;
    int M = 4;
    vector<int> stock(6, N / 6); // 6 / 6 = 1 camiseta de cada talla

    // Preferencias orig: S XL, L S, L XL, L XL
    // Convertidas a enteros:
    vector<Voluntario> voluntarios = {
        {4, 1}, {2, 4}, {2, 1}, {2, 1}
    };

    bool esPosible = asignarCamisetas(voluntarios, stock, 0);
    assert(esPosible == false);
}

// ejemplo 3 del enunciado (Debe devolver YES / true)
void testEjemplo3() {
    int N = 6;
    int M = 1;
    vector<int> stock(6, N / 6); // 1 camiseta de cada talla

    // Preferencias orig: L M
    // Convertidas a enteros:
    vector<Voluntario> voluntarios = {
        {2, 3}
    };

    bool esPosible = asignarCamisetas(voluntarios, stock, 0);
    assert(esPosible == true);
}

// sin stock (devolver NO / false)
void testMochilaVacia() {
    int M = 2;
    // Si N=0, array de stock todo a 0
    vector<int> stock(6, 0); 
    
    vector<Voluntario> voluntarios = {
        {0, 1}, {1, 2}
    };

    bool esPosible = asignarCamisetas(voluntarios, stock, 0);
    assert(esPosible == false);
}

int main() {
    testEjemplo1();
    testEjemplo2();
    testEjemplo3();
    testMochilaVacia();

    std::cout << "Todos los tests de BT pasaron!" << std::endl;
    return 0;
}