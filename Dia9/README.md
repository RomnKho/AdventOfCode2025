## **DÍA 9**

### Programación dinámica 

- Se ha escogido este problema ya que al leerlo ha saltado a la vista la forma de hacerlo
- Se ha utilizado recursividad para abordar el tema de la memoria y la programación dinámica
  y parecía el método más evidente de usar 

- Esta es la primera alternativa que se escogió

- Se ha aprendido a manejar de manera global una memoria y a manejar diferentes 
  estructuras ya implementadas en C++ como std::vector y std::array

## EXPLICACIÓN FUNCIONES USADAS 

```cpp
std::vector<std::vector<long long>> Memoria
```

    Vector de vectores que servirá de memoria para recordar las áreas calculadas
    Los términos de esta son las posiciones de las coordenadas en el vector a parte vCoords
    Así, M[0][1] por ejemplo será el area formada entre las coordenadas que se encuentran en 
    la primera posición y segunda posición en vCoords

```cpp
void inicializarMemoria(int n)
```

    Función que inicializa la memoria con el tamaño necesario

```cpp
long long calcularArea(std::vector<std::array<long long,2>> &vCoords, int i, int j)
```

    Función que calcula el area entre dos coordenadas y lo guarda en la memoria

```cpp
long long maxArea(std::vector<std::array<long long,2>> &vCoords, int ini, int fin, std::array<long long,2> coords, int i)
```

    Función que busca el área máxima que sale entre un vector de coordenadas vCoords 
    y unas coordenadas proporcionadas por el usuario (coords) 

```cpp
std::vector<std::array<long long, 2>> leer(std::string nombre)
```

    Función que lee el input que se proporciona y lo guarda en vCoords


