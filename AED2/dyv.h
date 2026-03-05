#ifndef DYV_H
#define DYV_H

#include <iostream>
using namespace std;

// m<=n, donde n = longitud de la cadena A, y m = longitud de la cadena B
const int m = 5; // longitud de la cadena B

 // Implementación del algoritmo iterativo
int iterativo(int n, int m, char A[], int &p);

 // Implementación del algoritmo divide y vencerás
int dyv(int ini, int fin, int m, char A[], int &p);







#endif