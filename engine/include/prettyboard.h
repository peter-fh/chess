#include "chess_types.h"
#include <iostream>
#pragma once

class Prettyboard {
public:
	Prettyboard(bitboard b);
	friend std::ostream& operator<<(std::ostream& out, const Prettyboard& b);
private:
	bitboard b;
};
