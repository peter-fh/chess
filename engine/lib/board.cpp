#include "board.h"


Board::Board(){
	for (int i=0; i < 12; i++){
		pieces[i] = 0ULL;
	}
	this->init_from_fen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
}

Board::Board(std::string fen){
	this->init_from_fen(fen);
}


void Board::init_from_fen(std::string fen){
	std::unordered_map<char, int> index_map = {
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

	int i = 0;
	int square = 63;
	for (char c; (c=fen[i]) != ' '; ++i){
		if (isdigit(c)){
			square -= c - '0';
		} else if (index_map.count(c) != 0) {
			int piece_idx = index_map[c];
			this->pieces[piece_idx] |= 1ULL << square;
			square--;
		}
	}
}


std::string Board::fen(){
	std::unordered_map<int, char> piece_map = {
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

	std::string fen = "";
	for (int i=63; i >= 0; --i){
		for (int j=0; j < 12; ++j){
			if (this->pieces[j] & (1ULL << i)){
				std::cout << "Square " << i << " contains piece " << piece_map[j] << "\n";
				fen += piece_map[j];
			}
		}	
		if (i % 8 == 0 && i != 0){
			fen += "/";
		}
	}
	return fen;
}



std::ostream& operator<<(std::ostream& out, const Board& board){
	for (int i=63; i >= 0; --i){
		for (int j=0; j < 12; ++j)
		if (i % 8 == 0){
			out << "\n";
		}
	}

	return out;
}
