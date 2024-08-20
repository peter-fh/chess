#include "rays.h"
#include <iostream>
#include <bitset>


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

static const bitboard BOUNDS_MASK = 0xff818181818181ff;
bitboard cast_ray(bitboard b, int direction){

	int position = 0;
	bitboard ray = b;
	while (b >>= 1){
		position++;
	}

	int x = position % 8;
	int y = position / 8;
	if (x == 7 && direction % 8 == 1){
		return ray;
	}
	if (x == 0 && direction % 8 == 7){
		return ray;
	}
	if (y == 7 && direction / 8 == 1){
		return ray;
	}
	if (y == 0 && direction / 8 == -1){
		return ray;
	}

	do {
		if (direction < 0){
			ray |= ray >> abs(direction);
		} else {
			ray |= ray << direction;
		}
		std::cout << std::bitset<64>(ray) << ", direction: " << direction << "\n";
	} while (!(ray & BOUNDS_MASK));
	return ray;
}

void Rays::generate_rays(){
	for (int i=0; i < 64; ++i){
		bitboard b = 1ULL << i;
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



