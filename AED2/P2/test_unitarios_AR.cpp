#include <iostream>
#include <cassert>
#include "organizacion_clase_AR.h"

using namespace std;

int amistad[MAX_ALUMNOS][MAX_ALUMNOS] = {};
int trabajo[MAX_ALUMNOS][MAX_ALUMNOS] = {};
int solucion[MAX_ALUMNOS] = {};

// Funcion para borrrar (porq hemos declarado las matrices globales) y así no tener que reiniciar el programa cada vez
void limpiarMatrices(int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            amistad[i][j] = 0;
            trabajo[i][j] = 0;
        }
        solucion[i] = 0;
    }
}

// ejemplo del enunciado
void testEjemploEnunciado() {
    int N = 3;
    limpiarMatrices(N);
 
    // Llenar matriz amistad del ejemplo (sin diagonal)
    amistad [0] [1] = 5; 
    amistad [0] [2] = 6; 
    amistad [1] [0] = 4; 
    amistad [1] [2] = 3; 
    amistad [2] [0] = 2; 
    amistad [2] [1] = 1;

    // Llenar matriz trabajo del ejemplo (sin diagonal)
    trabajo [0] [1] = 5;
    trabajo [0] [2] = 3; 
    trabajo [1] [0] = 3; 
    trabajo [1] [2] = 2; 
    trabajo [2] [0] = 1; 
    trabajo [2] [1] = 5;

    int beneficio = organizacionClase(N, amistad, trabajo, solucion);
    
    // Verificamos que el beneficio máximo es exactamente 72
    assert(beneficio == 72); 
}

// todos se llevan bien, pero no trabajan (beneficio = 0)
void testSinCompenetracion() {
    int N = 2;
    limpiarMatrices(N);

    // Máxima amistad
    amistad[0][1] = 9; 
    amistad[1][0] = 9;
    
    // el producto (amistad * trabajo) debe dar 0.
    int beneficio = organizacionClase(N, amistad, trabajo, solucion);
    assert(beneficio == 0);
}

// número impar donde sobra 1 alumno y no hay parejas (N = 1)
void testUnSoloAlumno() {
    int N = 1;
    limpiarMatrices(N);

    int beneficio = organizacionClase(N, amistad, trabajo, solucion);
    
    // Al estar solo, no hay beneficio
    assert(beneficio == 0);
    // El alumno 0 debe estar en la posición 0 de la solución
    assert(solucion[0] == 0);
}

int main() {

    testEjemploEnunciado();
    testSinCompenetracion();
    testUnSoloAlumno();

    // Si llega aquí, significa que todo es correcto.
    cout << "Todos los tests de AR pasaron!" << endl;
    return 0;
}