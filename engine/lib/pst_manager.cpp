#include "pst_manager.h"
#include "board_types.h"
#include "prettyboard.h"
#include <iostream>
#include <fstream>


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
  read_psts();
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


void PstManager::read_psts() {
  std::ifstream pst_file;
  pst_file.open(pst_filename);
  for (int pst=0; pst < 12; ++pst){
    std::string array_string;
    std::string array_value_string;
    FastPst fast_pst = fast_psts[pst];
    for (int i=0; i < 65536; ++i){
      pst_file >> array_value_string;
      //std::cout << "Most significant at index " << i << ": " << array_value_string << "\n";
      fast_pst.most_significant[i] = std::stoi(array_value_string);
    }
    pst_file >> array_string;
    if (array_string != "ARR_END"){
      std::cout << "Not reading ARR_END\n";
    }
    for (int i=0; i < 65536; ++i){
      pst_file >> array_value_string;
      fast_pst.upper[i] = std::stoi(array_value_string);
    }
    pst_file >> array_string;
    if (array_string != "ARR_END"){
      std::cout << "Not reading ARR_END\n";
    }
    for (int i=0; i < 65536; ++i){
      pst_file >> array_value_string;
      fast_pst.lower[i] = std::stoi(array_value_string);
    }
    pst_file >> array_string;
    if (array_string != "ARR_END"){
      std::cout << "Not reading ARR_END\n";
    }
    for (int i=0; i < 65536; ++i){
      pst_file >> array_value_string;
      fast_pst.least_significant[i] = std::stoi(array_value_string);
    }
    pst_file >> array_string;
    if (array_string != "ARR_END"){
      std::cout << "Not reading ARR_END\n";
    }
    pst_file >> array_string;
    if (array_string != "PST_END"){
      std::cout << "Not reading PST_END\n";
    }


  }
}

void PstManager::write_psts(){
  std::ofstream pst_file;
  pst_file.open(pst_filename);
  for (int pst=0; pst < 12; ++pst){
    FastPst fast_pst = fast_psts[pst];

    for (int i=0; i < 65536; ++i){
      pst_file << fast_pst.most_significant[i] << "\n";
    }
    pst_file << "ARR_END\n";

    for (int i=0; i < 65536; ++i){
      pst_file << fast_pst.upper[i] << "\n";
    }
    pst_file << "ARR_END\n";

    for (int i=0; i < 65536; ++i){
      pst_file << fast_pst.lower[i] << "\n";
    }
    pst_file << "ARR_END\n";

    for (int i=0; i < 65536; ++i){
      pst_file << fast_pst.least_significant[i] << "\n";
    }
    pst_file << "ARR_END\n";
    pst_file << "PST_END\n";

  }

}


bool operator==(const PstManager& a, const PstManager& b){
  int line = 0;
  for (int pst=0; pst < 12; ++pst){
    FastPst fast_pst_a = a.fast_psts[pst];
    FastPst fast_pst_b = b.fast_psts[pst];

    for (int i=0; i < 65536; ++i){
      line++;
      if (fast_pst_a.most_significant[i] != fast_pst_b.most_significant[i]){
        std::cout << "Error in most significant on line " << line << "\n";
        std::cout << "A: " << fast_pst_a.most_significant[i] << "\n";
        std::cout << "B: " << fast_pst_b.most_significant[i] << "\n";
        return false;
      }
      if (fast_pst_a.upper[i] != fast_pst_b.upper[i]){
        std::cout << "Error in upper on line " << line << "\n";
        std::cout << "A: " << fast_pst_a.upper[i] << "\n";
        std::cout << "B: " << fast_pst_b.upper[i] << "\n";
        return false;
      }
      if (fast_pst_a.lower[i] != fast_pst_b.lower[i]){
        std::cout << "Error in lower on line " << line << "\n";
        std::cout << "A: " << fast_pst_a.lower[i] << "\n";
        std::cout << "B: " << fast_pst_b.lower[i] << "\n";
        return false;
      }
      if (fast_pst_a.least_significant[i] != fast_pst_b.least_significant[i]){
        std::cout << "Error in least significant on line " << line << "\n";
        std::cout << "A: " << fast_pst_a.least_significant[i] << "\n";
        std::cout << "B: " << fast_pst_b.least_significant[i] << "\n";
        return false;
      }
    }
  }
  return true;
}

void PstManager::generate_psts(){
  piece_evals[0] = 20000;
  piece_evals[1] = 800;
  piece_evals[2] = 500;
  piece_evals[3] = 315;
  piece_evals[4] = 300;
  piece_evals[5] = 100;
  piece_evals[6] = -20000;
  piece_evals[7] = -800;
  piece_evals[8] = -500;
  piece_evals[9] = -315;
  piece_evals[10] = -300;
  piece_evals[11] = -100;

  generate_fast_pst(PST_K, 0);
  generate_fast_pst(PST_Q, 1);
  generate_fast_pst(PST_R, 2);
  generate_fast_pst(PST_B, 3);
  generate_fast_pst(PST_N, 4);
  generate_fast_pst(PST_P, 5);
  generate_fast_pst(PST_k, 6);
  generate_fast_pst(PST_q, 7);
  generate_fast_pst(PST_r, 8);
  generate_fast_pst(PST_b, 9);
  generate_fast_pst(PST_n, 10);
  generate_fast_pst(PST_p, 11);
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
void PstManager::generate_fast_pst(int* pst, int piece_index){

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


