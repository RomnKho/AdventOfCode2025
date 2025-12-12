
#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <vector>
#include <algorithm>
#include <cmath>

// Memoria que ira guardando las areas entres todos las coordenadas que se pasan
// M[0][1] será, por ejemplo, el area entre la primera coordenada y la segunda
// Esto es todo según el orden que se proporciona en el input
std::vector<std::vector<long long>> Memoria;

// n es el tamaño del vector
void inicializarMemoria(int n) {
	Memoria.resize(n, std::vector<long long>(n, -1)); // -1 = noCalculado
}

// Función que calcula el area entre dos coordenadas
// i, j son las posiciones de las coordenadas en el vector vCoords
long long calcularArea(std::vector<std::array<long long,2>> &vCoords, int i, int j) {
	// Si ya se ha calculado previamente el area de esas dos coordenadas
	if(Memoria[i][j] != -1) {
		return Memoria[i][j];
	}

	// Se calcula el area
	long long coordsX = std::abs(vCoords[i][0] - vCoords[j][0]);
	long long coordsY = std::abs(vCoords[i][1] - vCoords[j][1]);
	long long area = coordsX * coordsY;

	// Se guarda en la memoria
	Memoria[i][j] = area;
	Memoria[j][i] = area;

	return area;
}

// Función que busca el area máxima entre dos coordenadas
// coords se lo proporciona el usuario y vCoords es el vector en donde bsca el maximo
// ini es la posición incial del vector y fin la posición final
// i es la posicion de coords en vCoords

long long maxArea(std::vector<std::array<long long,2>> &vCoords, int ini, int fin, std::array<long long,2> coords, int i) {
	if(ini == fin) {
		// std::cout << "Se calcula area de " << i << " y " << ini << std::endl;
		return calcularArea(vCoords, i, ini); // Devuelve el area calculada
	} else {
		int mid = (ini + fin) / 2; 
		// std::cout << "dividiendose vector..." << std::endl;
		return std::max(maxArea (vCoords, ini, mid, coords, i), maxArea(vCoords, mid+1, fin, coords, i));
	}
}

std::vector<std::array<long long, 2>> leer(std::string nombre){
    std::vector<std::array<long long,2>> coordenadas;
    std::array<long long,2> a;
    std::ifstream archivo (nombre);
	long long x, y;
	char coma;

    if (!archivo.is_open()){
        std::cout << "No se ha encontrado el archivo";
        return coordenadas;  // Retorna vector vacío si no se pudo abrir
    }

    while(archivo >> x >> coma >> y){ 
        a = {x, y};
        coordenadas.push_back(a);
    }
    return coordenadas;
}

int main() {

	std::vector<std::array<long long,2>> vCoords;

	vCoords = leer("input.txt");

	long long areaMaxima = -1;
	long long areaActual = -1;

	// inicializar la memoria con el tamaño del vector 
	inicializarMemoria(vCoords.size());

	for(int i = 0; i < vCoords.size(); i++) {
		areaActual = maxArea(vCoords, 0, vCoords.size()-1, vCoords[i], i);
		if(areaActual > areaMaxima) {
			areaMaxima = areaActual;
		}
	}

	std::cout << "Área más grande: " << areaMaxima << std::endl;
	return 0;
}


