#include "board.h"
#include "board_types.h"


int Board::evaluate(){
	int eval = 0;
	eval += hamming_weight(pieces[K_INDEX]) * 2000;
	eval += hamming_weight(pieces[Q_INDEX]) * 800;
	eval += hamming_weight(pieces[R_INDEX]) * 500;
	eval += hamming_weight(pieces[B_INDEX]) * 315;
	eval += hamming_weight(pieces[N_INDEX]) * 300;
	eval += hamming_weight(pieces[P_INDEX]) * 100;
	eval -= hamming_weight(pieces[k_INDEX]) * 2000;
	eval -= hamming_weight(pieces[q_INDEX]) * 800;
	eval -= hamming_weight(pieces[r_INDEX]) * 500;
	eval -= hamming_weight(pieces[b_INDEX]) * 315;
	eval -= hamming_weight(pieces[n_INDEX]) * 300;
	eval -= hamming_weight(pieces[p_INDEX]) * 100;

	return eval;
}
