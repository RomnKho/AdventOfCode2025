#ifndef NODEAOC8_H
#define NODEAOC8_H

#include <ostream>

class NodeAoC8 {
	public:
		int coords[3]; // Coordenadas de cada junkbox
		NodeAoC8 *next; // Nodo que apunta al siguiente junkbox

	public:
		// Constructor
		NodeAoC8(int x, int y, int z, NodeAoC8 *next = nullptr) 
			: coords{x, y, z}, next(next) {}

		// Sobrecarga del operador <<
		friend std::ostream &operator<<(std::ostream &out, const NodeAoC8 &node) {
			out << "[";
			for(int i = 0; i < 3; i++) {
				out << node.coords[i];
				if(i < 2) out << ", ";
			}
			out << "]";
			return out;
		}

};



#endif
