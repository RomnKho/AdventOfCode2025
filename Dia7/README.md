## DÍA 7

### TABLAS HASH
- Se ha abordado el ejercicio con tablas hash ya que se habia visto que guardando las coordenadas anteriores a un split se podia facilmente colocar el plit dividido donde debe
- Es la primera alternativa que se escogió
- Se ha aprendido a usar estructuras como std::unordered_set e implementar la tabla hash

### EXPLICACIÓN FUNCIONES USADAS

```cpp
struct PairHash {};
```

Estructura para crear la tabla hash

```cpp
size_t operator()(const pair<int,int>& p) const 
```

Función que devuelve la clave de la hash a partir de los integers que se proporciona en el par. Ejemplo: pair<23, 19> saldria 2319 como clave.

```cpp
void LeerInput(const string& archivo, vector<string>& mapa)
```

Función que lee el archivo de texto que se le porporciona y coloca la información en un vector de strings

```cpp
long long contar_splits(const vector<string>& mapa)
```

Función que cuenta los splits totales en la última fila. Primero se encuentra la S (la estrella del arbol") que determina la columna inicial donde van a iniciar los splits. Luego se crea un mapa hash con las posiciones en donde irán todas las posiciones posteriores a un split (activas) 
```cpp 
unordered_set<pair<int,int>, PairHash> activas;
```
y otro map que guardará las posiciones de splitters ya visitados. Para poder diferenciar el hecho de que en una misma línea pueden haber más de un un split.
```cpp
unordered_set<pair<int,int>, PairHash> splitters_visitados;
```
Así, luego va recorriendo el mapa para verificar donde hay . para colocar | y donde hay ^ para decidir que se colocará a los lados de abajo los |. 
