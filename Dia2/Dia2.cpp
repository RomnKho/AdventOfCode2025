#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

bool mitades(int n){
    string num = to_string(n);
    int tam=num.length();
    //Si el tamaño es impar no puede tener mitades
    if(tam%2!=0){
        return false;
    }

    int mitad=tam/2;

    //Comparar ambas mitades
    return num.substr(0,mitad)==num.substr(mitad);
}

int Sumas(int min,int max){
    int suma=0;
    for(int i=min;i<=max;i++){
         if(mitades(i)){
            suma+=i;
         }
    }
    return suma;
}


void leer(string nombre){
    string rango;
    ifstream archivo (nombre);
    int resultado=0,suma_rango=0;

    if (!archivo.is_open()){
        cout << "No se ha encontrado el archivo";
    }

    while(getline(archivo, rango,',')){  //Separa cada rango por comas 11-23,10-90 -> 11-23
        int pos=rango.find('-'); //Te da la posición del guión
        int min=stoi(rango.substr(0,pos)); //Tiene el primer numero desde el guion
        int max=stoi(rango.substr(pos+1)); //Tiene el ultimo numero desde el guion
        suma_rango=Sumas(min,max);
        resultado+=suma_rango;
    }
    cout<<resultado<<endl;
}

int main(){
    leer("input.txt");

    return 0;
}
