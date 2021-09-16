#pragma once
#include <filesystem>
class Helpers
{
private:
	Helpers() = delete;
	Helpers(const Helpers&) = delete;
	Helpers& operator= (const Helpers&) = delete;
public:
	
	static void CreateWindow(sf::RenderWindow& window, std::optional<std::string> fileContents = std::nullopt);
	static void LoadFileToString(const std::filesystem::path& path, std::string& loadTo);
	static void ReplaceFirstOccurance(std::string& s, const std::string& toReplace, const std::string& replaceWith);

	// return vec2f from global bounds 

	// Receives position, and checks if contained in area
	static bool CheckIfPointContainedInArea(const sf::Vector2f& pos, const sf::Vector2f& area);


	static float perpDot(const sf::Vector2f& A, const sf::Vector2f& B);
	static float dot(const sf::Vector2f& A, const sf::Vector2f& B);
};
