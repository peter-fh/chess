#include "httplib.h"
#include <board.h>

int main() {
	using namespace httplib;
	Server server;

	auto ret = server.set_mount_point("/", "chess/");
	if (!ret) {
		std::cout << "Did not find mounting point for chess frontend\n";
	}
	server.Get("/engine", [](const httplib::Request &req, httplib::Response &res) {
		if (req.has_param("board")){
		}
	});

	server.listen("0.0.0.0", 8080);
}
