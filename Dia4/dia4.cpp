#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

class GrafoRollos {
    private:
        // Atributos
        vector<string> grid;
        vector<vector<int>> ids;        // Matriz para guardar IDs (o -1 si no es rollo)
        vector<vector<int>> listaAdyacencia;    // Lista de adyacencia
        int filas;
        int columnas;
        int numVertices;
        
        // Direcciones de los 8 posibles rollos adyacentes
        const int dir[8][2] = {
            {-1, -1}, {-1, 0}, {-1, 1},
            {0, -1},           {0, 1},
            {1, -1},  {1, 0},  {1, 1}
        };
        
    public:
        // Constructor
        GrafoRollos() : filas(0), columnas(0), numVertices(0) {}
        
        // Método para cargar y procesar el grafo
        bool procesarArchivo(const string& nombre_archivo) {
            if (!leerGrid(nombre_archivo)) {
                return false;
            }
            
            asignarIDs();
            construirGrafo();
            
            return true;
        }
        
        // Método para leer el grid desde archivo
        bool leerGrid(const string& nombre_archivo) {
            ifstream archivo(nombre_archivo);
            
            if (!archivo.is_open()) {
                cerr << "Error: No se pudo abrir " << nombre_archivo << endl;
                return false;
            }
            
            string linea;
            filas = 0;
            columnas = 0;
            
            while (getline(archivo, linea)) {
                if (filas == 0) {
                    columnas = linea.length();
                }
                grid.push_back(linea);
                filas++;
            }
            
            archivo.close();
            
            if (filas == 0 || columnas == 0) {
                cerr << "Error: Archivo vacío o formato incorrecto" << endl;
                return false;
            }
            
            return true;
        }
        
        // Método para asignar IDs únicos a cada rollo
        void asignarIDs() {
            // Inicializar matriz de IDs con -1 = no rollo
            ids.assign(filas, vector<int>(columnas, -1)); //assign te pide 1 para cuantas filas crear y segundo para q poner en cada fila
            /*
                {@    .   .   @}
                {.    @   @   .}
                {@    .   @   .}
                
            ids = {
                { 0, -1, -1,  1},  // Fila 0: rollo en (0,0)=ID0 y (0,3)=ID1
                {-1,  2,  3, -1},  // Fila 1: rollo en (1,1)=ID2 y (1,2)=ID3
                { 4, -1,  5, -1}   // Fila 2: rollo en (2,0)=ID4 y (2,2)=ID5
            };
            */
            numVertices = 0;
            
            // Asignar IDs secuenciales a los rollos
            for (int f = 0; f < filas; f++) {
                for (int c = 0; c < columnas; c++) {
                    if (grid[f][c] == '@') {
                        ids[f][c] = numVertices;
                        numVertices++;
                    }
                }
            }
            
            // Preparar la lista de adyacencia
            listaAdyacencia.resize(numVertices);
        }
        
        // Método para construir el grafo de conexiones
        void construirGrafo() {
            
            // Recorrer todo el grid
            for (int f = 0; f < filas; f++) {
                for (int c = 0; c < columnas; c++) {
                    if (ids[f][c] != -1) {  // Si es un rollo
                        int idActual = ids[f][c]; //Nos quedamos con el ID
                        
                        // Se revisan las 8 casillas adyacentes
                        for (int d = 0; d < 8; d++) {
                            int nfilas = f + dir[d][0];
                            int ncolumnas = c + dir[d][1];
                            
                            // Verificar límites
                            if (nfilas >= 0 && nfilas < filas && ncolumnas >= 0 && ncolumnas < columnas) {
                                int idVecino = ids[nfilas][ncolumnas];
                                
                                // Si hay un rollo vecino y aún no está conectado
                                if (idVecino != -1 && idVecino > idActual) {
                                    // Añadir conexión en ambos sentidos (grafo no dirigido)
                                    listaAdyacencia[idActual].push_back(idVecino);
                                    listaAdyacencia[idVecino].push_back(idActual);
                                }
                            }
                        }
                    }
                }
            }
        }
        
        // Método para contar rollos con menos de 4 adyacentes
        int contarAccesibles() {
            int cont = 0;
            
            for (int i = 0; i < numVertices; i++) {
                //limite carretilla
                if (listaAdyacencia[i].size() < 4) {
                    cont++;
                }
            }
            
            return cont;
        }
};

int main() {

    GrafoRollos grafo;
    
    if (!grafo.procesarArchivo("input.txt")) {
        return 1;
    }
    
    cout << "Rollos accesibles: " << grafo.contarAccesibles() << endl;
    
    return 0;
}