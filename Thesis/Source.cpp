#include "pch.h"
#pragma warning(disable : 26812)
#include "Game.h"



int main() {
	Game::getInstance()->run(120);
	delete Game::getInstance();
}

