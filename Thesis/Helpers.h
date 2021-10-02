#pragma once
#include <filesystem>

class Spline;
class Helpers
{
private:
	Helpers() = delete;
	Helpers(const Helpers&) = delete;
	Helpers& operator= (const Helpers&) = delete;
public:
	
	static void CreateWindow(sf::RenderWindow& window, std::optional<std::string> fileContents = std::nullopt);
	static void LoadFileToString(const std::filesystem::path& path, std::string& loadTo);
	static void ReplaceFirstOccurance(std::string& s, std::string_view toReplace, std::string_view replaceWith);

	// return vec2f from global bounds 

	// Receives position, and checks if contained in area
	static bool CheckIfPointContainedInArea(const sf::Vector2f& pos, const sf::Vector2f& area);


	static float toDeg(float rad);
	static float toDeg(const sf::Vector2f& vec);
	static float toRad(float deg);
	static sf::Vector2f normalize(const sf::Vector2f& vec);
	static void normalize(sf::Vector2f& vec);
	static float getLength(sf::Vector2f vec);

	/**
	* \brief T is the return type, args are converted to int regardless	
	*/
	template <typename T> inline static T getRandom(T lower, T upper);

	
	
	static void drawPath(sf::RenderTarget& target, const Spline& path);
	static void print(sf::Vector2f vec);




	static float perpDot(const sf::Vector2f& A, const sf::Vector2f& B);
	static float dot(const sf::Vector2f& A, const sf::Vector2f& B);
};
template <typename T>
inline static T Helpers::getRandom(T lower, T upper) {
	static std::random_device	rand{};
	static std::default_random_engine engine{ rand() };


	std::uniform_int_distribution dist{ static_cast<int>(lower), static_cast<int>(upper)};
	return static_cast<T>(dist(engine));
};
