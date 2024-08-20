#include "prettyboard.h"

Prettyboard::Prettyboard(bitboard b){
	this->b = b;	
}


std::ostream& operator<<(std::ostream& out, const Prettyboard& b){
	for (int i=0; i < 64; ++i){
		if (i % 8 == 0 && i != 0){
			out << "\n";
		}
		if (b.b & (1ULL << i)){
			out << "1";
		} else {
			out << "0";
		}
	}
	out << "\n";
	return out;
}
