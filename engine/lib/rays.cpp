#include "rays.h"
#include <iostream>
#include <bitset>
#include "prettyboard.h"


Rays::Rays(){
	zero_rays();
	generate_rays();
}


void Rays::zero_rays(){
	for (int i=0; i < N; ++i){
		_north[i] = 0ULL;
		_northeast[i] = 0ULL;
		_east[i] = 0ULL;
		_southeast[i] = 0ULL;
		_south[i] = 0ULL;
		_southwest[i] = 0ULL;
		_west[i] = 0ULL;
		_northwest[i] = 0ULL;
	}
}


bool in_bounds(int x, int y){

	if (x > 7 || x < 0){
		return false;
	} 
	if (y > 7 || y < 0){
		return false;
	}

	return true;
}


bitboard cast_ray(bitboard b, int direction){

	int position = 0;
	bitboard ray = 0ULL;
	while (b >>= 1){
		position++;
	}
	const int b_pos = position;
	//std::cout << "position: " << position <<"\n";

	int x = position % 8;
	int y = position / 8;
	int dx = 0;
	if (direction == 7 || direction == -1 || direction == -9){
		dx = -1;
	} else if (direction == 9 || direction == 1 || direction == -7){
		dx = 1;
	} else {
		//std::cout << "dx is zero, direction is " << direction << "\n";
	}
	int dy = 0;
	if (direction > 1){
		dy = 1;
	} else if (direction < -1){
		dy = -1;
	}

		int debug_direction = -1;
		int debug_pos = 27;
	while (in_bounds(x, y)){
		if (direction == debug_direction && b_pos == debug_pos){
			std::cout << "x for 2: " << x << ", y: " << y << "\n";
			std::cout << "dx for 2: " << dx << ", dy: " << dy << "\n";
			std::cout << "ray for 2:\n"  << Prettyboard(ray) << "\n";
		}
		position = x + y*8;
		//std::cout << "position2: " << position <<"\n";
		if (direction > 0){
			ray |= (1ULL << position);
		} else {
			ray |= (1ULL << position);
		}
		x += dx;
		y += dy;
	}

	if (direction == debug_direction && b_pos == debug_pos){
		std::cout << "2: " << Prettyboard(ray)<<  "\n";
	}
	return ray;

}

void Rays::generate_rays(){
	for (int i=0; i < 64; ++i){
		bitboard b = 1ULL << i;
		//std::cout << "i: " << i << "\n";
		_north[hash(b)] = cast_ray(b, 8);
		_northeast[hash(b)] = cast_ray(b, 7);
		_east[hash(b)] = cast_ray(b, -1);
		_southeast[hash(b)] = cast_ray(b, -9);
		_south[hash(b)] = cast_ray(b, -8);
		_southwest[hash(b)] = cast_ray(b, -7);
		_west[hash(b)] = cast_ray(b, 1);
		_northwest[hash(b)] = cast_ray(b, 9);
	}
}

bitboard Rays::north(bitboard b){
	return _north[hash(b)];
}
bitboard Rays::northeast(bitboard b){
	return _northeast[hash(b)];
}
bitboard Rays::east(bitboard b){
	return _east[hash(b)];
}
bitboard Rays::southeast(bitboard b){
	return _southeast[hash(b)];
}
bitboard Rays::south(bitboard b){
	return _south[hash(b)];
}
bitboard Rays::southwest(bitboard b){
	return _southwest[hash(b)];
}
bitboard Rays::west(bitboard b){
	return _southwest[hash(b)];
}
bitboard Rays::northwest(bitboard b){
	return _northwest[hash(b)];
}

inline int Rays::hash(bitboard b){
	return b % N;
}



