#ifndef RAYS_H
#define RAYS_H
#include "chess_types.h"

// hash for all 64-bit binary numbers with only 1 bit using h(x)= x % N
// tested for lowest number with 0 collisions/lowest prime above 64, see commits d6ffb10 and a815263
#define N 67

class Rays {
public:
	Rays();
	bitboard north(bitboard b);
	bitboard northeast(bitboard b);
	bitboard east(bitboard b);
	bitboard southeast(bitboard b);
	bitboard south(bitboard b);
	bitboard southwest(bitboard b);
	bitboard west(bitboard b);
	bitboard northwest(bitboard b);
private:
	bitboard _north[N];
	bitboard _northeast[N];
	bitboard _east[N];
	bitboard _southeast[N];
	bitboard _south[N];
	bitboard _southwest[N];
	bitboard _west[N];
	bitboard _northwest[N];
	void zero_rays();
	void generate_rays();
	int hash(bitboard b);
};

#endif
