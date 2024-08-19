#ifndef BOARD_H
#define BOARD_H
#include <string>
#include "chess_types.h"



class Board {

public:
	Board();
	Board(std::string fen);

	Moves* get_moves();
	void make_next_move(Moves* moves);
	std::string fen();

	friend std::ostream& operator<<(std::ostream& out, const Board& board);

	static std::string int_to_square(int position);
	static int square_to_int(std::string square);
private:
	void init_from_fen(std::string fen);

	bitboard pieces[12];
	GameState state;

};

#endif
