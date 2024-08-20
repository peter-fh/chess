#include "board.h"
#include <bitset>
#include <iostream>


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



Board::Board(){
	for (int i=0; i < 12; i++){
		pieces[i] = 0ULL;
	}
	this->init_from_fen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
}

Board::Board(std::string fen){
	for (int i=0; i < 12; i++){
		pieces[i] = 0ULL;
	}
	this->init_from_fen(fen);
}

std::string Board::int_to_square(int position){
	std::string square = "";
	char letter = 'a' + (7-(position % 8));
	square += letter + std::to_string(position / 8 + 1);
	return square;
}

int Board::square_to_int(std::string square){
	char row = square[0];
	char column = square[1];
	return (7 - (row - 'a')) + (column - '0'-1)*8;
}

void Board::init_from_fen(std::string fen){
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
	++i;

	std::string turn = "";
	for (char c; (c=fen[i]) != ' '; ++i){
		turn += c;
	}
	++i;

	if (turn == "w"){
		this->state.turn = WHITE;
	} else if (turn == "b"){
		this->state.turn = BLACK;
	} else {
		panic("Board::init_from_fen with " + fen + " has turn string " + turn);
	}
	

	std::string castle = "";
	for (char c; (c=fen[i]) != ' '; ++i){
		castle += c;
	}
	++i;

	for (int j=0; j < 4; ++j){
		if (castle.find(castle_characters[j]) != std::string::npos){
			this->state.valid_castle[j] = true;
	} else {
			this->state.valid_castle[j] = false;
		}
	}

	std::string en_passent = "";
	for (char c; (c=fen[i]) != ' '; ++i){
		en_passent += c;
	}
	++i;

	int en_passent_square = -2;
	if (en_passent == "-"){
		en_passent_square = -1;
	} else {
		en_passent_square = Board::square_to_int(en_passent);
	}
	if (en_passent_square == -2){
		panic("Board::init_from_fen(): En passent part of fen is: " + en_passent)
	}
	this->state.en_passent_position = en_passent_square;

	std::string halfmove = "";
	for (char c; (c=fen[i]) != ' '; ++i){
		halfmove += c;
	}
	if (halfmove == ""){
		panic("Board::init_from_fen(): Halfmove is empty on fen " + fen);
	}
	++i;
	this->state.halfmove = std::stoi(halfmove);

	std::string fullmove = "";
	for (char c; (c=fen[i]) != ' '; ++i){
		fullmove += c;
	}
	if (fullmove == ""){
		panic("Board::init_from_fen(): Halfmove is empty on fen " + fen);
	}
	++i;
	this->state.fullmove = std::stoi(fullmove);
}


std::string Board::fen(){
	std::string return_fen = "";
	int empty_squares = 0;
	for (int i=63; i >= 0; --i){
		bool found = false;
		for (int j=0; j < 12; ++j){
			if (this->pieces[j] & (1ULL << i)){
				if (found) {
					panic("Board::fen(): multiple pieces in one square");
				}
				if (empty_squares){
					return_fen += std::to_string(empty_squares);
					empty_squares = 0;
				}
				found = true;
				return_fen += piece_map[j];
			}
		}
		if (!found){
			empty_squares++;
		}
		if (i % 8 == 0){
			if (empty_squares){
				return_fen += std::to_string(empty_squares);
			}
			if (i != 0){
				return_fen += "/";
			}
			empty_squares = 0;
		} 
	}


	std::string turn_string = " ";
	turn_string += turn_characters[this->state.turn];
	return_fen += turn_string;

	std::string castle_string = " ";
	char castle_characters[4] = {'K', 'Q', 'k', 'q'};
	for (int i=0; i < 4; ++i){
		if (this->state.valid_castle[i]){
			castle_string += castle_characters[i];
		}
	}
	return_fen += castle_string;


	std::string en_passent_str = " ";
	int position = this->state.en_passent_position;
	if (position == -1){
		en_passent_str += "-";
	} else {
		en_passent_str += Board::int_to_square(position);
	}
	if (en_passent_str == " "){
		panic("Board::fen(): state.en_passent_position=" + std::to_string(position));
	}
	return_fen += en_passent_str;

	return_fen += " " + std::to_string(this->state.halfmove);
	return_fen += " " + std::to_string(this->state.fullmove);

	return return_fen;
}



std::ostream& operator<<(std::ostream& out, const Board& board){
	for (int i=0; i < 12; ++i){
		std::bitset<64> piece(board.pieces[i]);
		std::cout << piece_map[i] << ": " << piece << "\n";
	}
	return out;
}


