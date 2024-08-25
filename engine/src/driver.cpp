#include <iostream>
#include "board.h"


int test_hash(int n, int (hash_function)(int n, bitboard k)){
	bitboard* arr = new bitboard[n];
	for (int i=0; i < n; ++i){
		arr[i] = 0;
	}

	
	int collisions = 0;
	for (int i=0; i < 64; ++i){
		int index = hash_function(n, (1ULL << i));
		if (arr[index] != 0){
			++collisions;
		}
		arr[index] = (1ULL << i);
	}

	std::cout << "\n";
	for (int i=0; i < n; ++i){
		std::cout << std::bitset<64>(arr[i]) << " [" << i << "]\n";
		//std::cout << "[" << i << "]: " << std::bitset<64>(arr[i]) << "\n";
	}
	delete[] arr;
	return collisions;
}

int modulo_hash(int n, bitboard k){
	return k % n;
}

int _msb(bitboard b){
	int position = 0;
	while (b >>= 1){
		++position;
	}
	return position;
}

int _msb_only(bitboard b){
	return b & -b;
		
}

int main(){
	//int n=67;
	//int collisions = test_hash(n, modulo_hash);
	//std::cout << "Modulo hash: " << collisions << " collisions.\n";
	//std::cout << _msb(0b101010) << "\n";

	bitboard _ = 0b0000000000000000;
	bitboard b = 0b1101000101011010;

	std::cout << std::bitset<16>(b) << "\n";
	std::cout << std::bitset<16>(_msb_only(b)) << "\n";
	//panic("Driver has not been implemented");
}
