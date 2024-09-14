#ifndef CHESS_TYPES_H
#define CHESS_TYPES_H

#include <stdint.h>
#include <iostream>

#define panic(msg) std::cout << "panic!\n" << msg << std::endl;exit(1);

typedef uint64_t bitboard;

int get_piece_index(int move_index, int turn);

typedef struct Move {
	bitboard to;
	bitboard from;
	int index;
	int take_index;
} Move;

std::ostream& operator<<(std::ostream& out, const Move& move);

// Index is 0-11 for move from Move array, 12 or 13 for 0 and 1 indices of castle array
typedef struct Moves {
	Move moves[12];
	bool castles[2];
	int index;
} Moves;


typedef struct {
	int turn;
	bool valid_castle[4];
	int en_passent_position;
	int halfmove;
	int fullmove;
} GameState;

std::ostream& operator<<(std::ostream& out, const Moves& moves);

#endif
