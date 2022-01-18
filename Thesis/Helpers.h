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
	inline static void LoadFileToString(const std::filesystem::path& path, std::string& loadTo);
	//////
	/// Replaces in string 's', the first found 'toReplace' string, with 'replaceWith'
	//////
	inline static void ReplaceFirstOccurance(std::string& s, std::string_view toReplace, std::string_view replaceWith);

    //////
    /// Returns true if provided 2D point is contained in the 'area'
    //////
	inline static bool CheckIfPointContainedInArea(const sf::Vector2f& pos, const sf::FloatRect& area);

	//////
	/// Returns float precision value converted from radians to degrees.
	//////
	inline static float toDeg(float rad);
	//////
	/// Returns float precision value converted from 2D point to degrees.
	//////
	inline 	static float toDeg(const sf::Vector2f& vec);
	//////
	/// Returns float precision value converted from degrees to radians.
	//////
	inline 	static float toRad(float deg);
	//////
	/// Returns normalized 2D vector
	//////
	inline 	static sf::Vector2f normalize(const sf::Vector2f& vec);
	//////
    /// Normalizes 2D vector in place
    //////
	inline 	static void normalize(sf::Vector2f& vec);
	//////
    /// Returns float precision value as length of the provided vector
    //////
	inline 	static float getLength(sf::Vector2f vec);

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
	inline static void print(sf::Vector2f vec);


	//////
	/// Returns float precision value of perpendicular dot product of the provided vecs
	//////	
	inline static float perpDot(const sf::Vector2f& A, const sf::Vector2f& B);
	//////
	/// Returns float precision value of dot product of the provided vecs
	//////	
	inline static float dot(const sf::Vector2f& A, const sf::Vector2f& B);
};


template <typename T>
inline static T Helpers::getRandom(T lower, T upper) {
	static std::random_device	rand{};
	static std::default_random_engine engine{ rand() };

	std::uniform_int_distribution dist{ static_cast<int>(lower), static_cast<int>(upper)};
	return static_cast<T>(dist(engine));
};


void Helpers::ReplaceFirstOccurance(std::string& string, std::string_view toReplace, std::string_view replaceWith)
{
	std::size_t pos = string.find(toReplace);
	if (pos == std::string::npos)
		return;

	string.replace(pos, toReplace.length(), replaceWith);
}


bool Helpers::CheckIfPointContainedInArea(const sf::Vector2f& pos, const sf::FloatRect& area)
{
	if (area.contains(pos))
		return true;
	else
		return false;
}

float Helpers::toDeg(float rad)
{
	constexpr long double M_PIl = 3.141592653589793238462643383279502884L; /* pi */

	return rad * 180.f / static_cast<float>(M_PIl);
}

float Helpers::toDeg(const sf::Vector2f& vec)
{
	return Helpers::toDeg(atan2f(vec.y, vec.x));
}

float Helpers::toRad(float deg)
{

	constexpr long double M_PIl = 3.141592653589793238462643383279502884L; /* pi */

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

	std::string line;
	while (std::getline(file, line))
		loadTo += line;
}