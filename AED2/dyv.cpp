#include "dyv.h"

int iterativo(int n, int m, char A[], int &p) {

    p = 1;
    int cont = 1;
    int max = 1;

    int i = 0;
    while (i < n-m+1 && max < m ) { // recorre Bs de la cadena A (hasta que no haya más Bs o hasta que max sea la longitud de la cadena B)
        cont = 1; // reinicio el contador
        for (int j = i; j <= i+m-2; j++) { // recorre carácteres de la cadena B hasta el penúltimo carácter (porque el último no tiene un siguiente para comparar)
            if (A[j] <= A[j+1]) { // si el carácter actual es menor o igual al siguiente, entonces está ordenado
                cont++;           // aumento el contador
            }
            else { // si el siguiente carácter no está ordenado
                if (cont > max) { // si la cantidad de caracteres ordenados hasta ahora es mayor o igual que max
                    max = cont; // actualizo max
                    p = i+1; // actualizo p con la posición de inicio de la cadena ordenada más larga encontrada hasta ahora
                }
                cont = 1; // reinicio el contador
            }
        // volvemos a comparar con el siguiente carácter de la cadena B (a ver si hay una cadena ordenada más larga dentro de B)
        }
        if (cont > max) { // comprobamos el último tramo ordenado de la cadena B
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

    // Si el tramo mide exactamente m, solo hay una subcadena posible.
    // Hago lo mismo que he hecho en el iterativo, pero solo para esta subcadena.
    if (longitud == m){
        int max_local = 1;
        int cont = 1;

        for (int i = ini; i < fin; i++){
            if (A[i] <= A[i+1]){
                cont++;
            } else {
                if (cont > max_local){
                    max_local = cont;
                }
                cont = 1;
            }
        }
        if (cont > max_local){
            max_local = cont;
        }

        p = ini + 1;  // Actualizo p (empezando en 1, como me piden)
        return max_local;
    }

    // Divide y Vencerás
    int mitad = (ini + fin) / 2;

    int pIzq = 0;
    int maxIzq = dyv(ini, mitad, m, A, pIzq);

    int pDer = 0;
    int maxDer = dyv(mitad + 1, fin, m, A, pDer);

    // Ahora lo Combino (Zona del cruce)
    // Lo que tenemos que hacer es revisar las cadenas de tamaño 'm' que empiezan en la parte
    // izquierda y terminan en la parte derecha (que cruzan la frontera vamos)
    int maxCentro = 0;
    int pCentro = 0;


    // Calculo donde puede empezar una ventana para que cruce la mitad
    // Como muy tarde empieza en mitad y como muy pronto en mitad -m +2
    int inicio_cruce = mitad -m + 2;
    if(inicio_cruce < ini){
        inicio_cruce = ini;    //Evitamos salir por la izquierda
    }

    int fin_cruce = mitad;
    if(fin_cruce + m - 1> fin){
        fin_cruce = fin -m +1;    // Evitamos salir por la derecha
    }


    // Miro si todas las ventanas de tamaño m en esta zona del cruce
    for(int i = inicio_cruce; i <= fin_cruce; i++) {
        int cont = 1;
        int max_actual = 1;

        //Evalúo la racha dentro de esta ventana específica de tamaño m
        for (int j = i; j < i+m-1; j++) {
            if(A[j] <= A[j+1]){
                cont++;
            }else{
                if(cont > max_actual){
                    max_actual = cont;
                }
                cont = 1;
            }
        }
        if(cont > max_actual){
            max_actual = cont;
        }

        // Me quedo con la mejor ventana de la zona central
        // Y uso >= para que si hay empate, se actualice (como en el iterativo)
        if(max_actual > maxCentro){
            maxCentro = max_actual;
            pCentro = i + 1;
        }
    }

    // Mi Decisión Final (me quedo con la mejor de las tres partes)
    int max_final = maxIzq;
    p = pIzq;

    if(maxCentro > max_final){
        max_final = maxCentro;
        p = pCentro;
    }

    if(maxDer > max_final){
        max_final = maxDer;
        p = pDer;
    }

    return max_final;
}


