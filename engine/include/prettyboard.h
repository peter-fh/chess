#include "chess_types.h"
#include <iostream>

class Prettyboard {
	Prettyboard(bitboard b);
	friend std::ostream& operator<<(std::ostream& out, const Prettyboard& b);
private:
	bitboard b;
};
