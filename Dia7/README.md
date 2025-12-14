## DÍA 7

### TABLAS HASH
- Se ha abordado el ejercicio con tablas hash ya que se habia visto que guardando las coordenadas anteriores a un split se podia facilmente colocar el split dividido donde debe
- Es la primera alternativa que se escogió
- Se ha aprendido a usar estructuras como std::unordered_set e implementar la tabla hash

### EXPLICACIÓN FUNCIONES USADAS

```cpp
struct PairHash {};
```

Estructura para crear la tabla hash

```cpp
size_t operator()(const pair<int,int>& p) const;
```

Función que devuelve la clave de la hash a partir de los integers que se proporciona en el par. Ejemplo: pair<2, 19> saldria 2019 como clave.

```cpp
void LeerInput(const string& archivo, vector<string>& mapa);
```

Función que lee el archivo de texto que se le porporciona y coloca la información en un vector de strings

```cpp
long long contar_splits(const vector<string>& mapa);
```

Función que cuenta los splits totales en la última fila. Primero se encuentra la S ("la estrella del arbol") que determina la columna inicial donde van a iniciar los splits. En el caso de que no se enceuntre la S la función retornará 0 significando que no se pudo iniciar el conteo de splits.
```cpp
int columnaInicial = -1;

    for (int c = 0; c < C; c++) {
        if (mapa[0][c] == 'S') {
            columnaInicial = c;
            break;
        }
    }

    if (columnaInicial == -1 || L == 1) {
        return 0;
    }
```
Luego se crea un mapa hash con las posiciones en donde irán todas las posiciones posteriores a un split 
```cpp 
unordered_set<pair<int,int>, PairHash> activas;
```
Ejemplo de lo que se guardaría en activas:
```
......S.......
.....|.|......
.....|^|......   <= Guarda las posiciones de |
```
y otro map que guardará las posiciones de splitters ya visitados. Para poder diferenciar el hecho de que en una misma línea pueden haber más de un un split.
```cpp
unordered_set<pair<int,int>, PairHash> splitters_visitados;
```
Así, luego se crea un bucle que va a ir recorriendo el mapa. Aquí se crea un auxilir llamado next.
```cpp
unordered_set<pair<int,int>, PairHash> next;
```
que servirá para colocar los splits siguientes a activos, es decir,
```
......S.......
.....|.|......
.....|^|......   <= Esto es activas
.....|.|......   <= Esto es next
```

Dentro de este, se decide si hay que pasar a la siguiente linea dividiendo el split o sin dividirse por eso los dos if siguiente.

Pasa sin dividirse:
```cpp
if (celda == '.') {
        if (l + 1 < L)
            next.insert({l + 1, c});
    }
```

Pasa dividiendose:
```cpp
else if (celda == '^') {
    
    if (!splitters_visitados.count({l, c})) {
        splitters_visitados.insert({l, c});
        totalSplits++;

        int nl = l + 1;
        if (nl < L) {
            if (c - 1 >= 0){
                next.insert({nl, c - 1});
            } 
            if (c + 1 < C){
                next.insert({nl, c + 1});
                }
        }
    }
} 
```

Ya para finalizar activas pasa a ser next y se vuelve a realizar el bucle hasta que se haya llegado a la ultima linea:

```cpp
if (l >= L) continue;
```
