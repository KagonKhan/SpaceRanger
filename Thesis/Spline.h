#pragma once

class Spline
{
private:
	std::vector<sf::Vector2f> m_Points;
	std::vector<sf::Vector2f> m_Gradients;
	int m_Index, m_Laps;
	bool m_Looped, m_Done;
	float m_Precision;


	sf::Vector2f getSplinePoint(const std::vector<sf::Vector2f>& waypoints, float t, bool looped = false);
	void calculateSplinePoints(const std::vector<sf::Vector2f>& waypoints, float precision, bool looped);

public:
	explicit Spline(const std::vector<sf::Vector2f>& waypoints, float precision = 0.01f, bool isLooped = false);

	void setWaypoints(const std::vector<sf::Vector2f>& waypoints);

	sf::Vector2f getNextPoint();


	int getLaps() const								{		return m_Laps;											}
	bool isDone()const								{		return m_Done;											}
	const std::vector<sf::Vector2f>& getPath()const {		return m_Points;										}
	sf::Vector2f getGradient()						{		return m_Gradients[m_Index];							}
	float getAngle() const { std::cout << "\nindex: " << m_Index;		return Helpers::toDeg(m_Gradients[m_Index]); }
};
