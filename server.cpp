#include "httplib.h"

int main() {
	using namespace httplib;
	Server server;

	auto ret = server.set_mount_point("/", "chess/");
	if (!ret) {
		std::cout << "Did not find mounting point for chess frontend\n";
	}

	server.Post("/engine", [](const httplib::Request &req, httplib::Response &res) {
		std::string board = req.body;
		std::cout << "recieved board:" << board << "\n";
		res.status = StatusCode::OK_200;
	});


	std::cout << "\n\nStarting server on port 8080\n";
	server.listen("0.0.0.0", 8080);
}
