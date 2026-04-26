#include <iostream>
#include "organizacion_clase_AR.h"
#include <cassert>
#include <math.h>
#include <fstream>
#include <chrono>
#include <algorithm>
#include <vector>

using namespace std;

int amistad_global[MAX_ALUMNOS][MAX_ALUMNOS];
int trabajo_global[MAX_ALUMNOS][MAX_ALUMNOS];
int solucion_global[MAX_ALUMNOS];

// genera un caso de prueba aleatorio para el peor caso llenando las matrices de amistad y trabajo con valores entre 1 y 9,
// excepto en la diagonal que es 0.
void generarPeorCaso(int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                amistad_global[i][j] = 0;
                trabajo_global[i][j] = 0;
            } else {
                amistad_global[i][j] = (rand() % 9) + 1; // Valores entre 1 y 9
                trabajo_global[i][j] = (rand() % 9) + 1;
            }
        }
    }
}

double medirTiempo(int n) {
    generarPeorCaso(n);

    auto start = std::chrono::high_resolution_clock::now();

    organizacionClase(n, amistad_global, trabajo_global, solucion_global);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    
    return duration.count();
}

double mediana(std::vector<double> v) {
    int n = v.size();
    if (n == 0) return 0.0;
    std::sort(v.begin(), v.end());
    if (n % 2 == 0) {
        return (v[n / 2 - 1] + v[n / 2]) / 2.0;
    } else {
        return v[n / 2];
    }
}

int main() {
    std::vector<int> longitudes;
    
    for (int i = 0; i <= 5; i += 1) {
        longitudes.push_back(100 * pow(2, i));
    }

    std::ofstream csv("resultados_AR.csv");
    csv << "Longitud,PeorCaso\n";

    std::cout << "Midiendo tiempos experimentales para AR..." << std::endl;

    for (int n : longitudes) {
        std::vector<double> tiempos;
        
        for (int iter = 0; iter < 10; iter++) {
            tiempos.push_back(medirTiempo(n));
        }
        
        double t_mediana = mediana(tiempos);
        std::cout << "N = " << n << " | Tiempo: " << t_mediana << " ms" << std::endl;
        csv << n << "," << t_mediana << "\n";
    }

    csv.close();
    std::cout << "Medicion completada." << std::endl;
    return 0;
}