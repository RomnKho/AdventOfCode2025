#ifndef LISTLINKEDAOC8_H
#define LISTLINKEDAOC8_H

#include <ostream>

template <typename T>
class ListLinkedAoC8 {
	private:
		NodeAoC8<T> *first; // Puntero al primero de la lista
		int sz; // Tamaño de la lista

	public:
		// Constructor
		ListLinkedAoC8() {
			first = nullptr; // No hay un primero al que apuntar
			sz = 0;
		}

		// Destructor
		~ListLinkedAoC8() {
			 while(first != nullptr) {
        			NodeAoC8<T> *aux = first;
        			first = first->next;
        			delete aux;
    				}
		}

		// Sobrecarga del operador
		friend std::ostream& operator<<(std::ostream &out, const ListLinkedAoC8<T> &list) {
			out << "[";
			// Creo un auxiliar
			NodeAoC8<T> *aux = list.first;
			// Creo un bucle que vaya pasando por todos los datos de la lista
			while(aux != nullptr) {
				out << aux->data;
				if(aux->next != nullptr) {
					out << ", ";
				}
				aux = aux->next;
			}
			out << "]";
			return out;
		}

		// Método de inserción en la lista
		void insert(int pos, T e) {
			// Manejo de posiciones
                        if(pos < 0 || pos > sz) throw std::out_of_range("Posición inválida");
			// Si lo quiero colocar primero
			if(pos == 0) {
				first = new NodeAoC8<T>(e,first);
			} else {
				// Creo un auxiliar que apunte donde el primero
				NodeAoC8<T> *aux = first;
				// Lo llevo a la posición
				for(int i = 0; i < pos-1; i++) {
					aux = aux->next;
				}
				// Aux->next apuntará al nuevo nodo que
				// apunta a su vez a donde marcaba antes aux->next
				aux->next = new Node<T>(e,aux->next);
			}
			// Incremento el tamaño
			sz++;
		}

		// Método de búsqueda dentro de la lista
		int search(T e) override {
			// Creo un auxiliar
			Node<T> *aux = first;
			int pos = 0;
			// Bucle para encontrar el elemento
			while(aux != nullptr) {
				if( e == aux->data) return pos; // Se encontró con el elemento
				aux = aux->next;
				pos++;
			}
			// No se encontró el elemento
			return -1;
		}


		int getSize() {
			return sz;
		}
};


#endif
