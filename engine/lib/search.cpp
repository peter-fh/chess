#include "search.h"
#include "board.h"
#include <sstream>
#include <string>


int dfs(Board& board, int depth){
	if (depth == 0){
		return board.evaluate();
	}


	int max_eval = -100000;
	Moves* moves = board.get_moves();
	while (true){
		Move* move = board.make_next_move(moves);
		if (move->index == -1){
			break;
		}

		max_eval = std::max(-dfs(board, depth - 1), max_eval);
		board.unmake_move(move);
	}
	return max_eval;
}


Move* dfs_root(Board& board, int depth){
	int max_eval = -100000;
	Move* max_move = new Move;
	Moves* moves = board.get_moves();
	while (true){
		Move* move = board.make_next_move(moves);
		if (move->index == -1){
			break;
		}

		int eval = -dfs(board, depth-1);
		if (eval > max_eval){
			max_move = move;
			max_eval = eval;
		}
		board.unmake_move(move);
	}
	return max_move;
}


const char* engine_move(char* board_fen, int depth){
	Board board(board_fen);
	Move* move = dfs_root(board, depth);
	std::ostringstream oss;
	oss << move;
	std::string out = oss.str();
	char* result = new char[out.size() + 1];
	std::strcpy(result, out.c_str());
	return result;
}


