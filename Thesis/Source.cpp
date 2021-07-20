#pragma warning(disable : 26812)

#include "SFML/Graphics.hpp"
#include "Frame.h"
#include "VLayout.h"
#include "TextButton.h"

int main() {
	Configuration::initialize();

	sf::RenderWindow window(sf::VideoMode(1600, 1024), "test");
	sf::Event sfevent;

	GUI::Frame mainMenu(window);
	enum Status {
		StatusMainMenu, StatusGame, StatusConfiguration, StatusPaused,
		StatusExit
	} status = Status::StatusMainMenu;

	GUI::VLayout* layout = new GUI::VLayout;
	layout->setSpace(25);
	GUI::TextButton* newGame = new GUI::TextButton("New Game");
	GUI::TextButton* config = new GUI::TextButton("Configuration");
	GUI::TextButton* exit = new GUI::TextButton("Exit");
	layout->add(newGame);
	//layout->add(config);
	//layout->add(exit);
	mainMenu.setLayout(layout);


	while (window.isOpen()) {
		while (window.pollEvent(sfevent))
			if (sfevent.type == sf::Event::Closed)
				window.close();



		window.draw(mainMenu);


		window.display();
		window.clear();
	}
}