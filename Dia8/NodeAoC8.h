#ifndef NODEAOC8_H
#define NODEAOC8_H

#include <ostream>
#include <array>

class NodeAoC8 {
	public: 
		T data; // Elemento almacenado de tipo T (cualquier tipo)
		NodeAoC8<T> *next; // Puntero al siguiente nodo de la secuencia 
			       // Si no fuera puntero, habría un bucle infinito de Nodes
			       // Tengo una referencia a un objeto de la misma clase
	public:
		//Constructor
	
		NodeAoC8(T data, NodeAoC8<T> *next = nullptr) {
			this->data = data;
			this->next = next;
		}
		
		// Imprimo el data de ese nodo
		friend std::ostream& operator<<(std::ostream &out, const NodeAoC8<T> &node) {
			out << node->data;
			return out;
		}

};



#endif
