#ifndef TABLEENTRYAOC8_H
#define TABLEENTRYAOC8_H

#include <array>
#include <ostream>

class TableEntryAoC8 {

//	-----------------
//	| key |	x, y, z |
//	-----------------
	
	public:
		int key; // Clave numerica del circuito
		std::array<int, 3> coords; // Coordenadas de las junkbox
	
	public:
		// Constructor con parámetros
		TableEntryAoC8(int key, std::array<int, 3> &coords) {
			this->key;
			this->coords = coords;
		}	

		// Constructor sin coordenadas
		TableEntryAoC8(int key) {
			this->key = key;
			this->coords = {0, 0, 0};
		}

		// Constructor sin parámetros
		TableEntryAoC8() {
			this->key = 0;
			this->coords = {0, 0, 0};
		}

		friend bool operator==(const TableEntryAoC8 &te1, const TableEntryAoC8 &te2) {
			return (te1.key == te2.key);
		}

		friend bool operator!=(const TableEntryAoC8 &te1, const TableEntryAoC8 &te2) {
			return (te1.key != te2.key);
		}

		friend std::ostream &operator<<(std::ostream &out, const TableEntryAoC8 &te) {
			out << "["  <<te.key << " -> " << "[ ";
			for(int i = 0; i < 3; i++) {
				out << te.coords[i] << " ";				
			}
			out << " ]";

			return out;
		}
};	

#endif
