#include "board.h"
#include "board_types.h"
#include "prettyboard.h"
#include <bitset>
#include <iostream>



Board::Board(){
	for (int i=0; i < 12; i++){
		pieces[i] = 0ULL;
	}
	this->init_from_fen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
	//this->init_from_fen("rnbqkbnr/ppp1pppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
	set_sided_bitboards();
	init_msbs();
	init_weights();
}

Board::Board(std::string fen){
	for (int i=0; i < 12; i++){
		pieces[i] = 0ULL;
	}
	this->init_from_fen(fen);
	set_sided_bitboards();
	init_msbs();
	init_weights();
}

void Board::init_weights(){
	for (int i=0; i < 65536; ++i){
		weights[i] = slow_hamming_weight(i);
	}
}

void Board::init_msbs(){
	for (int i=0; i < 65536; ++i){
		msbs[i] = slow_msb(i);
	}
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
		this->piece_index_adder = 0;
	} else if (turn == "b"){
		this->state.turn = BLACK;
		this->piece_index_adder = 6;
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
	for (char c; (c=fen[i]) != 0; ++i){
		fullmove += c;
		if (i > fen.length()){
			panic("Seeking past fen length!\n");
		}
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


void Board::change_turn(){
	if (state.turn == WHITE){
		state.turn = BLACK;
		set_sided_bitboards();
	} else if (state.turn == BLACK){
		state.turn = WHITE;
		set_sided_bitboards();
	} else {
		panic("Turn in board while changing turn is not white or black")
	}
}


void Board::set_sided_bitboards(){
	friendly_pieces = 0ULL;
	opposite_pieces = 0ULL;
	if (state.turn == 0){
		for (int i=0; i < 6; ++i){
			friendly_pieces |= pieces[i];
		}
		for (int i=6; i < 12; ++i){
			opposite_pieces |= pieces[i];
		}
		piece_index_adder = 0;
	} else {
		for (int i=0; i < 6; ++i){
			opposite_pieces |= pieces[i];
		}
		for (int i=6; i < 12; ++i){
			friendly_pieces |= pieces[i];
		}
		piece_index_adder = 6;

	}
	all_pieces = friendly_pieces | opposite_pieces;
	phantom_pawn = 0ULL;
	if (state.en_passent_position != -1){
		phantom_pawn = 1ULL << state.en_passent_position;
	}


}

std::ostream& _operator(std::ostream& out, const Move& move){

	int move_to = msb_index(move.to);
	std::string move_word = "";
	std::cout << "Move index: " << move.index << "\n";
	move_word += piece_map[move.index];
	move_word += Board::int_to_square(move_to);
	move_word += " ";
	out << move_word;
	return out;
}

std::ostream& operator<<(std::ostream& out, const Move& move){

	int move_to = msb_index(move.to);
	std::string move_word = "";
	std::cout << "Move index: " << move.index << "\n";
	move_word += piece_map[move.index];
	move_word += Board::int_to_square(move_to);
	move_word += " ";
	out << move_word;
	return out;

}

std::ostream& operator<<(std::ostream& out, const Moves& moves){
	std::vector<std::string> moves_list;
	for (int i=moves.index; i < 12; ++i){
		Move move = moves.moves[i];
		bitboard move_board = move.to;
		while (move_board){
			int move_to = msb_index(move_board);
			std::string move_word = "";
			move_word += move_piece_map[i];
			move_word += Board::int_to_square(move_to);
			move_word += " ";
			moves_list.push_back(move_word);
			move_board ^= (1ULL << move_to);

		}
	}
	if (moves.castles[K_CASTLE_INDEX]){
		moves_list.push_back("oo ");
	}
	if (moves.castles[Q_CASTLE_INDEX]){
		moves_list.push_back("ooo ");
	}
	
	std::sort(moves_list.begin(), moves_list.end());

	std::string moves_string = "";
	for (std::string& move: moves_list){
		move[0] = tolower(move[0]);
		moves_string += move;
	}

	out << moves_string;
	return out;
}
std::ostream& operator_(std::ostream& out, const Moves& moves){
	std::vector<std::string> moves_list;
	for (int i=moves.index; i < 12; ++i){
		Move move = moves.moves[i];
		bitboard move_board = move.to;
		std::cout << "Board for " << move_piece_map[i] << ":\n";
		std::cout << Prettyboard(move_board) << "\n";
	}
	if (moves.castles[K_CASTLE_INDEX]){
		moves_list.push_back("o-o ");
	}
	if (moves.castles[Q_CASTLE_INDEX]){
		moves_list.push_back("o-o-o ");
	}
	
	std::sort(moves_list.begin(), moves_list.end());

	std::string moves_string = "";
	for (std::string& move: moves_list){
		move[0] = tolower(move[0]);
		moves_string += move;
	}

	out << moves_string;
	return out;
}


std::ostream& operator<<(std::ostream& out, const Board& board){
	for (int i=63; i >= 0; --i){
		bool found = false;
		for (int j=0; j < 12; ++j){
			if ((1ULL << i) & board.pieces[j]){
				std::cout << piece_map[j];
				found = true;
			} 
		}
		if (!found){
			std::cout << "0";
		}
		std::cout << " ";
		if (i % 8 == 0){
			std::cout << "\n";
		}
	}
	/*for (int i=0; i < 12; ++i){*/
	/*	std::bitset<64> piece(board.pieces[i]);*/
	/*	std::cout << piece_map[i] << ": " << Prettyboard(board.pieces[i])<< "\n";*/
	/*}*/
	return out;
}


bool Board::validate(){
	for (int i=0; i < 64; ++i){
		bool found = false;
		for (int j=0; j < 12; ++j){
			if ((pieces[j] & (1ULL << i)) != 0){
				if (found){
					return false;
				}
				found = true;
			}
		}
	}
	return true;
}


