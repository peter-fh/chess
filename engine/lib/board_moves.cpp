#include "board.h"
#include "board_types.h"
#include "prettyboard.h"
#include <bitset>
#include <iostream>



#define LSB_FUNC 0
#define MSB_FUNC 1

bitboard Board::directional_move(bitboard piece, Rays& rays, int bit_func_type, bitboard ray_func(Rays&, bitboard)){
	bitboard ray = ray_func(rays, piece) & ~piece;
	bitboard collision_mask = ray & all_pieces;
	bitboard closest_collision;
	switch (bit_func_type){
		case LSB_FUNC:
			closest_collision = fast_lsb(collision_mask);
			break;
		case MSB_FUNC:
			closest_collision = msb(collision_mask);
			break;
		default:
			panic("bit func type in directional_move is not 0 or 1")

	}
	bitboard exclusion_mask = ray_func(rays, closest_collision);
	return (ray & ~exclusion_mask) | closest_collision;
}


bitboard Board::get_north_moves(bitboard piece){
	return directional_move(piece, rays, LSB_FUNC, north);
}
bitboard Board::get_northeast_moves(bitboard piece){
	return directional_move(piece, rays, LSB_FUNC, northeast);
}
bitboard Board::get_east_moves(bitboard piece){
	return directional_move(piece, rays, MSB_FUNC, east);
}
bitboard Board::get_southeast_moves(bitboard piece){
	return directional_move(piece, rays, MSB_FUNC, southeast);
}
bitboard Board::get_south_moves(bitboard piece){
	return directional_move(piece, rays, MSB_FUNC, south);
}
bitboard Board::get_southwest_moves(bitboard piece){
	return directional_move(piece, rays, MSB_FUNC, southwest);
}
bitboard Board::get_west_moves(bitboard piece){
	return directional_move(piece, rays, LSB_FUNC, west);
}
bitboard Board::get_northwest_moves(bitboard piece){
	return directional_move(piece, rays, LSB_FUNC, northwest);
}


bitboard Board::queen_moves(bitboard queen){
	bitboard queen_move_board = 
	get_north_moves(queen) 
	| get_northeast_moves(queen) 
	| get_east_moves(queen)
	| get_southeast_moves(queen)
	| get_south_moves(queen)
	| get_southwest_moves(queen)
	| get_west_moves(queen)
	| get_northwest_moves(queen);

	return queen_move_board &~ friendly_pieces;
}

bitboard Board::bishop_moves(bitboard bishop){
	bitboard bishop_move_board = 
	get_northeast_moves(bishop) |
	get_southeast_moves(bishop) |
	get_southwest_moves(bishop) |
	get_northwest_moves(bishop);
	return bishop_move_board &~ friendly_pieces;
}

bitboard Board::rook_moves(bitboard rook){
	bitboard rook_move_board = 
		get_north_moves(rook)
		| get_east_moves(rook)
		| get_south_moves(rook)
		| get_west_moves(rook);
	return rook_move_board &~ friendly_pieces;

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



bitboard Board::knight_moves(bitboard knight){
	bitboard moves = 0ULL;
	moves |= (knight & (E2_MASK & S1_MASK)) >> 10;
	moves |= (knight & (E1_MASK & S2_MASK)) >> 17;
	moves |= (knight & (W1_MASK & S2_MASK)) >> 15;
	moves |= (knight & (W2_MASK & S1_MASK)) >> 6;
	moves |= (knight & (W2_MASK & N1_MASK)) << 10;
	moves |= (knight & (W1_MASK & N2_MASK)) << 17;
	moves |= (knight & (E1_MASK & N2_MASK)) << 15;
	moves |= (knight & (E2_MASK & N1_MASK)) << 6;
	moves &= ~friendly_pieces;
	return moves;
}

bitboard Board::king_moves(bitboard king){
	bitboard king_moves = 0ULL;
	king_moves |= (king & N1_MASK) << 8;
	king_moves |= (king & (N1_MASK & E1_MASK)) << 7;
	king_moves |= (king & E1_MASK) >> 1;
	king_moves |= (king & (S1_MASK & E1_MASK)) >> 9;
	king_moves |= (king & S1_MASK) >> 8;
	king_moves |= (king & (S1_MASK & W1_MASK)) >> 7;
	king_moves |= (king & W1_MASK) << 1;
	king_moves |= (king & (N1_MASK & W1_MASK)) << 9;
	return king_moves &~ friendly_pieces;
}




void Board::white_pawn_moves(PawnMoveBoard& pawn_move_board, bitboard pawns){
	pawn_move_board.forward = pawns << 8;
	pawn_move_board.forward &= ~all_pieces;
	pawn_move_board.double_forward = ((pawns & W_UNMOVED_PAWN_MASK) &~ (all_pieces >> 8)) << 16;
	pawn_move_board.double_forward &= ~all_pieces;
	pawn_move_board.right_take = (pawns & E1_MASK) << 7;
	pawn_move_board.right_take &= opposite_pieces | phantom_pawn;
	pawn_move_board.left_take = (pawns & W1_MASK) << 9;
	pawn_move_board.left_take &= opposite_pieces | phantom_pawn;
}

void Board::black_pawn_moves(PawnMoveBoard& pawn_move_board, bitboard pawns){
	pawn_move_board.forward = pawns >> 8;
	pawn_move_board.forward &= ~all_pieces;
	pawn_move_board.double_forward = ((pawns & B_UNMOVED_PAWN_MASK) &~ (all_pieces << 8)) >> 16;
	pawn_move_board.double_forward &= ~all_pieces;
	pawn_move_board.right_take = (pawns & E1_MASK) >> 9;
	pawn_move_board.right_take &= opposite_pieces | phantom_pawn;
	pawn_move_board.left_take = (pawns & W1_MASK) >> 7;
	pawn_move_board.left_take &= opposite_pieces | phantom_pawn;
}



Moves* Board::get_moves(){
	/*std::cout << "Piece index adder: " << piece_index_adder << "\n";*/
	Moves* moves = new Moves();	
	moves->index = 0;
	bitboard queen = pieces[Q_INDEX + piece_index_adder];
	moves->moves[Q_MINDEX].to = queen_moves(queen);
	moves->moves[Q_MINDEX].from = queen;

	bitboard king = pieces[K_INDEX + piece_index_adder];
	moves->moves[K_MINDEX].to = king_moves(king);
	moves->moves[K_MINDEX].from = king;

	bitboard rooks = pieces[R_INDEX + piece_index_adder];
	if (rooks){
		bitboard lrook = fast_lsb(rooks);
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
		bitboard lbishop = fast_lsb(bishops);
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
		bitboard lknight = fast_lsb(knights);
		bitboard mknight = knights & ~lknight;
		moves->moves[N1_MINDEX].from = lknight;
		moves->moves[N1_MINDEX].to = knight_moves(lknight);
		if (mknight){
			moves->moves[N2_MINDEX].from = mknight;
			moves->moves[N2_MINDEX].to = knight_moves(mknight);
		}
	}

	bitboard pawns = pieces[P_INDEX + piece_index_adder];
	if (pawns){
		PawnMoveBoard pawn_moves;
		if (state.turn == WHITE){
			white_pawn_moves(pawn_moves, pawns);
		} else if (state.turn == BLACK){
			black_pawn_moves(pawn_moves, pawns);
		} else {
			panic("State turn is neither black nor white")
		}

		moves->moves[PF_MINDEX].to= pawn_moves.forward;
		moves->moves[PF_MINDEX].from = 0ULL;
		moves->moves[PDF_MINDEX].to = pawn_moves.double_forward;
		moves->moves[PDF_MINDEX].from = 0ULL;
		moves->moves[PRT_MINDEX].to = pawn_moves.right_take;
		moves->moves[PRT_MINDEX].from = 0ULL;
		moves->moves[PLT_MINDEX].to = pawn_moves.left_take;
		moves->moves[PLT_MINDEX].from = 0ULL;
	}
	if (state.turn == WHITE){
		if (state.valid_castle[K_CASTLE_INDEX] && (all_pieces & K_CASTLE_MASK) == 0){
			moves->castles[K_CASTLE_INDEX] = true;
		} else {
			moves->castles[K_CASTLE_INDEX] = false;
		}
		if (state.valid_castle[Q_CASTLE_INDEX] && (all_pieces & Q_CASTLE_MASK) == 0){
			moves->castles[Q_CASTLE_INDEX] = true;
		} else {
			moves->castles[Q_CASTLE_INDEX] = false;
		}

	}
	else if (state.turn == BLACK){
		if (state.valid_castle[k_CASTLE_INDEX] && (all_pieces & k_CASTLE_MASK) == 0){
			moves->castles[K_CASTLE_INDEX] = true;
		} else {
			moves->castles[K_CASTLE_INDEX] = false;

		}
		if (state.valid_castle[q_CASTLE_INDEX] && (all_pieces & q_CASTLE_MASK) == 0){
			moves->castles[Q_CASTLE_INDEX] = true;
		} else {
			moves->castles[Q_CASTLE_INDEX] = false;
		}
	}

	return moves;
}


inline void white_kingside_castle(bitboard& king, bitboard& rooks){
	king = 0x2;
	rooks &= ~0x1;
	rooks |= 0x4;
}

inline void white_kingside_uncastle(bitboard& king, bitboard& rooks){
	king = 0x8;
	rooks &= ~0x4;
	rooks |= 0x1;
}


inline void white_queenside_castle(bitboard& king, bitboard& rooks){
	king = 0x20;
	rooks &= ~0x80;
	rooks |= 0x10;
}

inline void white_queenside_uncastle(bitboard& king, bitboard& rooks){
	king = 0x8;
	rooks &= ~0x10;
	rooks |= 0x80;
}


inline void black_kingside_castle(bitboard& king, bitboard& rooks){
	king = 0x200000000000000;
	rooks &= ~0x100000000000000;
	rooks |= 0x400000000000000;
}

inline void black_kingside_uncastle(bitboard& king, bitboard& rooks){
	king = 0x800000000000000;
	rooks &= ~0x400000000000000;
	rooks |= 0x100000000000000;
}


inline void black_queenside_castle(bitboard& king, bitboard& rooks){
	king = 0x2000000000000000;
	rooks &= ~0x8000000000000000;
	rooks |= 0x1000000000000000;
}

inline void black_queenside_uncastle(bitboard& king, bitboard& rooks){
	king = 0x800000000000000;
	rooks &= ~0x1000000000000000;
	rooks |= 0x8000000000000000;
}


int get_piece_index(int move_index, int turn){
	int piece_index;
	switch (move_index){
		case 0:
			piece_index = 0;
			break;
		case 1:
			piece_index = 1;
			break;
		case 2:
			piece_index = 2;
			break;
		case 3:
			piece_index = 2;
			break;
		case 4:
			piece_index = 3;
			break;
		case 5:
			piece_index = 3;
			break;
		case 6:
			piece_index = 4;
			break;
		case 7:
			piece_index = 4;
			break;
		case 8:
			piece_index = 5;
			break;
		case 9:
			piece_index = 5;
			break;
		case 10:
			piece_index = 5;
			break;
		case 11:
			piece_index = 5;
			break;
		default:
			panic("move index in make_next_move cannot be converted to piece index")
	}
	
	if (turn == BLACK){
		piece_index += 6;
	} 
	return piece_index;
}

bitboard get_pawn_from(bitboard to, int index, int turn){
	if (turn == WHITE){
		switch (index){
			case PF_MINDEX:
				return (to >> 8);
			break;	
			case PDF_MINDEX:
				return (to >> 16);
			break;
			case PRT_MINDEX:
				return (to >> 7);
			break;
			case PLT_MINDEX:
				return (to >> 9);
			break;
			default:
				panic("Calling get_pawn_from with index that isn't a pawn move index") 


		}
	} else {
		switch (index){
			case PF_MINDEX:
				return (to << 8);
			break;	
			case PDF_MINDEX:
				return (to << 16);
			break;
			case PRT_MINDEX:
				return (to << 9);
			break;
			case PLT_MINDEX:
				return (to << 7);
			break;
			default:
				panic("Calling get_pawn_from with index that isn't a pawn move index") 
		}
	}
}


Move* Board::make_next_move(Moves* moves){
	set_sided_bitboards();
	/*std::cout << "Turn while making move: " << state.turn << "\n";*/
	Move* return_move = new Move;
	while (moves->index < 12 && moves->moves[moves->index].to == 0){
		moves->index++;
	}
	/*std::cout << "Moves index: " << moves->index << "\n";*/

	int index = moves->index;
	if (index < 12){
		int piece_index = get_piece_index(index, state.turn);
		bitboard to = fast_lsb(moves->moves[index].to);
		moves->moves[index].to &= ~to;
		bitboard from;

		if (index < 8){
			from = moves->moves[index].from;
		} else {
			from = get_pawn_from(to, index, state.turn);
		}
		/*std::cout << "Piece index: " << piece_index << "\n";*/
		/*std::cout << "From: " << Board::int_to_square(msb_index(from)) << "\n";*/
		/*std::cout << "To: " << Board::int_to_square(msb_index(to)) << "\n";*/

		pieces[piece_index] &= ~from;
		pieces[piece_index] |= to;

		bool taking_move = false;
		if (to & opposite_pieces){
			for (int i=6-piece_index_adder; i < 12-piece_index_adder; ++i){
				if (pieces[i] & to){
					pieces[i] &= ~to;
					return_move->take_index = i;
					taking_move = true;
				}
			}
			if (!taking_move){
				panic("Taking move but take_index is not set!")
			}
		} else {
			return_move->take_index = -1;
		}

		return_move->to = to;
		return_move->from = from;
		return_move->index = index;
		change_turn();
	} else if (index == 13 && moves->castles[0]){
		if (state.turn == WHITE){
			white_kingside_castle(pieces[K_INDEX], pieces[R_INDEX]);
		} else {
			black_kingside_castle(pieces[k_INDEX], pieces[r_INDEX]);
		}
		return_move->to = 0ULL;
		return_move->from = 0ULL;
		return_move->index = OO_INDEX;
		moves->index++;
		change_turn();
	} else if (index == 14 && moves->castles[1]){
		if (state.turn == WHITE){
			white_queenside_castle(pieces[K_INDEX], pieces[R_INDEX]);
		} else {
			black_queenside_castle(pieces[k_INDEX], pieces[r_INDEX]);
		}
		return_move->to = 0ULL;
		return_move->from = 0ULL;
		return_move->index = OOO_INDEX;
		moves->index++;
		change_turn();
	} else {
		/*std::cout << "index: " << index << "\n";*/
		moves->index = -1;
		return_move->to = 0ULL;
		return_move->from = 0ULL;
		return_move->index = -1;
	}

	return return_move;
}


void Board::unmake_move(Move* move){
	set_sided_bitboards();

	// [DEBUG] assert correct number of pawns
	/*if (hamming_weight(pieces[11]) > 8){*/
	/*	panic("Too many black pawns!")*/
	/*}*/

	if (move->index == -1){
		return;
	}

	change_turn();
	/*std::cout << "Turn while unmaking move: " << state.turn << "\n";*/
	if (move->index < 12){
		int piece_index = get_piece_index(move->index, state.turn);
		bitboard to = move->to;
		bitboard from = move->from;
		pieces[piece_index] &= ~to;
		pieces[piece_index] |= from;
		if (move->take_index != -1){
			/*std::cout << "Undoing taking move" << "\n";*/
			int take_index = move->take_index;
			pieces[take_index] |= to;
		}
	} else if (move->index == OO_INDEX){
		if (state.turn == WHITE){
			white_kingside_uncastle(pieces[K_INDEX], pieces[R_INDEX]);
		}
		else {
			black_kingside_uncastle(pieces[k_INDEX], pieces[r_INDEX]);
		}
	} else if (move->index == OOO_INDEX){
		if (state.turn == WHITE){
			white_queenside_uncastle(pieces[K_INDEX], pieces[R_INDEX]);
		}
		else {
			black_queenside_uncastle(pieces[k_INDEX], pieces[r_INDEX]);
		}
	} else {
		panic("Move in unmake_move() has index that is not -1 and not [0,14]")
	}

}

