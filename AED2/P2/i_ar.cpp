#include <iostream>
#include <algorithm>
using namespace std;

const int MAX_ALUMNOS = 100;
const int MAX_PAREJAS = (MAX_ALUMNOS * (MAX_ALUMNOS - 1)) / 2;

struct Pupitre {
    int alum1;
    int alum2;
    int beneficio;
};



Pupitre pupitre[MAX_PAREJAS];

// Para ordenar de mayor a menor beneficio
bool compararParejas(Pupitre a, Pupitre b) {
    return a.beneficio > b.beneficio;
}

int organizacionClase(int N, int amistad[MAX_ALUMNOS][MAX_ALUMNOS], int trabajo[MAX_ALUMNOS][MAX_ALUMNOS], int solucion[MAX_ALUMNOS]) {
    
    int beneficio_total = 0;
    int pareja = 0;
    bool emparejado[MAX_ALUMNOS] = {};

    for (int i = 0; i < N; i++) {
        for (int j = i+1; j < N; j++) { // i+1 para no generar parejas repetidas
            pupitre[pareja].beneficio = (amistad[i][j] + amistad[j][i]) * (trabajo[i][j] + trabajo[j][i]);
            pupitre[pareja].alum1 = i;
            pupitre[pareja].alum2 = j;

            pareja++;

        }
    }

    // Ordenar solo desde el inicio hasta el nº de parejas generado
    sort(pupitre, pupitre + pareja, compararParejas);

    int indice = 0;
    // elegir parejas válidas dentro de las ordenadas
    for (int k = 0; k < pareja; k++) {
        if (!emparejado[pupitre[k].alum1] && !emparejado[pupitre[k].alum2]) {
            emparejado[pupitre[k].alum1] = true;
            emparejado[pupitre[k].alum2] = true;
            beneficio_total = beneficio_total + pupitre[k].beneficio;

            solucion[indice] = pupitre[k].alum1;
            indice++;
            solucion[indice] = pupitre[k].alum2;
            indice++;
            
        }
    }

    // En caso de que haya alumnos impares
    if (N % 2 != 0) {
        for (int i = 0; i < N; i++) {
            if (!emparejado[i]) {
                solucion[indice] = i;
            }
        }
    }

    return beneficio_total;
}

int main () {

    // ENTRADA
    int P; // número de casos prueba
    cin >> P;

    // Bucle para cada caso prueba
    for (int i = 0; i < P; i++) {
        int N; // número de alumnos
        cin >> N;

        int amistad[MAX_ALUMNOS][MAX_ALUMNOS] = {};
        int trabajo[MAX_ALUMNOS][MAX_ALUMNOS] = {};

        // Bucle para matriz amistad
        for (int fila = 0; fila < N; fila++) {
            for (int columna = 0; columna < N-1; columna++) {
                if (columna < fila){
                    cin >> amistad[fila][columna]; // antes de la diagonal
                }
                else {
                    cin >> amistad[fila][columna+1]; // saltar la diagonal
                }
            }
        }

        // Bucle apra matriz de trabajo
        for (int fila = 0; fila < N; fila++) {
            for (int columna = 0; columna < N-1; columna++) {
                if (columna < fila){
                    cin >> trabajo[fila][columna];
                }
                else {
                    cin >> trabajo[fila][columna+1];
                }
            }
        }

        // SALIDA
        int solucion[MAX_ALUMNOS] = {};
        int beneficio_total = organizacionClase(N, amistad, trabajo, solucion);
        
        cout << beneficio_total << endl;
        for (int alumn = 0; alumn < N; alumn++) {
            cout << solucion[alumn] << " ";
        }
        cout << endl;
  

    }

    return 0;
}