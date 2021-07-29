#pragma warning(disable : 26812)
#include "UI.h"

#include "Configuration.h"
#include "UI.h"
#include "Button.h"
int main() {
	Configuration::initialize();

	sf::RenderWindow window(sf::VideoMode(1600, 1024), "test");
	sf::Event sfevent;

	UI ui(window);
	VerticalLayout* layout = new VerticalLayout;
	TextButton* button = new TextButton("New Game");
	TextButton* button2 = new TextButton("Options");

	layout->add(button);
	layout->add(button2);

	ui.addLayout(layout);

	while (window.isOpen()) {
		while (window.pollEvent(sfevent))
			if (sfevent.type == sf::Event::Closed)
				window.close();





		window.clear(sf::Color(255,155,100));
		window.draw(ui);
		window.display();
	}
}