#include <iostream>
#include <cassert>
#include "board.h"

void assert_fen(){
	std::vector<std::string> fens = {
		"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1",
		"rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq c6 0 2",
		"rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2",
		"rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1"
	};

	std::string out;
	Board board; 

	for (std::string fen: fens){
		board = Board(fen);
		out = board.fen();
		//std::cout << fen << "->" << out << "\n\n";
		assert(out == fen);
	}

	std::cout << "assert_fen(): passed\n";
}


void assert_square(){
	for(int i=0; i < 64; ++i){
		std::string square = Board::int_to_square(i);
		int position = Board::square_to_int(square);
		//std::cout << "i=" << i <<", square=" << square << ", position=" << position << "\n";
		assert(position == i);
	}
	std::cout << "assert_square(): passed\n";

}

int main(){
	assert_square();
	assert_fen();
	std::cout << "passed all tests\n";
}
