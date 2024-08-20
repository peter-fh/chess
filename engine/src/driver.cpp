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
		std::cout << "[" << i << "]: " << arr[i] << "\n";
	}
	delete[] arr;
	return collisions;
}

int modulo_hash(int n, bitboard k){
	return k % n;
}


int main(){
	int n=67;
	int collisions = test_hash(n, modulo_hash);
	std::cout << "Modulo hash: " << collisions << "collisions.\n";
	//panic("Driver has not been implemented");
}
