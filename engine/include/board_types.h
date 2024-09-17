#include "board.h"

#pragma once

#define K_MINDEX 0
#define Q_MINDEX 1
#define R1_MINDEX 2
#define R2_MINDEX 3
#define B1_MINDEX 4
#define B2_MINDEX 5
#define N1_MINDEX 6
#define N2_MINDEX 7
// forward
#define PF_MINDEX 10
// double forward
#define PDF_MINDEX 11
// right take
#define PRT_MINDEX 8
// left take
#define PLT_MINDEX 9

static std::unordered_map<int, char> move_piece_map = {
	{K_MINDEX, 'K'},
	{Q_MINDEX, 'Q'},
	{R1_MINDEX, 'R'},
	{R2_MINDEX, 'R'},
	{B1_MINDEX, 'B'},
	{B2_MINDEX, 'B'},
	{N1_MINDEX, 'N'},
	{N2_MINDEX, 'N'},
	{PF_MINDEX, 'P'},
	{PDF_MINDEX, 'P'},
	{PRT_MINDEX, 'P'},
	{PLT_MINDEX, 'P'},
};


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
// o-o (kingside castle)
#define OO_INDEX 12
// o-o-o (queenside castle)
#define OOO_INDEX 13

// 00000001
// 11111110
// FC
// 7F
// 00111111
// 3F
// 80
// 00000001
#define W1_MASK			0x7F7F7F7F7F7F7F7F
#define W2_MASK			0x3F3F3F3F3F3F3F3F
#define E1_MASK			0xFEFEFEFEFEFEFEFE
#define E2_MASK			0xFCFCFCFCFCFCFCFC
#define N1_MASK			0x00FFFFFFFFFFFFFF
#define N2_MASK			0x0000FFFFFFFFFFFF
#define S1_MASK			0xFFFFFFFFFFFFFF00
#define S2_MASK			0xFFFFFFFFFFFF0000

#define W_UNMOVED_PAWN_MASK	0x000000000000FF00
#define B_UNMOVED_PAWN_MASK	0x00FF000000000000

#define K_CASTLE_INDEX 0
#define Q_CASTLE_INDEX 1
#define k_CASTLE_INDEX 2
#define q_CASTLE_INDEX 3

#define K_CASTLE_MASK		0x0000000000000006
#define Q_CASTLE_MASK		0x0000000000000070
#define k_CASTLE_MASK		0x0600000000000000
#define q_CASTLE_MASK		0x7000000000000000

#define WHITE 0
#define BLACK 1
static char turn_characters[2] = {'w', 'b'};


static std::unordered_map<int, char> piece_map = {
	{K_INDEX, 'K'},
	{Q_INDEX, 'Q'},
	{R_INDEX, 'R'},
	{B_INDEX, 'B'},
	{N_INDEX, 'N'},
	{P_INDEX, 'P'},
	{k_INDEX, 'k'},
	{q_INDEX, 'q'},
	{r_INDEX, 'r'},
	{b_INDEX, 'b'},
	{n_INDEX, 'n'},
	{p_INDEX, 'p'}
};


static std::unordered_map<char, int> index_map = {
	{'K', K_INDEX},
	{'Q', Q_INDEX},
	{'R', R_INDEX},
	{'B', B_INDEX},
	{'N', N_INDEX},
	{'P', P_INDEX},
	{'k', k_INDEX},
	{'q', q_INDEX},
	{'r', r_INDEX},
	{'b', b_INDEX},
	{'n', n_INDEX},
	{'p', p_INDEX}
};


static char castle_characters[4] = {'K', 'Q', 'k', 'q'};
