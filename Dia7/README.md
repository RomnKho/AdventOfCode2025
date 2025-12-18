## DÍA 7

### TABLAS HASH
- Hemos elegido este ejercicio ya que entre todas las posibilidades, este es el que vimos más claro para implementar una tabla hash.
- Se ha abordado el ejercicio con tablas hash ya que se habia visto que guardando las coordenadas anteriores a un split se podia facilmente colocar el split dividido donde debe.
- Es la primera alternativa que se escogió.
- Se ha aprendido a implementar de 0 una tabla hash además de implementar sus propios métodos.

### EXPLICACIÓN FUNCIONES USADAS

```cpp
struct Entrada {
    int l, c;
    bool ocupado = false;
};
```

Estructura que irá como elemento de la hash. 'Entrada' contiene a:
- l: linea
- c: columna
- ocupado: booleano que mira si hay algo en la celda

```cpp
class TablaHash; 
```

Clase que añade la tabla hash como tal. Esta tendrá los siguientes atributos:

```cpp
int tam;
vector<Entrada> tabla;
```

La explicación es la siguiente:
- tam: tamaño de la tabla hash
- tabla: vector de entrada que irá almacenando todas las coordenadas de los splits

Dentro de la clase se implementan diferentes métodos como el constructor.

```cpp
TablaHash(int n) : tam(n), tabla(n) {}
```

Luego, se ha añadido el método de inserción.

```cpp
bool insert(int l, int c);
```
En el se creará la clave de la hash a partir de los integers que se proporciona en la cabecera. Ejemplo: hash.insert(2,19) tendría 2019 como clave.

```cpp
int indice = ((unsigned long long)l * 1000 + c) % tam;
```

Si por alguna casualidad, dos entradas tuvieran la misma clave se intentará recolocar la entrada a insertar en otra cubeta. Además, mira si una posición ya se ha insertado antes.

```cpp
while (tabla[indice].ocupado) {

    if (tabla[indice].l == l && tabla[indice].c == c) return false;
    
    indice = (indice + 1) % tam; 
}

tabla[indice].l = l;
tabla[indice].c = c;
tabla[indice].ocupado = true;
```

La función devolverá `true` si se ha realizado con éxito la inserción o `false` si no se ha podido hacer.

Como última método de la clase se ha añadido una función que limpia la tabla hash para que pueda ser reutilizada.

```cpp
void limpiar() {
    for(int i = 0; i < tam; i++){
        
    tabla[i].ocupado = false;
    }
}
```

Por último se implementa la siguiente función que resuelve el problema:

```cpp
long long contar_splits(const vector<string>& mapa);
```

Esta es una función que cuenta los splits totales en la última fila. Primero se determina el tamaño del tablero que se da en el input. Luego se encuentra la S ("la estrella del arbol") que determina la columna inicial donde van a iniciar los splits. En el caso de que no se encuentre la S la función retornará 0 significando que no se pudo iniciar el conteo de splits.

```cpp
int L = mapa.size();
int C = mapa[0].size();

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

Luego se crea un mapa hash con las posiciones en donde irán todas las posiciones posteriores a un split. Se cre con el doble de tamaño del tablero para que siempre hayan huecos libres.

```cpp 
int tam = (L * C * 2);
TablaHash activas(tam);
```

Ejemplo de lo que se guardaría en activas:

```
......S.......
......|.......
.....|^|......   <= Guarda las posiciones de |
```

y otro mapa que guardará las posiciones de splitters ya visitados. Para poder diferenciar el hecho de que en una misma línea pueden haber más de un un split.

```cpp
TablaHash splitters_visitados(tam);
```

Así, luego se crea un bucle que va a ir recorriendo el mapa. Aquí se crea un auxiliar llamado next.

```cpp
TablaHash next(tam);
```

que servirá para colocar los splits siguientes a activos, es decir,

```
......S.......
......|.......
.....|^|......   <= Esto es activas
.....|.|......   <= Esto es next
```

Dentro de este, se decide si hay que pasar a la siguiente linea dividiendo el split o sin dividirse por eso los dos if siguiente.

Pasa sin dividirse:
```cpp
// CASO 1: Es un camino libre (.)
if (celda == '.') {
// Simplemente intentamos avanzar a la fila de abajo
    if (filaActual + 1 < L) {
        if (next.insert(filaActual + 1, colActual)) {
        nuevasEncontradas = true;
        }
    }
}
```

Pasa dividiendose:
```cpp
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
```

Ya para finalizar activas pasa a ser next y se vuelve a realizar el bucle hasta que se haya llegado a la ultima linea:

```cpp
if (filaActual >= L) continue;
```

Devuelve el numero de splits en la última fila

```cpp
return totalSplits;
```
