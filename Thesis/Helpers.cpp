#include "pch.h"
#include "Helpers.h"
#include "Spline.h"
void Helpers::CreateWindow(sf::RenderWindow& window, std::optional<std::string> fileContents)
{


	std::string title;
	int x				{ 400 };
	int y				{ 400 };
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

void Helpers::ReplaceFirstOccurance(std::string& string, std::string_view toReplace, std::string_view replaceWith)
{
	std::size_t pos = string.find(toReplace);
	if (pos == std::string::npos)
		return;

	string.replace(pos, toReplace.length(), replaceWith);
}


bool Helpers::CheckIfPointContainedInArea(const sf::Vector2f& pos, const sf::FloatRect& area)
{
	if(area.contains(pos))
		return true;
	else
		return false;
}

float Helpers::toDeg(float rad)
{
	return rad * 180.f / static_cast<float>(M_PIl);
}

float Helpers::toDeg(const sf::Vector2f& vec)
{
	return Helpers::toDeg(atan2f(vec.y, vec.x));
}

float Helpers::toRad(float deg)
{
	return deg * static_cast<float>(M_PIl) / 180.f;
}

sf::Vector2f Helpers::normalize(const sf::Vector2f& vec)
{
	sf::Vector2f result = vec;
	if (float length = std::sqrtf(vec.x * vec.x + vec.y * vec.y); length != 0)
		result /= length;

	return result;
}

void Helpers::normalize(sf::Vector2f& vec)
{
	float length = getLength(vec);
	if (length != 0)
		vec /= length;
}

float Helpers::getLength(sf::Vector2f vec)
{
	return std::sqrtf(vec.x * vec.x + vec.y * vec.y);
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

void Helpers::print(sf::Vector2f vec)
{
	BOOST_LOG_TRIVIAL(info) << vec.x << ", " << vec.y << '\n';
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