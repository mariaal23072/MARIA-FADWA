#include "organizacion_clase_AR.h"
#include <algorithm>


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