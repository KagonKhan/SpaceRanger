#pragma warning(disable : 26812)


#include "Game.h"
int main() {
	Configuration::initialize();
	
	Game game(sf::VideoMode(1920, 1080), "thesis", 120, false);
	game.run(30);
}