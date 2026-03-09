#include <iostream>
#include "dyv.h"
#include <cassert>
#include <math.h>
#include <fstream>
#include <chrono>
#include <algorithm>
#include <vector>

using namespace std;

// Peor caso: cadena igual o creciente
vector<char> generarPeorCaso(int longitud) {
    vector<char> A(longitud);
    for (int i = 0; i < longitud; ++i) {
        A[i] = 'a'; // cadena de caracteres iguales
    }
    return A;
}

// Mejor caso: cadena decreciente
vector<char> generarMejorCaso(int longitud) {
    vector<char> A(longitud);
    for (int i = 0; i < longitud; ++i) {
        A[i] = 'z' - (i % 26); // cadena de caracteres decrecientes (repite cada 26 caracteres)
    }
    return A;
}


// Mide el tiempo que tarda la función en ejecutarse
double medirTiempo(vector<char>& A, int m) {
    auto start = std::chrono::high_resolution_clock::now();

    int p = 0; // indice de inicio subcadena más larga
    int resultado = dyv(0, A.size() - 1, m, A.data(), p); // pasamos A.data() ya que A es un vector y espera char A[]

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duracion = end - start;
    return duracion.count();
}

double mediana(std::vector<double> v) {
    int n = v.size();
    if (n == 0) return 0.0;

    std::sort(v.begin(), v.end());

    if (n % 2 == 1)
        return v[n / 2];
    else
        return (v[n / 2 - 1] + v[n / 2]) / 2.0;
}

int main() {
    std::vector<int> longitudes;
    for (int i = 0; i <= 10; i += 1) {
        longitudes.push_back(1000 * pow(2, i));
    }

    int m = 5; // longitud de la cadena B a buscar

    std::ofstream csv("resultados.csv");
    csv << "Longitud,MejorCaso,PeorCaso\n";

    for (int longitud : longitudes) {
        auto mejorCaso = generarMejorCaso(longitud);
        vector<double> mejoresCasos;
        for (int j = 0; j < 10; j += 1){
            auto mejorTiempo = medirTiempo(mejorCaso, m);
            mejoresCasos.push_back(mejorTiempo);
        }
        auto medianaMejorTiempo = mediana(mejoresCasos);
        

        auto peorCaso = generarPeorCaso(longitud);
        vector<double> peoresCasos;
        for (int j = 0; j < 10; j += 1){
            auto peorTiempo = medirTiempo(peorCaso, m);
            peoresCasos.push_back(peorTiempo);
        }
        auto medianaPeorTiempo = mediana(peoresCasos);
        
        csv << longitud << "," << medianaMejorTiempo << "," << medianaPeorTiempo << "\n";
    }

    csv.close();
    return 0;
}