#ifndef DYVAOC8_H
#define DYVAOC8_H

#include <array>
#include <cmath>

// Quiero ordenar el vector segun las x para poder aplicar un 
// algoritmo de DyV
int partition(std::array<std::array<int,3>, 1000> &v, int ini, int fin) {
	int pivote = v[fin][1]; // El pivote es la última x del último junkbox
	int i = ini;
	std::array<int, 3> aux;
	// Bucle que recorre todo el vector
	for(int j = ini; j < fin; j++) {
		// Si el valor de la x de un junkbox es menor al pivote se colocan
		// las coordenadas en su lugar
		if(v[j][1] <= pivote) {
			aux = v[j];
			v[j] = v[i];
			v[i] = aux;
			i++;
		}
	}
	// Intercambio el pivote
	aux = v[i];
	v[i] = v[fin];
       	v[fin] = aux;
	// Devuelvo la posición en la que esta el pivote	
	return i;
}

// Funcion que ordena el array
std::array<std::array<int, 3>, 1000> QuickSort(std::array<std::array<int, 3>, 1000> &v, int ini, int fin) {
	if(ini < fin) {
		int pivote = partition(v, ini, fin);
		QuickSort(v, ini, pivote-1);
		QuickSort(v, pivote+1, fin);
	}
	return v;
}

float distance (const std::array<int, 3> &v1, const std::array<int, 3> &v2) {
	// La distancia geometrica entre dos puntos es:
	// raiz cuadrada de las diferencias entre sus coordenadas al cuadrado
	float x = pow((v1[0] - v2[0]),2) + pow((v1[1] - v2[1]),2) + pow((v1[2] - v2[2]),2);
	x = std::sqrt(x);
	return x;
}

// Función que busca la distancia minima entre dos junkboxes
// min es la distancia anterior
// Se pone para que la funcion no siempre coja el mismo valor 
void find_min_distance(std::array<std::array<int, 3> 1000> &v, int min, int ini, int fin,
			std::array<int, 3> *j1, std::array<int, 3> *j2) {
	if(ini < fin) {
		int mid = (ini + fin) / 2;


	}
	
	
	
	
}

#endif
