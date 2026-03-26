#include <iostream>
#include "dyv.h"
#include <cassert>
#include <math.h>
#include <fstream>
#include <chrono>
#include <algorithm>
#include <vector>

using namespace std;

// Peor caso: cadena decreciente
vector<char> generarPeorCaso(int longitud) {
    vector<char> A(longitud); // cadena a llenar
    for (int i = 0; i < longitud; ++i) {
        A[i] = 'z' - (i % 26); // cadena de caracteres decrecientes (repite cada 26 caracteres)
    }
    return A;
}

// Mejor caso: cadena creciente ( o cadena igual )
vector<char> generarMejorCaso(int longitud) {
    vector<char> A(longitud); // cadena a llenar
    for (int i = 0; i < longitud; ++i) {
        A[i] = 'a'; // cadena de caracteres iguales
        // También valdría:
        // A[i] = 'a' + (i % 26); // cadena de caracteres crecientes (repite cada 26 caracteres)
    }
    return A;
}


// Mide el tiempo que tarda la función en ejecutarse
double medirTiempo(vector<char>& A, int m) {
    auto start = std::chrono::high_resolution_clock::now(); // inicio de la medición

    int p = 0; // indice de inicio subcadena más larga
    int resultado = dyv(0, A.size() - 1, m, A.data(), p); // pasamos A.data() ya que A es un vector y espera char A[]

    auto end = std::chrono::high_resolution_clock::now(); // fin de la medición
    std::chrono::duration<double, std::milli> duracion = end - start; // duración en milisegundos
    return duracion.count(); // devuelve el tiempo en milisegundos
}

double mediana(std::vector<double> v) {
    int n = v.size(); // número de elementos
    if (n == 0) return 0.0; // caso de vector vacío

    std::sort(v.begin(), v.end()); // ordenamos el vector para calcular la mediana

    // Si el número de elementos es impar, la mediana es el elemento del medio
    // Si es par, la mediana es el promedio de los dos elementos del medio
    if (n % 2 == 1)
        return v[n / 2];
    else
        return (v[n / 2 - 1] + v[n / 2]) / 2.0;
}

int main() {
    std::vector<int> longitudes; // vector para almacenar las longitudes de las secuencias a probar
    // Generamos longitudes desde 1000 hasta 1 millón, aumentando de a potencias de 2
    for (int i = 0; i <= 10; i += 1) {
        longitudes.push_back(1000 * pow(2, i));
    }

    // Creamos un archivo CSV para guardar los resultados
    std::ofstream csv("resultados.csv");
    csv << "Longitud,MejorCaso,PeorCaso\n";

    // Para cada longitud, generamos el mejor caso y el peor caso, 
    // medimos el tiempo de ejecución y guardamos la mediana de los tiempos en el CSV
    for (int longitud : longitudes) {
        auto mejorCaso = generarMejorCaso(longitud); // Generamos el mejor caso para la longitud actual
        vector<double> mejoresCasos; // vector para almacenar los tiempos de ejecución del mejor caso
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
        
        // Guardamos los resultados en el CSV
        csv << longitud << "," << medianaMejorTiempo << "," << medianaPeorTiempo << "\n";
    }

    csv.close();
    return 0;
}