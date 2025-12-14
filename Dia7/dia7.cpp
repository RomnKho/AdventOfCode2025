#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <fstream>

using namespace std;

// Hash para pair<int,int>
struct PairHash {
    size_t operator()(const pair<int,int>& p) const {
        //Guardamos la fila y columna en un número único para poder guardar la clave
        //La razón por la que multiplicamos por 1000 es para que no haya ninguna colisión entre las claves
        return p.first * 1000 + p.second; 
    }
};


// Función para leer el input desde archivo
void LeerInput(const string& archivo, vector<string>& mapa) {
    ifstream input(archivo);

    if (!input) {
        cerr << "Error: no se pudo abrir " << archivo << endl;
        return;
    }

    string line;
    while (getline(input, line)) {
        mapa.push_back(line);
    }
}

// Función que resuelve el problema
long long contar_splits(const vector<string>& mapa) {
    if (mapa.empty()){
         return 0;
    }
    //Establezco las dimensiones del mapa con las variables L(línea) y C(columna)

    int L = mapa.size();
    int C = mapa[0].size();

    // Buscar la 'S' en la primera fila.
   
    int columnaInicial = -1;
    for (int c = 0; c < C; c++) {
        if (mapa[0][c] == 'S') {
            columnaInicial = c;
            break;
        }
    }
    // En el caso de que no se encuentre la 'S' no se puede iniciar el programa.

    if (columnaInicial == -1 || L == 1) {
        return 0;
    }
    // Conjunto de posiciones activas actualmente
    unordered_set<pair<int,int>, PairHash> activas;
    activas.insert({1, columnaInicial});

    // Conjunto de splitters ya visitados
    unordered_set<pair<int,int>, PairHash> splitters_visitados;
    long long totalSplits = 0;

    // Mientras haya posiciones activas
    while (!activas.empty()) {
        unordered_set<pair<int,int>, PairHash> next;

        // Convertimos activas a vector para recorrer con índice
        vector<pair<int,int>> activas_vec(activas.begin(), activas.end());

        for (size_t i = 0; i < activas_vec.size(); i++) {
            pair<int,int> pos = activas_vec[i];
            int l = pos.first;
            int c = pos.second;

            if (l >= L) continue; // nos salimos del mapa

            char celda = mapa[l][c];

            if (celda == '.') {
                // Avanzar recto
                if (l + 1 < L)
                    next.insert({l + 1, c});
            }
            else if (celda == '^') {
                // Solo contar si no lo hemos visitado antes
                if (!splitters_visitados.count({l, c})) {
                    splitters_visitados.insert({l, c});
                    totalSplits++;

                    int nl = l + 1;
                    if (nl < L) {
                        if (c - 1 >= 0){
                            // diagonal izquierdo
                            next.insert({nl, c - 1});
                        } 
                        if (c + 1 < C){
                            // diagonal derecho
                            next.insert({nl, c + 1});
                         } 
                    }
                }
            }
        }

        // Avanzamos al siguiente paso
        activas = move(next);
    }

    return totalSplits;
}

int main() {
    vector<string> mapa;

    // Leer archivo
    LeerInput("input.txt", mapa);

    // Llamamos al error en caso de que el mapa esté vacío
    if (mapa.empty()) {
        cerr << "El archivo está vacío o no se pudo leer.\n";
        return 1;
    }

    // Cargamos el resultado de la función para luego sacarlo en pantalla.
    long long resultado = contar_splits(mapa);

    cout << "Resultado: " << resultado << endl;
    return 0;
}