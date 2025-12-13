#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(){
    ifstream archivo("input.txt");
    string fila;
    int num = 50, clave = 0;
    int valor;

    if (!archivo.is_open()){
        cout << "No se ha encontrado el archivo";
        return -1;
    }
    
    while(getline(archivo, fila)){
        valor = stoi(fila.substr(1)); //Se queda con el numero de fila
        int num_anterior = num; // Guardamos el valor antes de la operación

        if(fila[0] == 'L'){ 
            num -= valor; 
        } 
        else{ 
            num += valor; 
        }

        int menor = min(num_anterior, num); //Te dice cual de los dos es el menor
        int mayor = max(num_anterior, num); //Te dice cual de los dos es el mayor
        
        for(int i = menor; i <= mayor; i++) {
            if(i != num_anterior && i % 100 == 0) {
                clave++;
            }
        }
        
        num = ((num % 100) + 100) % 100;
    }
    
    archivo.close();
    cout << "Clave: " << clave << endl;
    return 0;
}
