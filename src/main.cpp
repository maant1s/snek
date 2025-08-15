#include "snek.hpp"

int main() {
	std::unique_ptr<App> app = std::make_unique<App>();
	if(!app){
		std::cerr << "FATAL ERROR: Failed to initialize." << std::endl;
		return EXIT_FAILURE;
	}
	return app->run();
}