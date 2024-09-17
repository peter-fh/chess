#include <iostream>
#include <cassert>
#include <map>
#include <fstream>
#include <sstream>
#include "rays.h"
#include "prettyboard.h"
#include "search.h"
#include <chrono>

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

	std::cout << "test_fen(): passed\n";
}


void test_square(){
	for(int i=0; i < 64; ++i){
		std::string square = Board::int_to_square(i);
		int position = Board::square_to_int(square);
		//std::cout << "i=" << i <<", square=" << square << ", position=" << position << "\n";
		assert(position == i);
	}
	std::cout << "test_square(): passed\n";

}


void print_rays(){
	Rays rays;
	for (int i=0; i < 64; ++i){
		std::cout << "-------------------------" << i << "\n";
		std::cout << Prettyboard(west(rays, (1ULL << i))) << "\n";
	}
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
		bitboard ray = north(rays, test_case);
		//std::cout << "Square: " << key << "\n";
		//std::cout << "Ray:\n" << Prettyboard(ray) << "\n";
		//std::cout << "Val:\n" << Prettyboard(val) << "\n";
		assert(ray == val);
	}

	for (auto const& [key, val]: northeast_cases){
		bitboard test_case = 1ULL << key;
		bitboard ray = northeast(rays, test_case);
		//std::cout << "Square: " << key << "\n";
		//std::cout << "Ray:\n" << Prettyboard(ray) << "\n";
		//std::cout << "Val:\n" << Prettyboard(val) << "\n";
		assert(ray == val);
	}
	for (auto const& [key, val]: east_cases){
		bitboard test_case = 1ULL << key;
		bitboard ray = east(rays, test_case);
		//std::cout << "Square: " << key << "\n";
		//std::cout << "Ray:\n" << Prettyboard(ray) << "\n";
		//std::cout << "Val:\n" << Prettyboard(val) << "\n";
		assert(ray == val);
	}

	for (auto const& [key, val]: southeast_cases){
		bitboard test_case = 1ULL << key;
		bitboard ray = southeast(rays, test_case);
		//std::cout << "Square: " << key << "\n";
		//std::cout << "Ray:\n" << Prettyboard(ray) << "\n";
		//std::cout << "Val:\n" << Prettyboard(val) << "\n";
		assert(ray == val);
	}

	for (auto const& [key, val]: south_cases){
		bitboard test_case = 1ULL << key;
		bitboard ray = south(rays, test_case);
		//std::cout << "Square: " << key << "\n";
		//std::cout << "Ray:\n" << Prettyboard(ray) << "\n";
		//std::cout << "Val:\n" << Prettyboard(val) << "\n";
		assert(ray == val);
	}
	std::cout << "test_rays(): passed\n";

}


typedef struct MovesTestCase{
	std::string fen;
	std::string moves;
} MovesTestCase;

void test_get_moves(){
	std::ifstream log_file("../log.txt");
	std::vector<MovesTestCase> test_cases;
	if (!log_file.is_open()){
		panic("could not open log.txt\n");
	}

	std::string line;
	while (getline(log_file, line)){
		MovesTestCase test_case;
		if (line.find(";") != std::string::npos){
			test_case.fen = line.substr(0, line.find(";"));
			test_case.moves = line.substr(line.find(";")+1, line.length());
			test_cases.push_back(test_case);
		}
	}


	log_file.close();

	for (auto test_case: test_cases) {
		Board board(test_case.fen);
		Moves* moves = board.get_moves();
		std::stringstream sout;
		sout << *moves;
		std::string calculated_moves = sout.str();
		assert(test_case.moves == calculated_moves);
	}
	std::cout << "test_get_moves(): passed\n";
}


void test_dfs(Board& board, int depth){
	if (depth == 0){
		return;
	}

	Moves* moves = board.get_moves();
	while (true){
		Move* move = board.make_next_move(moves);
		if (move->index == -1){
			break;
		}
		/*std::cout << "Made move " << *move << ":\n" << board << "";*/
		test_dfs(board, depth - 1);
		board.unmake_move(move);
		/*std::cout << "Unmade move\n" << board << "\n";*/
		//assert(board.validate());
	}
}

// Rafe: the day I start wearing new shoes is the day I start wearing new shoes

void test_make_moves(){
	
	Board board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
	//test_dfs(board, 1);
	std::cout << "test_make_moves(): passed\n";

}


void test_engine_takes_king(){
	Board board("8/3k4/8/8/8/3Q4/K7/8 w - - 0 1");
	//Board board("kbK5/pp6/1P6/8/8/8/8/R7 w - - 0 1");
	//std::cout << board << "\n";
	//std::cout << Prettyboard(board.pieces[6]) << "\n\n";
	Move* move = engine_move(board, 3);
	//std::cout << Prettyboard(move->to) << "\n\n";
	//std::cout << Prettyboard(board.pieces[6]) << "\n\n";
	assert((move->to & board.pieces[0]) != 0 || (move->to & board.pieces[6]) != 0);
	std::cout << "test_engine_takes_king(): passed\n";
}


void time_for_dfs(int depth){
	using namespace std::chrono;
	auto start = high_resolution_clock::now();
	Board board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
	Move* move = engine_move(board, depth);
	auto end = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(end - start);
	std::cout << "Time for search at depth " << depth << ": " << duration.count() << "ms\n";
}


int main(){
	test_square();
	test_fen();
	test_rays();
	test_get_moves();
	test_make_moves();
	test_engine_takes_king();
	time_for_dfs(4);
	std::cout << "passed all tests\n";
}

