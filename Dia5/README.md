## DÍA 5

### ÁRBOLES BINARIO DE BÚSQUEDA
- e
- e
- e
- e

### EXPLICACIÓN FUNCIONES USADAS

```cpp
class Node;
```
Clase que creará los nodos. De elemento al nodo se le pone un array de dos long long ya que se pretende guardar un rango de numero (Ej. 12-34). Luego están los punteros izquierda y derecha que servirán para apuntar a los siguientes elementos del árbol.

```cpp
std::array<long long,2> range; 
Node *right;
Node *left;
```

Luego se crea la clase Arbol que llevará de atributos un nodo que funcionará de raíz (el primer nodo de la esctructura) y el numero de elementos que hay dentro del árbol.

```cpp
class Arbol;
```
```cpp
Node *root;
int sz;
```

En esta clase se implementa el método de inserción de elementos. 

```cpp
void insert(std::array<int,2> inputRange);
```

Este método primero mira si existe una raíz en el árbol. Si no es el caso, se coloca un nodo con el rango de elemento.

```cpp
if(root == nullptr) {
    root = new Node(inputRange);
    sz++;
}
```

Si ya existe una raíz se coloca el nodo en función de si el primer número del rangoes más pequeño o más grande que el anterior. Si es más grande se coloca a la derecha y, si es más pequeño, se coloca a la izquierda. 

```cpp
else {
    Node *aux = root;

    Node *auxRange = new Node(inputRange);

    while(aux->right != auxRange || aux->left != auxRange) {
        
        if(auxRange->range[0] <= aux->range[0] && aux->left != nullptr) {
            aux = aux->left;
        }
        
        if(auxRange->range[0] > aux->range[0] && aux->right != nullptr) {
            aux = aux->right;
        }
        
        if(auxRange->range[0] <= aux->range[0] && aux->left == nullptr) {
            aux->left = auxRange;
        }
        
        if(auxRange->range[0] > aux->range[0] && aux->right == nullptr) {
            aux->right = auxRange;
        }
    }
}
```