#include <iostream>
#include "test.h"
#include "benchmark.h"

void RunAllTests(){
	std::cout << "\n\n\n---------------RUNNING ALL TESTS---------------\n";
	Test::test_square();
	Test::test_fen();
	Test::test_rays();
	Test::test_get_moves();
	Test::test_make_moves();
	Test::test_engine_takes_king(false);
	Test::test_read_psts();
	std::cout << "---------------PASSED ALL TESTS----------------\n";
}

void RunAllBenchmarks(){
	std::cout << "\n\n\n-------------RUNNING ALL BENCHMARKS------------\n";
	Benchmark::measure_dfs(4);
	Benchmark::measure_startup();
	std::cout << "------------FINISHED ALL BENCHMARKS------------\n";
}

int main(){
	RunAllTests();
	RunAllBenchmarks();
}
