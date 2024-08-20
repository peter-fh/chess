#include <iostream>
#include <cassert>
#include <map>
#include "board.h"
#include "rays.h"
#include "prettyboard.h"

void test_fen(){
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


void test_square(){
	for(int i=0; i < 64; ++i){
		std::string square = Board::int_to_square(i);
		int position = Board::square_to_int(square);
		//std::cout << "i=" << i <<", square=" << square << ", position=" << position << "\n";
		assert(position == i);
	}
	std::cout << "assert_square(): passed\n";

}


void test_rays() {
	Rays rays;
	std::map<int, bitboard> north_cases = {
		{27, 0x808080808000000},
		{2, 0x404040404040404}
	};
	std::map<int, bitboard> northeast_cases = {
		{28, 0x102040810000000},
		{2, 0x10204}
	};
	std::map<int, bitboard> east_cases = {
		{27, 0xf000000},
		{0, 1}
	};
	std::map<int, bitboard> southeast_cases = {
		{38, 0x4020100804},
		{56, 0x100000000000000},	
		{63, 0x8040201008040201},
	};
	std::map<int, bitboard> south_cases = {
		{32, 0x101010101},
		{46, 0x404040404040},	
	};


	for (auto const& [key, val]: north_cases){
		bitboard test_case = 1ULL << key;
		bitboard ray = rays.north(test_case);
		std::cout << "Square: " << key << "\n";
		std::cout << "Ray:\n" << Prettyboard(ray) << "\n";
		std::cout << "Val:\n" << Prettyboard(val) << "\n";
		assert(ray == val);
	}

	for (auto const& [key, val]: northeast_cases){
		bitboard test_case = 1ULL << key;
		bitboard ray = rays.northeast(test_case);
		std::cout << "Square: " << key << "\n";
		std::cout << "Ray:\n" << Prettyboard(ray) << "\n";
		std::cout << "Val:\n" << Prettyboard(val) << "\n";
		assert(ray == val);
	}
	for (auto const& [key, val]: east_cases){
		bitboard test_case = 1ULL << key;
		bitboard ray = rays.east(test_case);
		std::cout << "Square: " << key << "\n";
		std::cout << "Ray:\n" << Prettyboard(ray) << "\n";
		std::cout << "Val:\n" << Prettyboard(val) << "\n";
		assert(ray == val);
	}

	for (auto const& [key, val]: southeast_cases){
		bitboard test_case = 1ULL << key;
		bitboard ray = rays.southeast(test_case);
		std::cout << "Square: " << key << "\n";
		std::cout << "Ray:\n" << Prettyboard(ray) << "\n";
		std::cout << "Val:\n" << Prettyboard(val) << "\n";
		assert(ray == val);
	}

	for (auto const& [key, val]: south_cases){
		bitboard test_case = 1ULL << key;
		bitboard ray = rays.south(test_case);
		std::cout << "Square: " << key << "\n";
		std::cout << "Ray:\n" << Prettyboard(ray) << "\n";
		std::cout << "Val:\n" << Prettyboard(val) << "\n";
		assert(ray == val);
	}

}

int main(){
	test_square();
	test_fen();
	test_rays();
	std::cout << "passed all tests\n";
}
