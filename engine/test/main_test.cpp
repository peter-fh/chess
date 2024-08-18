#include <iostream>
#include <cassert>
#include "board.h"

void assert_fen(){
	std::string fen, out;

	fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
	out = Board(fen).fen();
	std::cout << fen << "->" << out << "\n";
	assert(out == fen);

	fen =  "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
	out = Board(fen).fen();
	std::cout << fen << "->" << out << "\n";
	assert(out == fen);

	fen =  "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1";
	out = Board(fen).fen();
	std::cout << fen << "->" << out << "\n";
	assert(out == fen);

	fen =  "rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq c6 0 2";
	out = Board(fen).fen();
	std::cout << fen << "->" << out << "\n";
	assert(out == fen);

	fen =  "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2";
	out = Board(fen).fen();
	std::cout << fen << "->" << out << "\n";
	assert(out == fen);
}


int main(){
	assert_fen();
}
