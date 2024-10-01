#include "pst.h"
#include "chess_types.h"

#ifndef PST_MANAGER_H
#define PST_MANAGER_H

typedef struct FastPst {
	int* most_significant;
	int* upper;
	int* lower;
	int* least_significant;
} FastPst;



class PstManager {
public:
	PstManager();
	int evaluate_piece(bitboard b, int pst_index);
private:
	void init_pst();
	void copy_pst(int* pst, int copy_index);
	int tables[12][64];
	int piece_evals[12];

	//FastPst fast_pst[12];
};
#endif
