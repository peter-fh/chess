#include <iostream>
#include <cassert>
#include <map>
#include <fstream>
#include <sstream>
#include "rays.h"
#include "prettyboard.h"
#include "search.h"
#include <chrono>
#include "benchmark.h"

namespace Benchmark {

void measure_dfs(int depth){
	int iterations = 100;
	std::cout << "Calculating search time at depth " << depth << " for " << iterations << " iterations\n";
	int total_search_time = 0;
	PstManager* pst_manager = new PstManager;
	for (int i=0; i < iterations; ++i){
		using namespace std::chrono;
		Board board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", pst_manager);
		auto start = high_resolution_clock::now();
		Move* _ = engine_move(board, depth);
		auto end = high_resolution_clock::now();
		auto duration = duration_cast<milliseconds>(end - start);
		auto count = duration.count();
		total_search_time += count;
		std::cout << "\rIteration " << i+1 << "/" << iterations << std::flush;
	}
	std::cout << "\n";
	std::cout << "Time for search at depth " << depth << ": " << static_cast<float>(total_search_time) / iterations << "ms\n";
}

void measure_startup(){
	int iterations = 10;
	std::cout << "Calculating startup time for " << iterations << " iterations\n";
	int total_startup_time = 0;
	for (int i=0; i < iterations; ++i){
		using namespace std::chrono;
		auto start = high_resolution_clock::now();
		Board board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
		auto end = high_resolution_clock::now();
		auto duration = duration_cast<milliseconds>(end - start);
		auto count = duration.count();
		total_startup_time += count;
		std::cout << "\rIteration " << i+1 << "/" << iterations << std::flush;
	}
	std::cout << "\n";
	std::cout << "Time for startup: " << static_cast<float>(total_startup_time) / iterations << "ms\n";
}

}
