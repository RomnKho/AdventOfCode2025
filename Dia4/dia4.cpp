#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map> 
#include <utility>

using namespace std;

//Genera un mapa que asocia coordenadas(fila,columna) a un ID
using MapaID = map<pair<int, int>, int>;

//Genera una lista donde cada posicion tiene una lista de rollos conectados
using ListaAdyacentes = vector<vector<int>>;


// Función para leer el grid desde archivo
vector<string> leerGrid(const string& nombre_archivo, int& filas, int& columnas) {
    vector<string> lineasGrid;
    ifstream archivo(nombre_archivo);
    
    if (!archivo.is_open()) {
        cerr << "Error: No se pudo abrir " << nombre_archivo << endl;
        return lineasGrid;
    }
    
    string linea;
    filas = 0;
    columnas = 0;
    
    while (getline(archivo, linea)) {
        if (filas == 0) {
            columnas = linea.length();
        }
        lineasGrid.push_back(linea);
        filas++;
    }
    
    archivo.close();
    return lineasGrid;
}

// Función para asignar IDs únicos a cada rollo
MapaID asignarIDs(const vector<string>& lineasGrid, int& numVertices) {
    MapaID coord_to_ID;
    int Id_aux = 0;
    
    for (int r = 0; r < lineasGrid.size(); r++) {
        for (int c = 0; c < lineasGrid[r].length(); c++) {
            if (lineasGrid[r][c] == '@') {
                coord_to_ID[{r, c}] = Id_aux;
                Id_aux++;
            }
        }
    }
    
    numVertices = Id_aux;
    return coord_to_ID;
}

// Función para construir el grafo de conexiones entre rollos vecinos
ListaAdyacentes construirGrafo(const vector<string>& lineasGrid, 
                             const MapaID& coord_to_ID, 
                             int numVertices) {
    
    ListaAdyacentes adjList(numVertices); // Creamos lista de adyacencia
    
    // Direcciones de los 8 rollo adyacentes
    int dir[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1},           {0, 1},
        {1, -1},  {1, 0},  {1, 1}
    };
    
    int filas = lineasGrid.size();
    int columnas = lineasGrid[0].length();
    
    for (int f = 0; f < filas; f++) {
        for (int c = 0; c < columnas; c++) {
            if (lineasGrid[f][c] == '@') {
                int u = coord_to_ID.at({f, c}); // ID del rollo actual
                
                for (int d = 0; d < 8; d++) {
                    int nfilas = f + dir[d][0];
                    int ncolumnas = c + dir[d][1];
                    
                    // Verificar límites y si es rollo
                    if (nfilas >= 0 && nfilas < filas && ncolumnas >= 0 && ncolumnas < columnas && lineasGrid[nfilas][ncolumnas] == '@') {
                        
                        // Verificar si el vecino tiene ID asignado
                        auto it = coord_to_ID.find({nfilas, ncolumnas});
                        if (it != coord_to_ID.end()) {
                            int v = it->second; // ID del vecino
                            
                            // Evitar rollos conectados dos veces
                            if (v > u) {
                                adjList[u].push_back(v);
                                adjList[v].push_back(u);
                            }
                        }
                    }
                }
            }
        }
    }
    
    return adjList;
}

// Contar rollos con menos de 4 adyacentes
int contarAccesibles(const ListaAdyacentes& adjList) {
    int accessibleCount = 0;
    
    for (int i = 0; i < adjList.size(); ++i) {
        int degree = adjList[i].size(); // Catidad de rollos adyacentes a uno
        if (degree < 4) {
            accessibleCount++;
        }
    }
    
    return accessibleCount;
}

int main() {
  
    int filas = 0, columnas = 0;
    
    //
    vector<string> lineasGrid = leerGrid("input.txt", filas, columnas);
    
    if (filas == 0 || columnas == 0) {
        cerr << "Error: Archivo vacío o formato incorrecto" << endl;
        return 1;
    }

    int numVertices = 0;

    MapaID coord_to_ID = asignarIDs(lineasGrid, numVertices);
    
    ListaAdyacentes adjList = construirGrafo(lineasGrid, coord_to_ID, numVertices);

    int accessibleCount = contarAccesibles(adjList);
    
    cout << "Rollos accesibles: " << accessibleCount << endl;
    
    return 0;
}