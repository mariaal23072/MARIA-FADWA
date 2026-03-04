#include "dyv.h"

int iterativo(int n, int m, char A[], int &p) {

    p = 1;
    int cont = 1;
    int max = 1;

    int i = 0;
    while (i < n-m+1 && max < m) { // recorre Bs de la cadena A (hasta que no haya más Bs o hasta que max sea la longitud de la cadena B)
        cont = 1; // reinicio el contador
        for (int j = i; j <= i+m-2; j++) { // recorre carácteres de la cadena B hasta el penúltimo carácter (porque el último no tiene un siguiente para comparar)
            if (A[j] <= A[j+1]) { // si el carácter actual es menor o igual al siguiente, entonces está ordenado
                cont++;           // aumento el contador
            }
            else { // si el siguiente carácter no está ordenado
                if (cont >= max) { // si la cantidad de caracteres ordenados hasta ahora es mayor o igual que max
                    max = cont; // actualizo max
                    p = i+1; // actualizo p con la posición de inicio de la cadena ordenada más larga encontrada hasta ahora
                }
                cont = 1; // reinicio el contador
            }
        // volvemos a comparar con el siguiente carácter de la cadena B (a ver si hay una cadena ordenada más larga dentro de B)
        }
        if (cont >= max) { // comprobamos el último tramo ordenado de la cadena B
            max = cont;
            p = i+1; // actualizo p con la posición de inicio de la cadena ordenada más larga encontrada hasta ahora
        }
        i++;
    }

    return max;
}


int dyv(int ini, int fin, int m, char A[], int &p) {
    
    int max = 1;

    // Caso base:
    if (fin-ini+1 < m) { // si el tramo de la cadena A es menor que la longitud de la cadena B, entonces no hay solución
        return 0;
    }

    if (fin-ini+1 == m) { // si el tramo de la cadena A es igual a la longitud de la cadena B, entonces comprobamos si está ordenado
        for (int i = ini; i < fin; i++) {
            if (A[i] <= A[i+1]) {
                max++;
            }
            else {
                return 0; // si no está ordenado, entonces no hay solución
            }
        }
        p = ini+1; // actualizo p con la posición de inicio de la cadena ordenada encontrada
        return max;
    }

        // COMBINACIÓN:
    int maxU = 1;
    int pU = 0;

    // DIVIDE Y VENCERÁS:
    int mitad = (ini + fin) / 2; // posición de la mitad de A

    int maxIzq = dyv(ini, mitad, m, A, p); // máximo ordenado en la mitad izquierda
    int maxDer = dyv(mitad+1, fin, m, A, p); // máximo ordenado en la mitad derecha



    int cont = 1;

    for (int i = ini; i < fin; i++) {
        cont = 1; // reinicio el contador
        for (int j = i; j <= i+m-2; j++) { // recorre carácteres de la cadena B hasta el penúltimo carácter (porque el último no tiene un siguiente para comparar)
            if (A[j] <= A[j+1]) { // si el carácter actual es menor o igual al siguiente, entonces está ordenado
                cont++;           // aumento el contador
            }
            else { // si el siguiente carácter no está ordenado
                if (cont >= max) { // si la cantidad de caracteres ordenados hasta ahora es mayor o igual que max
                    max = cont; // actualizo max
                    p = i+1; // actualizo p con la posición de inicio de la cadena ordenada más larga encontrada hasta ahora
                }
                cont = 1; // reinicio el contador
            }
        // volvemos a comparar con el siguiente carácter de la cadena B (a ver si hay una cadena ordenada más larga dentro de B)
        }
        if (cont >= max) { // comprobamos el último tramo ordenado de la cadena B
            max = cont;
            p = i+1; // actualizo p con la posición de inicio de la cadena ordenada más larga encontrada hasta ahora
        }
    }

    

    

    return 0;
}
