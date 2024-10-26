#include "pst.h"
#include "chess_types.h"

#ifndef PST_MANAGER_H
#define PST_MANAGER_H

typedef struct FastPst {
	int* most_significant;
	int* upper;
	int* lower;
	int* least_significant;
	FastPst();
	~FastPst();
} FastPst;



class PstManager {
public:
	PstManager();
	int evaluate_piece(bitboard b, int pst_index);
private:
	void init_pst();
	void init_fast_pst(int* pst, int copy_index);
	int slow_evaluate_piece(bitboard b, int pst_index, int* pst);
	int piece_evals[12];


	FastPst fast_psts[12];
};
#endif
