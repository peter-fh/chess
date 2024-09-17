#ifndef BOARD_H
#define BOARD_H
#include <string>
#include "chess_types.h"
#include "rays.h"


struct PawnMoveBoard {
	bitboard forward;
	bitboard double_forward;
	bitboard right_take;
	bitboard left_take;
};

class Board {

public:
	Board();
	Board(std::string fen);

	Moves* get_moves();
	Move* make_next_move(Moves* moves);
	void unmake_move(Move* move);
	std::string fen();

	friend std::ostream& operator<<(std::ostream& out, const Board& board);

	static std::string int_to_square(int position);
	static int square_to_int(std::string square);

	int evaluate();
	bool validate();

	friend void test_engine_takes_king();
private:
	void change_turn();
	void init_from_fen(std::string fen);
	void set_sided_bitboards();
	bitboard directional_move(bitboard piece, Rays& rays, int bit_func_type, bitboard ray_func(Rays&, bitboard));
	bitboard get_positive_move(bitboard piece, int direction);


	bitboard king_moves(bitboard king);
	bitboard queen_moves(bitboard queen);
	bitboard rook_moves(bitboard rook);
	bitboard bishop_moves(bitboard bishop);
	bitboard knight_moves(bitboard knight);
	bitboard white_pawn_moves(bitboard pawn);
	void white_pawn_moves(PawnMoveBoard& pawn_move_board, bitboard pawns);
	void black_pawn_moves(PawnMoveBoard& pawn_move_board, bitboard pawns);

	bitboard pieces[12];
	bitboard friendly_pieces;
	bitboard opposite_pieces;
	bitboard all_pieces;
	bitboard phantom_pawn;
	int piece_index_adder;
	GameState state;
	Rays rays;

	bitboard get_north_moves(bitboard piece);
	bitboard get_northeast_moves(bitboard piece);
	bitboard get_east_moves(bitboard piece);
	bitboard get_southeast_moves(bitboard piece);
	bitboard get_south_moves(bitboard piece);
	bitboard get_southwest_moves(bitboard piece);
	bitboard get_west_moves(bitboard piece);
	bitboard get_northwest_moves(bitboard piece);

	int msb_index(bitboard b);
	bitboard msb(bitboard b);
	bitboard fast_lsb(bitboard b);
	bitboard lsb(bitboard b);
	int hamming_weight(bitboard b);
	uint16_t weights[65536];
	uint16_t msb_positions[65536];

};

int msb_index(bitboard b);


#endif
