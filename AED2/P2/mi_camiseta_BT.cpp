#include "mi_camiseta_BT.h"

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

// Función recursiva de Backtracking
bool asignarCamisetas(const vector<Voluntario>& voluntarios, vector<int>& stock, int indice) {

    // CASO BASE (Condición de parada)
    //Si el indice es igual al total de voluntarios, significa que hemos logrado pasar
    //por toda la fila y todos tienen camiseta.
    if (indice == (int)voluntarios.size()) {    // Aquí es donde tenía el error, lo he solucionado poniendo int para que no solo admita positivos
        return true;
    }

    // Cogemos al voluntario que le toca el turno en la fila
    Voluntario voluntarioActual = voluntarios[indice];

    // INTENTAMOS SU PRIMERA OPCIÓN
    if (stock[voluntarioActual.opcion1] > 0) {

        // Le "prestamos" la camiseta (restamos 1 al inventario)
        stock[voluntarioActual.opcion1]--;

        // Magia recursiva: Le decimos a la función que intente vestir al siguiente voluntario (indice + 1)
        if (asignarCamisetas(voluntarios, stock, indice + 1)) {
            return true;   // Si el resto de la fila consiguió camiseta, nosotros también devolvemos 'true' 
        } 

        // BACKTRACKING (Marcha atrás)
        // Si el 'if' anterior no entró, significa que darle esta camiseta a este voluntario
        // provocó que alguien de más atrás en la fila se quedara sin opciones.
        // Así que deshacemos el paso: le quitamos la camiseta (sumamos 1 al inventario)
        stock[voluntarioActual.opcion1]++;
    }

    // INTENTAMOS SU SEGUNDA OPCIÓN
    // (Solo llega aquí si la primera opción no había stock o si hacer la primera opción provocó un fallo luego)
    if (stock[voluntarioActual.opcion2] > 0) {

        // Le prestamos esta otra camiseta
        stock[voluntarioActual.opcion2]--;

        //Intentamos vestir al resto de la fila
        if (asignarCamisetas(voluntarios, stock, indice + 1)) {
            return true;
        }

        // BACKTRACKING
        // SI tampoco funciona, le volvemos a quitar la camiseta
        stock[voluntarioActual.opcion2]++;
    }


    // Ninguna opción sirvió
    return false;

}
