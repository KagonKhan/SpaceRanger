#include "pch.h"
#pragma warning(disable : 26812)


#include "Game.h"



/* 
* SFML does not work well with scaling, resulting in either native fullscreen or windowed mode
	TODO:
		- DONE = Add precompiled headers
		- Animate main menu buttons 
		- Convert to using smart pointers? i guess?
		- Fix leaks
		- Reposition for fullscreen
		- Have somewhere window options saved so that it can be recreated properly (config)


*/

int main() {

	
	Game game;
	game.run(60);
}