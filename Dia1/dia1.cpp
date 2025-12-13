#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    ifstream archivo("input.txt");
    string fila;
    long long num = 50, clave = 0;
    long long valor;

    if (!archivo.is_open()){
        cout << "No se ha encontrado el archivo";
        return -1;
    }
    
    while(getline(archivo, fila)){
        valor = stoi(fila.substr(1)); //Se queda con el numero de fila

        if(fila[0] == 'L'){ num -= valor; } //Si es L se resta
        else{ num += valor; } //Si es R se suma

        num = (num % 100 + 100) % 100;
        
        
        if(num == 0){ clave++; }
    }
    
    archivo.close();
    cout << "Clave: " << clave << endl;
    return 0;
}
