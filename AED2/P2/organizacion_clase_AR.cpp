#include "organizacion_clase_AR.h"
#include <algorithm>

Pupitre pupitre[MAX_PAREJAS]; // array global para almacenar las parejas y sus beneficios, con un tamaño máximo de parejas posibles

// Para ordenar de mayor a menor beneficio
bool compararParejas(Pupitre a, Pupitre b) {
    return a.beneficio > b.beneficio;
}

int organizacionClase(int N, int amistad[MAX_ALUMNOS][MAX_ALUMNOS], int trabajo[MAX_ALUMNOS][MAX_ALUMNOS], int solucion[MAX_ALUMNOS]) {
    
    int beneficio_total = 0; // variable para acumular el beneficio total
    int pareja = 0; // variable para contar el número de parejas generadas
    bool emparejado[MAX_ALUMNOS] = {}; // array para marcar si un alumno ya ha sido emparejado

    // Generar todas las parejas posibles y calcular su beneficio
    for (int i = 0; i < N; i++) {
        for (int j = i+1; j < N; j++) { // i+1 para no generar parejas repetidas
            // Calcular el beneficio de la pareja (i, j) y almacenarlo en el array de pupitres
            pupitre[pareja].beneficio = (amistad[i][j] + amistad[j][i]) * (trabajo[i][j] + trabajo[j][i]);
            pupitre[pareja].alum1 = i; // almacenar el índice del alumno 1 en la pareja
            pupitre[pareja].alum2 = j; // almacenar el índice del alumno 2 en la pareja

            pareja++;
        }
    }

    // Ordenar solo desde el inicio hasta el nº de parejas generado
    sort(pupitre, pupitre + pareja, compararParejas);

    int indice = 0; // variable para llevar el índice de la solución
    // elegir parejas válidas dentro de las ordenadas
    for (int k = 0; k < pareja; k++) {
        // Verificar si ambos alumnos de la pareja no han sido emparejados aún
        if (!emparejado[pupitre[k].alum1] && !emparejado[pupitre[k].alum2]) {
            emparejado[pupitre[k].alum1] = true; // marcar al alumno 1 como emparejado
            emparejado[pupitre[k].alum2] = true; // marcar al alumno 2 como emparejado
            beneficio_total = beneficio_total + pupitre[k].beneficio; // acumular el beneficio total

            // Agregar los alumnos de la pareja a la solución
            solucion[indice] = pupitre[k].alum1;
            indice++;
            solucion[indice] = pupitre[k].alum2;
            indice++;
            
        }
    }

    // En caso de que haya alumnos impares
    if (N % 2 != 0) {
        // Buscar el alumno que no ha sido emparejado y agregarlo a la solución
        for (int i = 0; i < N; i++) {
            if (!emparejado[i]) {
                solucion[indice] = i;
            }
        }
    }

    return beneficio_total; // retornar el beneficio total acumulado
}