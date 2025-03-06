#include "board.h"
#include "search.h"



int main(int argc, char* argv[]) {
	std::string fen = argv[1];
	Board board(fen);
	std::cout << *engine_move(board, 4);
}
