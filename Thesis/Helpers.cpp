#include "pch.h"
#include "Helpers.h"
#include "Spline.h"
void Helpers::CreateWindow(sf::RenderWindow& window, std::optional<std::string> fileContents)
{
	std::string title;
	int x				{ 1024 };
	int y				{ 768 };
	int framerate		{ 120 };
	bool fullscreen		{ false };
	bool borderless		{ false };
	bool vsync			{ false };

	std::ifstream settings("../media/config/screen.txt");
	if (!settings.is_open())
		return;


	std::stringstream buffer;
	buffer << settings.rdbuf();
	settings.close();

	std::string name;
	while (buffer >> name) {
		if (name == "title") {
			buffer >> title;
		}
		else if (name == "resolution") {
			buffer >> x >> y;
		}
		else if (name == "framerate") {
			buffer >> framerate;
		}
		else if (name == "fullscreen") {
			buffer >> fullscreen;
		}
		else if (name == "borderless") {
			buffer >> borderless;
		}
		else if (name == "vsync") {
			buffer >> vsync;
		}
	}



	if (fileContents.has_value()) {
		std::stringstream buffer;
		buffer << fileContents.value();

		std::string name;
		while (buffer >> name) {
			if (name == "fullscreen") {
				buffer >> fullscreen;
			}
			if (name == "vsync") {
				buffer >> vsync;
			}
			if (name == "resolution") {
				std::string skip;
				buffer >> x >> skip >> y;
			}
		}
	}

	using namespace sf::Style;

	if (fullscreen) {
		if (borderless)
			window.create(sf::VideoMode::getDesktopMode(), title, None);
		else
			window.create(sf::VideoMode::getDesktopMode(), title, Titlebar | Close | Fullscreen);
	}
	else
		window.create(sf::VideoMode(x, y), title, Titlebar | Close);


	window.setFramerateLimit(framerate);
	window.setVerticalSyncEnabled(vsync);
	window.setMouseCursorVisible(false);

	Configuration::boundaries = sf::Vector2f(window.getSize());
}


void Helpers::drawPath(sf::RenderTarget& target, const Spline& path)
{
	sf::CircleShape pixel(1.f);
	pixel.setFillColor(sf::Color::White);

	for (auto&& point : path.getPath()) {
		pixel.setPosition(point);
		target.draw(pixel);
	}
}
