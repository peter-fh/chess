#include "board.h"


int Board::evaluate(){
	int eval = 0;
	for (int i=0; i < 12; ++i){
		eval += pst_manager.evaluate_piece(pieces[i], i);
	}

	return eval;
}
