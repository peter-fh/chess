#ifndef CHESS_TYPES_H
#define CHESS_TYPES_H

#include <stdint.h>

#define panic(msg) std::cout << msg << std::endl;exit(1);

#define bitboard uint64_t


typedef struct {
	bitboard to;
	bitboard from;
	char type;
} Move;



typedef struct {
	Move moves[10];
	uint8_t index;
} Moves;


typedef struct {
	int turn;
	bool valid_castle[4];
	int en_passent_position;
	int halfmove;
	int fullmove;
} GameState;


#endif
