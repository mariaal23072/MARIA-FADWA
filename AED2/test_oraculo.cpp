#include <iostream>
#include "dyv.h"
#include <cassert>
#include <random>

using namespace std;

// Array A: Generar letras de la 'a' a la 'z' en un array
void generarSecuenciaAleatoria(int longitud, char A[], unsigned int semilla) {
    mt19937 gen(semilla);
    uniform_int_distribution<> dist('a', 'z');

    for (int i = 0; i < longitud; ++i) {
        A[i] = dist(gen);
    }
}

int main() {
    unsigned int semilla = 42;
    int m = 5;

    vector<int> longitudes = {5, 10, 20, 50, 100, 1000};

    for (size_t i = 0; i < longitudes.size(); ++i) {
        int longitud = longitudes[i];
        char A[longitud];
        
        generarSecuenciaAleatoria(longitud, A, semilla + i);

        int pDyv = 0;
        int pIter = 0;

        int dyvOutput = dyv(0, longitud - 1, m, A, pDyv);
        int resultadoIterativo = iterativo(longitud, m, A, pIter);
        
        cout << "Longitud de la secuencia: " << longitud << endl;
        cout << "Resultado DyV: " << dyvOutput << " (p=" << pDyv << ")" << endl;
        cout << "Resultado Iter: " << resultadoIterativo << " (p=" << pIter << ")" << endl;
        
        // Compara el máximo y la posición p
        assert(dyvOutput == resultadoIterativo && pDyv == pIter);
    }
    
    cout << "Pruebas superadas" << endl;
    return 0;
}