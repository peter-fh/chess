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


static const std::string pst_filename = "generated/pst";

class PstManager {
public:
	PstManager();
	int evaluate_piece(bitboard b, int pst_index);
	void write_psts();
	void generate_psts();
	friend bool operator==(const PstManager& a, const PstManager& b);
private:
	void read_psts();
	void generate_fast_pst(int* pst, int copy_index);
	int slow_evaluate_piece(bitboard b, int pst_index, int* pst);
	int piece_evals[12];


	FastPst fast_psts[12];
};
#endif
