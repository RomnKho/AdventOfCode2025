#ifndef LISTLINKEDAOC8_H
#define LISTLINKEDAOC8_H

#include <ostream>
#include "NodeAoC8.h"

class ListLinkedAoC8 {
	private: 
		NodeAoC8 *first; // Primer nodo de la lista
		int sz; // Tamaño de la lista
	
	public:
		// Constructor
		ListLinkedAoC8() {
			first = nullptr;
			sz = 0;
		}

		// Destructor
		~ListLinkedAoC8() {
			while(first != nullptr) {
				NodeAoC8 *aux = first;
				first = first->next;
				delete aux;
			}
		}

		// Método de inserción a la lista
		// El orden da igual en este caso
		void insert(int x, int y, int z) {
			// Como da igual el orden lo coloco siempre el primero y ya está
			first = new NodeAoC8(x, y, z, first);
			sz++;	
		}

		int size() {
			return sz;
		}
};


#endif
