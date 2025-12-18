#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

// Una entrada simple para nuestra tabla
struct Entrada {
    int l, c;
    bool ocupado = false; // Para saber si hay algo en esta celda
};

class TablaHash {
    public:
        int tam;
        vector<Entrada> tabla;

    public:
        // Inicializamos con un tamaño un poco mayor al mapa para evitar que se llene
        TablaHash(int n) : tam(n), tabla(n) {}

        //Colocamos las posiciones dependiendo de la línea y la columna y la guardamos en un índice.
        //Multiplicamos por 1000 las líneas para que no hayan colisiones, se podría multiplicar tanto 
        //líneas como columnas o multiplicar por cualquier otro número mientras sea para ahorrar colisiones.
        bool insert(int l, int c) {
            int indice = ((unsigned long long)l * 1000 + c) % tam;

            // Si el hueco está ocupado, buscamos el siguiente
            while (tabla[indice].ocupado) {
                // Si ya existe la posición, no podemos insertarla y tenemos que buscar otro hueco libre
                if (tabla[indice].l == l && tabla[indice].c == c) return false;
                
                indice = (indice + 1) % tam; 
            }

            // Cuando encontramos un hueco libre guardamos su posición y la marcamos como ocupada.
            tabla[indice].l = l;
            tabla[indice].c = c;
            tabla[indice].ocupado = true;
            return true;
        }

        //Limpiamos el vector para poder reutilizar la tabla
        void limpiar() {
            for(int i = 0; i < tam; i++){
                
            tabla[i].ocupado = false;
            }
        }
};



long long contar_splits(const vector<string>& mapa) {
    if (mapa.empty()){
         return 0;
    }
    int L = mapa.size();
    int C = mapa[0].size();

    int columnaInicial = -1;
    //Recorremos para encontrar donde esta la posición de la S para empezar a buscar splitters
    for (int c = 0; c < C; c++) {
        if (mapa[0][c] == 'S') { 
            columnaInicial = c; 
            break; 
        }
    }
    //Si no encontramos la posición de S en la primera fila no podemos hacer el problema
    if (columnaInicial == -1 || L == 1){ 
        return 0;
    }

    // Tamaño: el doble del área para que siempre haya huecos libres y sea rápido
    int tam = (L * C * 2);

    TablaHash activas(tam);
    activas.insert(1, columnaInicial);

    TablaHash splitters_visitados(tam);
    long long totalSplits = 0;

    while (true) {
        TablaHash next(tam);
        bool nuevasEncontradas = false;

        
       // Recorremos toda la tabla hash de posiciones actuales
        for (int i = 0; i < activas.tam; i++) {
            // Si la celda de la tabla está vacía, saltamos a la siguiente
            if (!activas.tabla[i].ocupado) {
                continue;
            }

            // Extraemos la posición actual para trabajar mejor
            int filaActual = activas.tabla[i].l;
            int colActual  = activas.tabla[i].c;

            // Si la fila está fuera de los límites del mapa, la ignoramos
            if (filaActual >= L) {
                continue;
            }

            char celda = mapa[filaActual][colActual];

            // CASO 1: Es un camino libre (.)
            if (celda == '.') {
            // Simplemente intentamos avanzar a la fila de abajo
                if (filaActual + 1 < L) {
                    if (next.insert(filaActual + 1, colActual)) {
                    nuevasEncontradas = true;
                    }
                }
            } 
    
            // CASO 2: Es un divisor (^)
            else if (celda == '^') {
                // Insertamos el splitter como visitado y aumentamos el total de splits.
                // Si 'insert' devuelve true, significa que es la primera vez que lo vemos.
                if (splitters_visitados.insert(filaActual, colActual)) {
                    totalSplits++;
                    // Calculamos las dos nuevas direcciones y comprobamos que no nos hayamos salido del mapa.
                    int filaSiguiente = filaActual + 1;
                    if (filaSiguiente < L) {
                        // Diagonal Izquierda
                        if (colActual - 1 >= 0) {
                            if (next.insert(filaSiguiente, colActual - 1)) {
                                nuevasEncontradas = true;
                            }
                        }
                        // Diagonal Derecha
                        if (colActual + 1 < C) {
                            if (next.insert(filaSiguiente, colActual + 1)) {
                                nuevasEncontradas = true;
                            }
                        }
                    }   
                }
            }
        }
        if (!nuevasEncontradas){ 
            break;
        }
        
        // Simplemente intercambiamos las tablas
        activas = next; 
    }

    return totalSplits;
}

int main() {
    vector<string> mapa;
    ifstream input("input.txt");
    string line;
    while (getline(input, line)) mapa.push_back(line);

    if (mapa.empty()) return 1;
    cout << "Resultado: " << contar_splits(mapa) << endl;
    return 0;
}