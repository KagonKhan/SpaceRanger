#include "pch.h"
#pragma warning(disable : 26812)


#include "Game.h"



/* 
	TODO:
		- DONE = Add precompiled headers
		- Animate main menu buttons 
		- Convert to using smart pointers? i guess?
		- Fix leaks
		- Reposition for fullscreen
		- Have somewhere window options saved so that it can be recreated properly (config)


*/

int main() {
	Configuration::initialize();
	
	Game game(sf::VideoMode(1920, 1080), "thesis", 120, false);
	game.run(30);
}