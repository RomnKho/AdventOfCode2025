## DÍA 5

### ÁRBOLES BINARIO DE BÚSQUEDA
- Hemos elegido este problema ya que es el único que hemos visto en el que se puede implementar esta estructura de datos sin que se complica mucho el problema
- Se ha necesitado crear desde 0 la estructura de los nodos ya que se necesitaba controlar la inserción de los rangos (cosa que no nos permite por ejemplo std::set o std::map). Así, podíamos ver, por ejemplo, el solapamiento de rangos.
- Hemos intentado implementar este problema con tablas hash pero al ver que era el único que veíamos claro hacer con árbol hemos optado hacerlo con esta estructura de datos.
- Se ha aprendido a crear un arbol desde cero, implementando métodos propios necesarios además de reforzar nuestro aprendizaje sobre los punteros, su inserción y su recorrido.

### EXPLICACIÓN FUNCIONES USADAS

```cpp
class Node;
```
Clase que creará los nodos. De elemento, al nodo se le pone un array de dos long long ya que se pretende guardar un rango de numero (Ej. 12-34). Luego están los punteros izquierda y derecha que servirán para apuntar a los siguientes elementos del árbol.

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

Si ya existe una raíz se coloca el nodo en función de si el primer número del rango es más pequeño o más grande que el anterior. Si es más grande se coloca a la derecha y, si es más pequeño, se coloca a la izquierda. 

```cpp
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
```

Luego, para evitar confusiones de rangos cuando se busca si un id está dentro de un rango, se mira si el intervalo a insertar en el árbol no contiene a otro rango ya dentro del árbol. Si este fuera el caso, se solapan los rangos.

```cpp
if(auxRange->range[0] <= aux->range[0] && auxRange->range[1] >= aux->range[1]) {
    aux->range = auxRange->range;
    break;
}
```

Para obtener el resultado del ejercicio se hace uso de una función booleana que mira si un id está dentro de un rango y devuelve true si está y false si no está.

```cpp
bool checkFreshness(long long id);
```

Para obtener el input del ejercicio se utiliza una función que lee el fichero de entrada y coloca los rangos obtenidos en un vector de 2 long long y los ids obtenidos en un vector de long long.

```cpp
void leerInput(std::string name, std::vector<std::array<long long,2>> &vRanges, std::vector<long long> &ids);
```

