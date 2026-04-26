#ifndef ORGANIZACION_CLASE_AR_H
#define ORGANIZACION_CLASE_AR_H

#include <iostream>
using namespace std;

const int MAX_ALUMNOS = 3500;
const int MAX_PAREJAS = (MAX_ALUMNOS * (MAX_ALUMNOS - 1)) / 2;

struct Pupitre {
    int alum1;
    int alum2;
    int beneficio;
};

Pupitre pupitre[MAX_PAREJAS];

int organizacionClase(int N, int amistad[MAX_ALUMNOS][MAX_ALUMNOS], int trabajo[MAX_ALUMNOS][MAX_ALUMNOS], int solucion[MAX_ALUMNOS]);

#endif