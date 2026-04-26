#ifndef MI_CAMISETA_BT_H
#define MI_CAMISETA_BT_H

#include <iostream>
#include <vector>
#include <string>
using namespace std;


// estructura para las preferencias del cada voluntario
struct Voluntario {
    int opcion1;
    int opcion2;
};

// Funcion para que me sea más facil saber las tallas y no me líe
int tallaEntero(string talla);

// Función recursiva de Backtracking
bool asignarCamisetas(const vector<Voluntario>& voluntarios, vector<int>& stock, int indice);

#endif