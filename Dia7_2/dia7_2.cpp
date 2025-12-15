#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <array>


// Clase para crear nodos
class Node {
    public:
        std::array<int,2> coords; // Se guardan las dos coordenadas
        Node *right;
        Node *left;

    public:
        // Constructor
        Node(std::array<int,2> coords, Node *right = nullptr, Node *left = nullptr) {
            this->coords = coords;
            this->right = right;
            this->left = left;
        }
};

// Clase para crear el árbol
class Arbol {
    private:
        Node *root;
        int numSplits;

    public:
        // Constructor
        Arbol() {
            root = nullptr;
            numSplits = 0;
        }

        void insert(std::array<int,2> coordsSplit) {
            if(root == nullptr) {
                // Si la raiz no apunta a nadie se coloca el primer nodo
                // del árbol
                root = new Node(coordsSplit);
                numSplits++;
            } else {
                // El arbol ya tiene una raiz 
                Node *aux = root;

                // Creo otro auxiliar con los valores a insertar
                Node *auxCoords = new Node(coordsSplit);

                // Bucle para colocar auxCoords donde debe
                while(aux->right != auxCoords || aux->left != auxCoords) {
                    // Si la x es menor o igual al anterior y aun sigue habiendo elementos 
                    if(auxCoords->coords[0] <= aux->coords[0] && aux->left != nullptr) {
                        aux = aux->left;
                    }
                    // Si la x es mayor al anterior y aun sigue habiendo elementos 
                    if(auxCoords->coords[0] > aux->coords[0] && aux->right != nullptr) {
                        aux = aux->right;
                    }
                    // Si la x es menor o igual al anterior y no hay más elementos en el árbol
                    if(auxCoords->coords[0] <= aux->coords[0] && aux->left == nullptr) {
                        aux->left = auxCoords;
                    }
                    // Si la x es mayor al anterior y no hay más elementos en el árbol
                    if(auxCoords->coords[0] > aux->coords[0] && aux->left == nullptr) {
                        aux->right = auxCoords;
                    }
                }
            }
            numSplits++;
        }

        private:

        

        long long numCaminos() {
            
        }

};

// Función de leer el archivo y construir el arbol
void leer(std::string name, std::set<std::array<long long,2>> &bst) {
    std::string line;
    std::ifstream fich(name);

    if(!fich.is_open()) {
        std::cerr << "No se ha encontrado archivo con ese nombre";
    }

    int y = 0;

    while(std::getline(fich, line)) {
        for(long long i = 0; i < line.length(); i++) {
            // El primero siempre es la S
            if(line[i] == 'S') {
                bst.insert({i, y});
                std::cout << "Se ha insertado la S en: " << i << y << std::endl;
            }
            // Ir guardando donde están los splits
            if(line[i] == '^') {
               bst.insert({i, y}); // Inserto en el árbol las coordenadas
               std::cout << "Se ha insertado: " << i << " " << y << std::endl;
            }
        }
        y++; // Aumenta de linea
    }
}

int main() {
    // Creo el arbol de arrays
    std::set<std::array<long long,2>> bst;

    std::string name = "input.txt";

    leer(name, bst);
    long long caminos = 0;

    for(const auto& i : bst) {
        caminos++;
    }

    std::cout << "Hay " << caminos << " caminos posibles" << std::endl;

    return 0;

}
