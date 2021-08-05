#include "pch.h"
#pragma warning(disable : 26812)


#include "Game.h"
/*	TODO */
/*	CODE CLEANUP
*	 - Game - DONE
* 
* 
* 
* 
* 
* 
* 
* 
* 
*/


/* 
* SFML does not work well with scaling, resulting in either native fullscreen or windowed mode
	TODO:
		- DONE = Add precompiled headers
		- Animate main menu buttons 
		- Convert to using smart pointers? i guess?
		- Fix leaks
		- Reposition for fullscreen
		- Have somewhere window options saved so that it can be recreated properly (config)
		- Check if the checkbox fits in shaded area if not raise some info or sth
		- Text position is not in the middle of the button
		- Recreating the window in options menu - do i have to .setframeratelimit - read
		- make a nicer cross in checkbox 
*/

int main() {
	Game game;
	game.run(120);
}

/*
		TODO:
			- Some area to spend points,
			- Possibly an area to add modules?
			- Button to launch
			- Some info on current level
			- Ship sprite, enlarged i guess


			- What about levels? A switch with an enum? All of them are classes

	*/