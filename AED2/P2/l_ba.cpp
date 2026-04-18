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

    // 2. INTENTAMOS SU PRIMERA OPCIÓN
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

    // 3. INTENTAMOS SU SEGUNDA OPCIÓN
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


    // 4. CALLEJÓN SIN SALIDA
    // Ninguna opción sirvió
    return false;

}




int main() {
    int numCasos;

    // Leemos el número de casos de prueba
    if (!(cin >> numCasos)) return 0;

    // Bucle para procesar cada caso de prueba
    while (numCasos > 0) {
        int N, M;
        cin >> N >> M; // N = total de camisetas, M = número de voluntarios

        // Calculamos cuántas camisetas hay de cada talla
        int camisetasPorTalla = N/6;

        //Creamos nuestro almacén (stock). Es un array de 6 posiciones.
        // Lo rellenamos inicialmente con la cantidad que acabamos de calcular.
        vector<int> stock(6, camisetasPorTalla);

        //Creamos una lista para guardar a todos nuestros voluntarios
        vector<Voluntario> voluntarios(M);

        // Leemos las preferecias de cada voluntario
        for (int i = 0; i < M; i++) {
            string talla1, talla2;
            cin >> talla1 >> talla2;

            //Guardamos las opciones ya traducidas a números
            voluntarios[i].opcion1 = tallaEntero(talla1);
            voluntarios[i].opcion2 = tallaEntero(talla2);
        }

        // Llamamos a la función empezando por el voluntario 0
        bool exito = asignarCamisetas(voluntarios, stock, 0);

        if (exito) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }


        numCasos--;     //Pasamos al siguiente cas
    }

    return 0;
    
}