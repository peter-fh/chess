#ifndef BOARD_H
#define BOARD_H
#include <string>
#include "chess_types.h"



class Board {

public:
	Board();
	Board(std::string fen);

	/*
	~Board();
	Board(const Board& board);
	Board& operator=(const Board& other);
	*/

	Moves* get_moves();
	void make_next_move(Moves* moves);
	std::string fen();

	friend std::ostream& operator<<(std::ostream& out, const Board& board);

private:
	void init_from_fen(std::string fen);

	bitboard pieces[12];
};

#endif
