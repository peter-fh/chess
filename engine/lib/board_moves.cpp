#include "board.h"
#include "board_types.h"
#include "prettyboard.h"
#include <bitset>
#include <iostream>


int msb_index(bitboard b){
	int position = 0;
	while (b >>= 1){
		++position;
	}
	return position;
}

bitboard msb(bitboard b){
	for (int i=63; i >= 0; --i){
		bitboard i_bit = (1ULL << i) & b;
		if (i_bit){
			return i_bit;
		}
	}
	return 0;
}

bitboard fast_lsb(bitboard b){
	return b & -b;
}

bitboard lsb(bitboard b){
	for (int i=0; i < 64; ++i){
		bitboard i_bit = (1ULL << i) & b;
		if (i_bit){
			return i_bit;
		}
	}
	return 0;
}


bitboard Board::directional_move(bitboard piece, Rays& rays, bitboard significant_func(bitboard), bitboard ray_func(Rays&, bitboard)){
	bitboard ray = ray_func(rays, piece) & ~piece;
	bitboard collision_mask = ray & all_pieces;
	bitboard closest_collision = significant_func(collision_mask);
	bitboard exclusion_mask = ray_func(rays, closest_collision);
	return ray & ~exclusion_mask;
}


bitboard Board::get_north_moves(bitboard piece){
	return directional_move(piece, rays, lsb, north);
}
bitboard Board::get_northeast_moves(bitboard piece){
	return directional_move(piece, rays, lsb, northeast);
}
bitboard Board::get_east_moves(bitboard piece){
	return directional_move(piece, rays, msb, east);
}
bitboard Board::get_southeast_moves(bitboard piece){
	return directional_move(piece, rays, msb, southeast);
}
bitboard Board::get_south_moves(bitboard piece){
	return directional_move(piece, rays, msb, south);
}
bitboard Board::get_southwest_moves(bitboard piece){
	return directional_move(piece, rays, msb, southwest);
}
bitboard Board::get_west_moves(bitboard piece){
	return directional_move(piece, rays, lsb, west);
}
bitboard Board::get_northwest_moves(bitboard piece){
	return directional_move(piece, rays, lsb, northwest);
}


bitboard Board::queen_moves(bitboard queen){
	return get_north_moves(queen) 
	| get_northeast_moves(queen) 
	| get_east_moves(queen)
	| get_southeast_moves(queen)
	| get_south_moves(queen)
	| get_southwest_moves(queen)
	| get_west_moves(queen)
	| get_northwest_moves(queen);
}

bitboard Board::bishop_moves(bitboard bishop){
	return get_northeast_moves(bishop) |
	get_southeast_moves(bishop) |
	get_southwest_moves(bishop) |
	get_northwest_moves(bishop);
}

bitboard Board::rook_moves(bitboard rook){
	return get_north_moves(rook)
	| get_east_moves(rook)
	| get_south_moves(rook)
	| get_west_moves(rook);

}

// n 0 0
// 0 0 1
// -10, E2 S1
//
// n 0
// 0 0
// 0 1
// -17, E1 S2
//
// 0 n
// 0 0
// 1 0
// -15, W1 S2
//
// 0 0 n
// 1 0 0
// -6, W2 S1
//
// 1 0 0
// 0 0 n
// 10, W2 N1
//
// 1 0
// 0 0
// 0 n
// 17, W1 N2
//
// 0 1
// 0 0
// n 0
// 15, E1 N2
//
// 0 0 1
// n 0 0
// 6, E2 N1
// 




// TODO: unit test the shit out of this





bitboard Board::knight_moves(bitboard knight){
	bitboard moves = 0ULL;
	moves |= (knight & (E2_MASK | S1_MASK)) >> 10;
	moves |= (knight & (E1_MASK | S2_MASK)) >> 17;
	moves |= (knight & (W1_MASK | S2_MASK)) >> 15;
	moves |= (knight & (W2_MASK | S1_MASK)) >> 6;
	moves |= (knight & (W2_MASK | N1_MASK)) << 10;
	moves |= (knight & (W1_MASK | N2_MASK)) << 17;
	moves |= (knight & (E1_MASK | N2_MASK)) << 15;
	moves |= (knight & (E2_MASK | N1_MASK)) << 6;
	moves &= ~all_pieces;
	return moves;
}


Moves* Board::get_moves(){
	Moves* moves = new Moves();	
	bitboard queen = pieces[Q_INDEX + piece_index_adder];
	moves->moves[Q_MINDEX].to = queen_moves(queen);
	moves->moves[Q_MINDEX].from = queen;

	bitboard rooks = pieces[R_INDEX + piece_index_adder];
	if (rooks){
		bitboard lrook = lsb(rooks);
		bitboard mrook = rooks & ~lrook;
		moves->moves[R1_MINDEX].from = lrook;
		moves->moves[R1_MINDEX].to = rook_moves(lrook);
		if (mrook){
			moves->moves[R2_MINDEX].from = mrook;
			moves->moves[R2_MINDEX].to = rook_moves(mrook);
		}
	}
	bitboard bishops = pieces[B_INDEX + piece_index_adder];
	if (bishops){
		bitboard lbishop = lsb(bishops);
		bitboard mbishop = bishops & ~lbishop;
		moves->moves[B1_MINDEX].from = lbishop;
		moves->moves[B1_MINDEX].to = bishop_moves(lbishop);
		if (mbishop){
			moves->moves[B2_MINDEX].from = mbishop;
			moves->moves[B2_MINDEX].to = bishop_moves(mbishop);
		}
		
	}
	bitboard knights = pieces[N_INDEX + piece_index_adder];
	if (knights){
		bitboard lknight = lsb(knights);
		bitboard mknight = knights & ~lknight;
		moves->moves[N1_MINDEX].from = lknight;
		moves->moves[N1_MINDEX].to = knight_moves(lknight);
		if (mknight){
			moves->moves[N2_MINDEX].from = mknight;
			moves->moves[N2_MINDEX].to = knight_moves(mknight);
		}
	}
	return moves;
}

