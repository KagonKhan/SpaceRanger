#pragma once
/* 
	Class inspired by works of @Javidx9
	and their works on youtube: https://youtu.be/9_aJGUTePYo


	modified for personal needs
*/


class Spline
{
private:
	std::vector<sf::Vector2f>	m_Points;
	std::vector<sf::Vector2f>	m_WayPoints;
	std::vector<sf::Vector2f>	m_Gradients;
	int							m_Index		{ 0 };
	int							m_Laps		{ 0 };
	bool						m_Done		{ false };
	bool						m_Looped;
	float						m_Precision;


	sf::Vector2f getSplinePoint(const std::vector<sf::Vector2f>& waypoints, float t, bool looped = false);
	void calculateSplinePoints(const std::vector<sf::Vector2f>& waypoints, float precision, bool looped);

public:
	explicit Spline(const std::vector<sf::Vector2f>& waypoints, float precision = 0.01f, bool isLooped = false);

	void setWaypoints(const std::vector<sf::Vector2f>& waypoints);

	sf::Vector2f getNextPoint();
	Spline getMirroredPath(bool mirrorByX);

	//////
	/// Returns number of laps made around the path
	//////
	int getLaps() const								{		    return m_Laps;										}
	bool isDone() const								{		    return m_Done;										}
	//////
	/// Returns the path as a vector of 2D points
	//////	
	const std::vector<sf::Vector2f>& getPath()const {		    return m_Points;									}
	sf::Vector2f getGradient()						{		    return m_Gradients[m_Index];						}
	sf::Vector2f getCurrent()						{		    return m_Points[m_Index];							}

	//////
	/// Returns float precision value of the angle on the path
	/// allows for accurate sprite rotations while following the path
	//////	
	float getAngle() const							{		    return Helpers::toDeg(m_Gradients[m_Index]);		}		
};

