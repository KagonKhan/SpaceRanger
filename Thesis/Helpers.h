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
	
	//////
	/// Initializes the window, uses values provided in a string
	/// if the string not provided, inits 1024x768 window
	//////
	static void CreateWindow(sf::RenderWindow& window, std::optional<std::string> fileContents = std::nullopt);
	//////
	/// loads to the provided strings, from the provided path, reading line by line
	//////
	static void LoadFileToString(const std::filesystem::path& path, std::string& loadTo);
	//////
	/// Replaces in string 's', the first found 'toReplace' string, with 'replaceWith'
	//////
	static void ReplaceFirstOccurance(std::string& s, std::string_view toReplace, std::string_view replaceWith);

    //////
    /// Returns true if provided 2D point is contained in the 'area'
    //////
	static bool CheckIfPointContainedInArea(const sf::Vector2f& pos, const sf::FloatRect& area);

	//////
	/// Returns float precision value converted from radians to degrees.
	//////
	static float toDeg(float rad);
	//////
	/// Returns float precision value converted from 2D point to degrees.
	//////
	static float toDeg(const sf::Vector2f& vec);
	//////
	/// Returns float precision value converted from degrees to radians.
	//////
	static float toRad(float deg);
	//////
	/// Returns normalized 2D vector
	//////
	static sf::Vector2f normalize(const sf::Vector2f& vec);
	//////
    /// Normalizes 2D vector in place
    //////
	static void normalize(sf::Vector2f& vec);
	//////
    /// Returns float precision value as length of the provided vector
    //////
	static float getLength(sf::Vector2f vec);

	//////
	/// Generates random INT number from the interval, and casts the results to T
	//////	
	template <typename T> inline static T getRandom(T lower, T upper);

	//////
	/// Draws the path using white circles of 1.f radius on the provided target
	//////	
	static void drawPath(sf::RenderTarget& target, const Spline& path);
	//////
	/// Prints vector values to the console
	//////	
	static void print(sf::Vector2f vec);


	//////
	/// Returns float precision value of perpendicular dot product of the provided vecs
	//////	
	static float perpDot(const sf::Vector2f& A, const sf::Vector2f& B);
	//////
	/// Returns float precision value of dot product of the provided vecs
	//////	
	static float dot(const sf::Vector2f& A, const sf::Vector2f& B);
};


template <typename T>
inline static T Helpers::getRandom(T lower, T upper) {
	static std::random_device	rand{};
	static std::default_random_engine engine{ rand() };


	std::uniform_int_distribution dist{ static_cast<int>(lower), static_cast<int>(upper)};
	return static_cast<T>(dist(engine));
};
