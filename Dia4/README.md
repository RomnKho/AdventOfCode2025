## DÍA 4

### GRAFOS
- Hemos elegido este problema ya que al ver lo que se necesitaba, hemos pensado que se podría integrar con grafos ya que simplemente haciamos las conexiones necesarias para decidir que casillas son las correctas.
- Observando este problema hemos visto que se podia afrontar tanto con grafos como con tablas hash, sin embargo hemos decidido resolverlo con grafos, ya que la solucion era mas sencilla.
- Se ha necesitado crear la estructura desde 0 para poder controlarla de manera más precisa.
- Se ha aprendido a utilizar funciones como assign() o push_back() y se han solidificado los conocimientos sobre grafos.

### EXPLICACIÓN CLASE Y ATRIBUTOS

```cpp
class GrafoRollos {};
```

Clase para resolver el problema del dia 4

```cpp
  vector<string> grid;
  vector<vector<int>> ids;
  vector<vector<int>> listaAdyacencia;
  int filas;
  int columnas;
  int numVertices;
  const int dir[8][2] = {
            {-1, -1}, {-1, 0}, {-1, 1},
            {0, -1},           {0, 1},
            {1, -1},  {1, 0},  {1, 1}
        };
```
Atributos de la clase GrafoRollos:
- grid: Genera un vector que guarda cada linea y a este se le puede acceder por linea y columna con grid[linea][carácter]
- ids: Genera una matriz para guardar los Ids de los rollos o indicar con -1 si no es un rollo
- listaAdyacencia: Genera una matriz que revisa las 8 celdas adyacentes al rollo
- filas: Número de filas
- columnas: Número de columnas
- numVertices: Número de rollos adyacentes a un rollo
- dir: Las 8 direcciones donde pueden estar los rollos adyacentes

### EXPLICACIÓN MÉTODOS

```cpp
GrafoRollos() : filas(0), columnas(0), numVertices(0) {}
```
Método constructor que inicializa los atributos filas, columnas y numVertices

```cpp
bool procesarArchivo(const string& nombre_archivo) {}
```
Método que carga y procesa el grafo

```cpp
bool leerGrid(const string& nombre_archivo)) {}
```
Método que lee el archivo input.txt y va guardando cada linea en el vector grid


```cpp
void asignarIDs() {}
```
Método que asigna Ids únicos a cada rollo, este primero inicializa la matriz de ids con la funcion .assign() a -1 (no hay rollo). Este método procesa cada linea y columa de tal modo qeu teniendo este input:
```
  {@    .   .   @}
  {.    @   @   .}
  {@    .   @   .}
```
La matriz Id quede asi:
```
  { 0, -1, -1,  1},  // Fila 0: rollo en (0,0)=ID0 y (0,3)=ID1
  {-1,  2,  3, -1},  // Fila 1: rollo en (1,1)=ID2 y (1,2)=ID3
  { 4, -1,  5, -1}   // Fila 2: rollo en (2,0)=ID4 y (2,2)=ID5
```

```cpp
void construirGrafo() {}
```
Método que constuye el grafo, es decir las conexiones entre los rollos y sus rollos adyacentes, esto lo hace recorriendo toda la matriz grid con:

```cpp
for (int f = 0; f < filas; f++){
  for (int c = 0; c < columnas; c++){
  }
}
```
Y en cada celda revisa las 8 casillas adyacentes:

```cpp
for (int d = 0; d < 8; d++) {
    int nfilas = f + dir[d][0];
    int ncolumnas = c + dir[d][1];
}
```
Y comprueba si algun rollo adyacente no esta conectado y lo conecta de forma mutua, es decir un rollo apunta a sus adyacentes y sus adyacentes le apuntan a él (Un grafo no dirigido).

```cpp
if (idVecino != -1 && idVecino > idActual) {
  listaAdyacencia[idActual].push_back(idVecino);
  listaAdyacencia[idVecino].push_back(idActual);
}
```

```cpp
int contarAccesibles(){}
```
Por último el método contarAcessibles cuenta cuantos rollos puede llevar la carretilla que son aquellos que tengan menos de 4 rollos adyacentes.

```cpp
for (int i = 0; i < numVertices; i++) {
  if (listaAdyacencia[i].size() < 4) {
      cont++;
  }
}
```
