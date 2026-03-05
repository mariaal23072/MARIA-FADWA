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
    
    // Caso base
    int longitud = fin - ini +1;

    // Si el tramo que tengo es menor que m, no puedo formar ni una cadena de tamaño m.
    if (longitud < m){
        return 0;
    }

    // Si el tramo mide exactamente m, solo hay una ventana posible.
    // Hago lo mismo que he hecho en el iterativo, pero solo para esta ventana.
    if (longitud == m){
        int max_local = 1;
        int cont = 1;

        for(int i = ini; i< fin; i++){
            if (A[i] <= A[i+1]){
                cont++;
            }else{
                if (cont >= max_local){
                    max_local = cont;
                }
                cont = 1;
            
        }
        if (cont <= max_local){
            max_local = cont;
        }

        p = ini + 1;  // Actualizo p (empezando en 1, como me piden)
        return max_local;
    }

}
