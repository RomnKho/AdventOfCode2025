#ifndef LISTLINKEDAOC8_H
#define LISTLINKEDAOC8_H

#include <ostream>

template <typename T>
class ListLinkedAoC8 {
	private:
		Node<T> *first; // Puntero al primero de la lista
		int sz; // Tamaño de la lista

	public:
		// Constructor
		ListLinked() {
			first = nullptr; // No hay un primero al que apuntar
			sz = 0;
		}

		// Destructor
		~ListLinked() {
			 while(first != nullptr) {
        			Node<T> *aux = first;
        			first = first->next;
        			delete aux;
    				}
		}

		friend std::ostream& operator<<(std::ostream &out, const ListLinked<T> &list) {
			out << "[";
			// Creo un auxiliar
			Node<T> *aux = list.first;
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

		void insert(int pos, T e) {
			// Manejo de posiciones
                        if(pos < 0 || pos > sz) throw std::out_of_range("Posición inválida");
			// Si lo quiero colocar primero
			if(pos == 0) {
				first = new Node<T>(e,first);
			} else {
				// Creo un auxiliar que apunte donde el primero
				Node<T> *aux = first;
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

		int getSize() {
			return sz;
		}
};


#endif
