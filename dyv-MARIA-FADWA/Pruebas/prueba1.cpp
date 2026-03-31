#include <iostream>
using namespace std;

#include "../Codigo/dyv.h"

int main() {
    // Ejemplo del enunciado de la práctica
    char A[] = {'c', 'd', 'd', 'a', 'b', 'c', 'd', 'a', 'c', 'c'};
    int m = 5;
    int n = 10;
    
    // Posición cadena más larga
    int p_dyv = 0;
    int p_iter = 0;

    // Llamada al algoritmo Divide y Vencerás
    int resultado_iter = iterativo(n, m, A, p_iter);

    // Llamada al algoritmo Iterativo
    int resultado_dyv = dyv(0, n - 1, m, A, p_dyv);

    // Imprimir los resultados por pantalla
    cout << "ITERATIVO: Solucion: B, posicion de inicio igual a " << p_iter << ", y numero de caracteres en C igual a " << resultado_iter << endl;
    cout << "DYV: Solucion: B, posicion de inicio igual a " << p_dyv << ", y numero de caracteres en C igual a " << resultado_dyv << endl;


    return 0;
}