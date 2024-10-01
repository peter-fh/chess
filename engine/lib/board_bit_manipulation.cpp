#include "board_types.h"
#include "board.h"
#include "prettyboard.h"
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
		bitboard i_bit = (1ull << i) & b;
		if (i_bit){
			return i_bit;
		}
	}
	return 0;
}

bitboard Board::slow_msb(bitboard b){
	bitboard position = msbs[(b & MOST_16) >> 48];
	if (position){
		return position << 48;
	}
	position = msbs[(b & SECOND_MOST_16) >> 32];
	if (position){
		return position <<  32;
	}
	position = msbs[(b & SECOND_LEAST_16) >> 16];
	if (position){
		return position <<  16;
	}
	position = msbs[b & LEAST_16];
	if (position){
		return position;
	}
	return 0;
}


bitboard Board::lsb(bitboard b){
	return b & -b;
}

bitboard Board::slow_lsb(bitboard b){
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
	/*
	for (int i=0; i < 64; ++i){
		if ((1ULL << i) & b){
			count++;
		}
	}
      */
	//return 0;
	count += weights[b & LEAST_16];
	count += weights[(b & SECOND_LEAST_16) >> 16];
	count += weights[(b & SECOND_MOST_16) >> 32];
	count += weights[(b & MOST_16) >> 48];
	return count;
}
int Board::slow_hamming_weight(bitboard b){
	int count = 0;
	for (int i=0; i < 64; ++i){
		if ((1ULL << i) & b){
			count++;
		}
	}
	return count;
}
