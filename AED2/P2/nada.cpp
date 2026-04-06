#include <iostream>
using namespace std;

const int MAX_ALUMNOS = 100;
const int MAX_PAREJAS = (MAX_ALUMNOS * (MAX_ALUMNOS - 1)) / 2; // -1 porque no se empareja consigo mismo

struct Pareja {
    int alumno1;
    int alumno2;
    int beneficio;
};

int organizacionClase(int N, int Amistad[][MAX_ALUMNOS], int Compenetracion[][MAX_ALUMNOS], int solucion[]) {
    
    Pareja lista_candidatos[MAX_PAREJAS]; // Lista de todas las parejas posibles con su beneficio
    bool emparejado[MAX_ALUMNOS]; // Para marcar si un alumno ya está emparejado
    
    // Poner todos los alumnos como no emparejados inicialmente
    for (int i = 0; i < N; i++) {
        emparejado[i] = false;
    }

    int beneficio_total = 0;
    int num_parejas = 0; // Contador de parejas generadas

    // Generar todas las parejas posibles con su beneficio
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            lista_candidatos[num_parejas].alumno1  = i;
            lista_candidatos[num_parejas].alumno2  = j;
            lista_candidatos[num_parejas].beneficio = (Amistad[i][j] + Amistad[j][i]) * (Compenetracion[i][j] + Compenetracion[j][i]);
            num_parejas++;
        }
    }

    // Ordenar por beneficio descendente (burbuja)
    for (int i = 0; i < num_parejas - 1; i++) {
        for (int j = 0; j < num_parejas - i - 1; j++) {
            if (lista_candidatos[j].beneficio < lista_candidatos[j + 1].beneficio) {
                Pareja tmp = lista_candidatos[j];
                lista_candidatos[j] = lista_candidatos[j + 1];
                lista_candidatos[j + 1] = tmp;
            }
        }
    }

    // Emparejar con avance rápido (greedy)
    int indice = 0;
    for (int k = 0; k < num_parejas; k++) {
        Pareja& p = lista_candidatos[k];
        if (!emparejado[p.alumno1] && !emparejado[p.alumno2]) {
            emparejado[p.alumno1] = true;
            emparejado[p.alumno2] = true;
            beneficio_total += p.beneficio;
            solucion[indice++] = p.alumno1;
            solucion[indice++] = p.alumno2;
        }
    }

    // Si N es impar, añadir el alumno sin pareja al final
    if (N % 2 != 0) {
        bool encontrado = false;
        for (int i = 0; i < N; i++) {
            if (!emparejado[i] && !encontrado) {
                solucion[indice] = i;
                encontrado = true;
            }
        }
    }

    return beneficio_total;
}

int main() {
    int P;
    cin >> P;

    while (P--) {
        int N;
        cin >> N;

        int Amistad[MAX_ALUMNOS][MAX_ALUMNOS] = {};
        int Compenetracion[MAX_ALUMNOS][MAX_ALUMNOS] = {};

        // Leer matriz de amistad (N-1 valores por fila, se omite la diagonal)
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N - 1; j++) {
                int val;
                cin >> val;
                // Los valores antes de la diagonal van en columnas 0..i-1
                // Los valores después van en columnas i+1..N-1
                if (j < i)
                    Amistad[i][j] = val;
                else
                    Amistad[i][j + 1] = val;
            }
        }

        // Leer matriz de compenetración (mismo formato)
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N - 1; j++) {
                int val;
                cin >> val;
                if (j < i)
                    Compenetracion[i][j] = val;
                else
                    Compenetracion[i][j + 1] = val;
            }
        }

        int solucion[MAX_ALUMNOS];
        int beneficio = organizacionClase(N, Amistad, Compenetracion, solucion);

        cout << beneficio << "\n";
        for (int i = 0; i < N; i++)
            cout << solucion[i] << " ";
        cout << "\n";
    }

    return 0;
}