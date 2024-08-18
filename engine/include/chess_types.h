#ifndef CHESS_TYPES_H
#define CHESS_TYPES_H

#include <stdint.h>

#include <iostream>
#define panic(msg) std::cout << msg << std::endl;exit(1);

#define bitboard uint64_t


typedef struct {
	bitboard to;
	bitboard from;
	char type;
} Move;


#define K_MINDEX 0
#define Q_MINDEX 1
#define R1_MINDEX 2
#define R2_MINDEX 3
#define B1_MINDEX 4
#define B2_MINDEX 5
#define N1_MINDEX 6
#define N2_MINDEX 7
#define P1_MINDEX 8
#define P2_MINDEX 9

typedef struct {
	Move moves[10];
	uint8_t index;
} Moves;


#define K_INDEX 0
#define Q_INDEX 1
#define R_INDEX 2
#define B_INDEX 3
#define N_INDEX 4
#define P_INDEX 5
#define k_INDEX 6
#define q_INDEX 7
#define r_INDEX 8
#define b_INDEX 9
#define n_INDEX 10
#define p_INDEX 11

#endif
