#include <iostream>
#include "dyv.h"
#include <cassert>
#include <random>

using namespace std;

// Llenar el array con letras aleatorias de la 'a' a la 'z'
void generarSecuenciaAleatoria(int longitud, char A[], unsigned int semilla) {
    mt19937 gen(semilla);
    uniform_int_distribution<> dist('a', 'z');

    for (int i = 0; i < longitud; ++i) {
        A[i] = dist(gen);
    }
}

int main() {

    unsigned int semilla = 42; // Semilla ej para generar secuencias aleatorias
    int m = 5;

    // Tamaños de prueba
    vector<int> longitudes = {5, 10, 20, 50, 100, 1000};

    for (size_t i = 0; i < longitudes.size(); ++i) {
        int longitud = longitudes[i];
        // Aqui guardamos la secuencia de letras
        char A[longitud];
        
        // Cambiamos la semilla en cada vuelta para que no salga siempre igual
        generarSecuenciaAleatoria(longitud, A, semilla + i);

        // Posicion que devuelve cada algoritmo
        int pDyv = 0;
        int pIter = 0;

        // Probamos los dos algoritmos: DyV e iterativo
        int resultadoIterativo = iterativo(longitud, m, A, pIter);
        int dyvOutput = dyv(0, longitud - 1, m, A, pDyv);
        
        cout << "Longitud de la secuencia: " << longitud << endl;
        cout << "Resultado DyV: " << dyvOutput << " (p = " << pDyv << ")" << endl;
        cout << "Resultado Iter: " << resultadoIterativo << " (p = " << pIter << ")" << endl;
        
        // Si esto falla, es que los dos metodos no coinciden (compara el resultado y la posicion de ambos algoritmos)
        assert(dyvOutput == resultadoIterativo && pDyv == pIter);
    }
    
    // Si llegamos aqui, todo ha ido bien
    cout << "Pruebas superadas!!" << endl;
    return 0;
} 