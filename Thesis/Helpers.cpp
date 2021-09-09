#include "pch.h"
#include "Helpers.h"

void Helpers::CreateWindow(sf::RenderWindow& window, std::optional<std::string> fileContents)
{


	std::string title;
	int x = 400, y = 400;
	int framerate = 120;
	bool fullscreen = 0, borderless = 0, vsync = 0;

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
				std::cout << "\n" << x << ", " << y << "\n";
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

void Helpers::ReplaceFirstOccurance(std::string& string, const std::string& toReplace, const std::string& replaceWith)
{
	std::size_t pos = string.find(toReplace);
	if (pos == std::string::npos)
		return;

	string.replace(pos, toReplace.length(), replaceWith);
}


bool Helpers::CheckIfPointContainedInArea(const sf::Vector2f& pos, const sf::Vector2f& size)
{
	if (pos.x > size.x || pos.x < -size.x || pos.y > size.y || pos.y < -size.y)
		return false;
	return true;
}

float Helpers::perpDot(const sf::Vector2f& A, const sf::Vector2f& B)
{
	return (A.x * B.y) - (A.y * B.x);
}

float Helpers::dot(const sf::Vector2f& A, const sf::Vector2f& B)
{
	return (A.x * B.x) + (A.y * B.y);
}


void Helpers::LoadFileToString(const std::filesystem::path& path, std::string& loadTo)
{
	std::ifstream file(path, std::ios::in | std::ios::binary);

	/*const auto  size = std::filesystem::file_size(path);
	loadTo = std::string(size, '\0');
	file.read(loadTo.data(), size);*/
	std::string line;
	while (std::getline(file, line))
		loadTo += line;
}