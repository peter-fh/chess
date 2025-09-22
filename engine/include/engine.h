#include "board.h"

class Engine {
public:
	Engine();
	std::string run(std::string fen);
private:
	const Rays rays;
	const PstManager* pst_manager;
	const std::array<uint16_t, 65536> weights;
	const std::array<uint16_t, 65536> msbs;
}
