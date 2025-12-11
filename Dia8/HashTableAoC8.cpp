#ifndef HASHTABLE_H
#define HASHTABLE_H


#include <array>
#include "ListLinkedAoC8.h"
#include "TableEntryAoC8.h"

class HashTableAoC8 {
	private:
		int n; // Número de cubetas en la tabla
		int max; // Máximo de cubetas que puede tener llenas la tabla
		
		ListLinkedAoC8<TableEntryAoc8> *HashTable; // La propia tabla hash
		
		// Método que determina en que cubeta de la tabla se posiciona el elemento
		// Simplemente quiero que sea como una lista enumerada
		// Ej. 
		// Clave cubeta 0 = 0
		// Clave cubeta 1 = 1
		// ...
		// Como hay 1000 coordenadas, se crearan 1000 cubetas por si acaso
		// Es por eso que la clave será creada como %1000
		int h(int key) {
			return (key % 1000);
		}

	public:
		// Constructor
		HashTable(int size) {
			n = 0;
			max = size;
			table = new ListLinkedAoC8<TableEntryAoC8>[size];
		}

		~HashTable() {
			delete[] table;
		}

		// Inserta el par key->coords en la tabla
		void insert(std::string key, std::array<int, 3> &coords) {

			// Se le otorga una cubeta segun la clave
			cub = h(key); 
			
			// Te pone en el array de la tabla en la posicion h(key) (funcion arriba)
			table[cub].append(TableEntryAoC8(key,coords));
			n++;
		}


};


#endif

