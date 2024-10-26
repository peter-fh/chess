#include "pst_manager.h"
#include "board_types.h"
#include "prettyboard.h"


int PST_K[64] {
  -30,-40,-40,-50,-50,-40,-40,-30,
  -30,-40,-40,-50,-50,-40,-40,-30,
  -30,-40,-40,-50,-50,-40,-40,-30,
  -30,-40,-40,-50,-50,-40,-40,-30,
  -20,-30,-30,-40,-40,-30,-30,-20,
  -10,-20,-20,-20,-20,-20,-20,-10,
  20, 20,  0,  0,  0,  0, 20, 20,
  20, 30, 10,  0,  0, 10, 30, 20
};
int PST_Q[64] {
  -20,-10,-10, -5, -5,-10,-10,-20,
  -10,  0,  0,  0,  0,  0,  0,-10,
  -10,  0,  5,  5,  5,  5,  0,-10,
  -5,  0,  5,  5,  5,  5,  0, -5,
  0,  0,  5,  5,  5,  5,  0, -5,
  -10,  5,  5,  5,  5,  5,  0,-10,
  -10,  0,  5,  0,  0,  0,  0,-10,
  -20,-10,-10, -5, -5,-10,-10,-20
};
int PST_R[64] {
  0,  0,  0,  0,  0,  0,  0,  0,
  5, 10, 10, 10, 10, 10, 10,  5,
  -5,  0,  0,  0,  0,  0,  0, -5,
  -5,  0,  0,  0,  0,  0,  0, -5,
  -5,  0,  0,  0,  0,  0,  0, -5,
  -5,  0,  0,  0,  0,  0,  0, -5,
  -5,  0,  0,  0,  0,  0,  0, -5,
  0,  0,  0,  5,  5,  0,  0,  0
};
int PST_B[64] {
  -20,-10,-10,-10,-10,-10,-10,-20,
  -10,  0,  0,  0,  0,  0,  0,-10,
  -10,  0,  5, 10, 10,  5,  0,-10,
  -10,  5,  5, 10, 10,  5,  5,-10,
  -10,  0, 10, 10, 10, 10,  0,-10,
  -10, 10, 10, 10, 10, 10, 10,-10,
  -10,  5,  0,  0,  0,  0,  5,-10,
  -20,-10,-10,-10,-10,-10,-10,-20,
};
int PST_N[64] {
  -50,-40,-30,-30,-30,-30,-40,-50,
  -40,-20,  0,  0,  0,  0,-20,-40,
  -30,  0, 10, 15, 15, 10,  0,-30,
  -30,  5, 15, 20, 20, 15,  5,-30,
  -30,  0, 15, 20, 20, 15,  0,-30,
  -30,  5, 10, 15, 15, 10,  5,-30,
  -40,-20,  0,  5,  5,  0,-20,-40,
  -50,-40,-30,-30,-30,-30,-40,-50,
};
int PST_P[64] {
  0,  0,  0,  0,  0,  0,  0,  0,
  50, 50, 50, 50, 50, 50, 50, 50,
  10, 10, 20, 30, 30, 20, 10, 10,
  5,  5, 10, 25, 25, 10,  5,  5,
  0,  0,  0, 20, 20,  0,  0,  0,
  5, -5,-10,  0,  0,-10, -5,  5,
  5, 10, 10,-20,-20, 10, 10,  5,
  0,  0,  0,  0,  0,  0,  0,  0,
};

int PST_k[64] {
  20, 30, 10,  0,  0, 10, 30, 20,
  20, 20,  0,  0,  0,  0, 20, 20,
  -10,-20,-20,-20,-20,-20,-20,-10,
  -20,-30,-30,-40,-40,-30,-30,-20,
  -30,-40,-40,-50,-50,-40,-40,-30,
  -30,-40,-40,-50,-50,-40,-40,-30,
  -30,-40,-40,-50,-50,-40,-40,-30,
  -30,-40,-40,-50,-50,-40,-40,-30,
};
int PST_q[64] {
  -20,-10,-10, -5, -5,-10,-10,-20,
  -10,  0,  0,  0,  0,  0,  0,-10,
  -10,  0,  5,  5,  5,  5,  0,-10,
  -5,  0,  5,  5,  5,  5,  0, -5,
  0,  0,  5,  5,  5,  5,  0, -5,
  -10,  5,  5,  5,  5,  5,  0,-10,
  -10,  0,  5,  0,  0,  0,  0,-10,
  -20,-10,-10, -5, -5,-10,-10,-20
};
int PST_r[64] {
  0,  0,  0,  5,  5,  0,  0,  0
  -5,  0,  0,  0,  0,  0,  0, -5,
  -5,  0,  0,  0,  0,  0,  0, -5,
  -5,  0,  0,  0,  0,  0,  0, -5,
  -5,  0,  0,  0,  0,  0,  0, -5,
  -5,  0,  0,  0,  0,  0,  0, -5,
  5, 10, 10, 10, 10, 10, 10,  5,
  0,  0,  0,  0,  0,  0,  0,  0,
};
int PST_b[64] {
  -20,-10,-10,-10,-10,-10,-10,-20,
  -10,  5,  0,  0,  0,  0,  5,-10,
  -10, 10, 10, 10, 10, 10, 10,-10,
  -10,  0, 10, 10, 10, 10,  0,-10,
  -10,  5,  5, 10, 10,  5,  5,-10,
  -10,  0,  5, 10, 10,  5,  0,-10,
  -10,  0,  0,  0,  0,  0,  0,-10,
  -20,-10,-10,-10,-10,-10,-10,-20,
};
int PST_n[64] {
  -50,-40,-30,-30,-30,-30,-40,-50,
  -40,-20,  0,  5,  5,  0,-20,-40,
  -30,  5, 10, 15, 15, 10,  5,-30,
  -30,  0, 15, 20, 20, 15,  0,-30,
  -30,  5, 15, 20, 20, 15,  5,-30,
  -30,  0, 10, 15, 15, 10,  0,-30,
  -40,-20,  0,  0,  0,  0,-20,-40,
  -50,-40,-30,-30,-30,-30,-40,-50,
};
int PST_p[64] {
  0,  0,  0,  0,  0,  0,  0,  0,
  5, 10, 10,-20,-20, 10, 10,  5,
  5, -5,-10,  0,  0,-10, -5,  5,
  0,  0,  0, 20, 20,  0,  0,  0,
  5,  5, 10, 25, 25, 10,  5,  5,
  10, 10, 20, 30, 30, 20, 10, 10,
  50, 50, 50, 50, 50, 50, 50, 50,
  0,  0,  0,  0,  0,  0,  0,  0,
};

PstManager::PstManager(){
  init_pst();
}

FastPst::FastPst(){
  most_significant = new int[1 << 16];
  upper = new int[1 << 16];
  lower = new int[1 << 16];
  least_significant = new int[1 << 16];
}

FastPst::~FastPst(){
  /*
  delete most_significant;
  delete upper;
  delete lower;
  delete least_significant;
  */
}



void PstManager::init_pst(){
  piece_evals[0] = 20000;
  piece_evals[1] = 800;
  piece_evals[2] = 500;
  piece_evals[3] = 315;
  piece_evals[4] = 300;
  piece_evals[5] = 100;
  piece_evals[6] = -2000;
  piece_evals[7] = -800;
  piece_evals[8] = -500;
  piece_evals[9] = -315;
  piece_evals[10] = -300;
  piece_evals[11] = -100;

  init_fast_pst(PST_K, 0);
  init_fast_pst(PST_Q, 1);
  init_fast_pst(PST_R, 2);
  init_fast_pst(PST_B, 3);
  init_fast_pst(PST_N, 4);
  init_fast_pst(PST_P, 5);
  init_fast_pst(PST_k, 6);
  init_fast_pst(PST_q, 7);
  init_fast_pst(PST_r, 8);
  init_fast_pst(PST_b, 9);
  init_fast_pst(PST_n, 10);
  init_fast_pst(PST_p, 11);
}

bitboard pst_lsb_index(bitboard b){
  for(int i=0; i < 64; ++i){
    bitboard piece = 1ULL << i;
    if (b & piece) {
      return i;
    }
  }

  return 0;
}


int PstManager::slow_evaluate_piece(bitboard b, int pst_index, int* pst){
  int eval = 0;
  while (b){
    bitboard piece = pst_lsb_index(b);
    eval += piece_evals[pst_index];
    eval += pst[piece];
    b &= ~(1ULL << piece);
  }
  return eval;

}
void PstManager::init_fast_pst(int* pst, int piece_index){

  FastPst fast_pst = fast_psts[piece_index];

  int* most_significant = fast_pst.most_significant;
  int* upper = fast_pst.upper;
  int* lower = fast_pst.lower;
  int* least_significant = fast_pst.least_significant;
  for(bitboard i=0; i < (1 << 16); ++i) {
    most_significant[i] = slow_evaluate_piece(i << 48, piece_index, pst);
    upper[i] = slow_evaluate_piece(i << 32, piece_index, pst);
    lower[i] = slow_evaluate_piece(i << 16, piece_index, pst);
    least_significant[i] = slow_evaluate_piece(i, piece_index, pst);
  }

}

int PstManager::evaluate_piece(bitboard b, int pst_index){
  if (b == 0){
    return 0;
  }

  FastPst fast_pst = fast_psts[pst_index];

  int total = 0;
  total += fast_pst.most_significant[(b & MOST_16) >> 48];
  total += fast_pst.upper[(b & SECOND_MOST_16) >> 32];
  total += fast_pst.lower[(b & SECOND_LEAST_16) >> 16];
  total += fast_pst.least_significant[b & LEAST_16];
  return total;
}


