#include "board.h"
// TODO: fast_msb


int Board::msb_index(bitboard b){
	int position = 0;
	while (b >>= 1){
		++position;
	}
	return position;
}

int msb_index(bitboard b){
	int position = 0;
	while (b >>= 1){
		++position;
	}
	return position;
}

bitboard Board::msb(bitboard b){
	for (int i=63; i >= 0; --i){
		bitboard i_bit = (1ULL << i) & b;
		if (i_bit){
			return i_bit;
		}
	}
	return 0;
}

bitboard Board::fast_lsb(bitboard b){
	return b & -b;
}

bitboard Board::lsb(bitboard b){
	for (int i=0; i < 64; ++i){
		bitboard i_bit = (1ULL << i) & b;
		if (i_bit){
			return i_bit;
		}
	}
	return 0;
}

int Board::hamming_weight(bitboard b){
	int count = 0;
	for (int i=0; i < 64; ++i){
		if ((1ULL << i) & b){
			count++;
		}
	}
	return count;
}
