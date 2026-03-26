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
int tallaEntero(string talla){
 
    if (talla == "XXL") return 0;
    else if (talla == "XL") return 1;
    else if (talla == "L") return 2;
    else if (talla == "M") return 3;
    else if (talla == "S") return 4;
    else if (talla == "XS") return 5;
    else return -1; // En caso deque haya algú error, aunque no debería haber
    // y el programa asueme que siempre está bien
}



int main() {
    int numCasos;

    // Leemos el número de casos de prueba


    
}