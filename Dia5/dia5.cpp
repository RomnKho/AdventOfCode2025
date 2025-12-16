#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <string>
#include <sstream>
#include <unistd.h>

// Clase para crear nodos
class Node {
    public:
        std::array<long long,2> range; // Se guardan el rango
        Node *right;
        Node *left;

    public:
        // Constructor
        Node(std::array<long long,2> range, Node *right = nullptr, Node *left = nullptr) {
            this->range = range;
            this->right = right;
            this->left = left;
        }
};

// Clase para crear el árbol
class Tree {
    private:
        Node *root;
        int sz;

    public:
        // Constructor
        Tree() {
            root = nullptr;
            sz = 0;
        }

        // Método de inserción en el árbol
        void insert(std::array<long long,2> inputRange) {
            if(root == nullptr) {
                // Si la raiz no apunta a nadie se coloca el primer nodo
                // del árbol
                root = new Node(inputRange);
                sz++; // Numero de elementos en el árbol
            } else {
                // El arbol ya tiene una raiz 
                Node *aux = root;

                // Creo otro auxiliar con los valores a insertar
                Node *auxRange = new Node(inputRange);

                // Bucle para colocar auxCoords donde debe
                while(true) {
                    // Si el rango del que queremos insertar es más grande que el anterior
                    // lo fusionamos
                    // Ej. rango a insertar (15-25) | rango anterior (17-20)
                    // Pasa a ser (15-25)
                    if(auxRange->range[0] <= aux->range[0] && auxRange->range[1] >= aux->range[1]) {
                        aux->range = auxRange->range;
                        break;
                    }

                    // Si el primer elemento del rango es menor al anterior
                    if(auxRange->range[0] <= aux->range[0]) {
                        // Si hay nodo a la izquierda seguimos recorriendo
                        if(aux->left != nullptr) {
                            aux = aux->left;
                        }
                        // Si no hay nodo a la izquierda...
                        else {
                            aux->left = auxRange;
                            break;
                        }
                    }
                    // Si el primer elemento del rango es mayor al anterior
                    else if(auxRange->range[0] > aux->range[0]) {
                        // Si hay nodo a la derecha seguimos recorriendo
                        if(aux->right != nullptr) {
                            aux = aux->right;
                        }
                        // Si no hay nodo a la derecha... 
                        else {
                            aux->right = auxRange;
                            break;
                        }
                    }
                    
                }
            }
            sz++;
        }

        bool checkFreshness(long long id) {
            // Creo un nodo auxiliar para recorrer el arbol
            Node *aux = root;

            while(aux != nullptr) {
                // Mirar si el id se encuentra dentro del rango de alguno de los que nos han dado
                if(id >= aux->range[0]) {
                    if(id > aux->range[1]) {
                        aux = aux->right;
                    } else {
                        // std::cout << id << " en rango " << aux->range[0] << "-" << aux->range[1] << std::endl;
                        return true;
                    }
                } else {
                    aux = aux->left;
                }
            }

            // std::cout << id << " no está en ningún rango" << std::endl;
            return false; // No se ha encontrado
        }
};

void leerInput(std::string name, std::vector<std::array<long long,2>> &vRanges, std::vector<long long> &ids) {
    long long inf, sup, id;
    char hyphen;
    std::string line;
    bool readingRanges = true;

    std::ifstream fich(name);

    if(!fich.is_open()) {
        std::cerr << "No se pudo abrir el archivo" << std::endl;
        return;
    }

    while(std::getline(fich, line)) {
        // El espacio marca el cambio entre rangos e ids
        if(line.empty()) {
            readingRanges = false;
            continue;
        }

        // Dependiendo de lo que queremos leer 
        if(readingRanges) {
            std::istringstream ss(line);
            ss >> inf >> hyphen >> sup;
            vRanges.push_back({inf, sup});
        } else {
            std::istringstream ss2(line);
            ss2 >> id;
            ids.push_back(id);
        }
    }
}

int main() {

    std::vector<std::array<long long,2>> vRanges;
    std::vector<long long> ids;

    leerInput("input.txt", vRanges, ids);

    Tree tRanges;

    for(int i = 0; i < vRanges.size(); i++) {
        tRanges.insert(vRanges[i]);
    }

    long long countFresh = 0;
    for(int j = 0; j < ids.size(); j++) {
        if(tRanges.checkFreshness(ids[j])) {
            countFresh += 1;
        }
    }

    std::cout << "Alimentos frescos: " << countFresh << std::endl;

    return 0;
}
