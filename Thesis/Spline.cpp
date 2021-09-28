#include "pch.h"
#include "Spline.h"

sf::Vector2f Spline::getSplinePoint(const std::vector<sf::Vector2f>& waypoints, float t, bool looped)
{
	int p0, p1, p2, p3;
	if (looped) {
		p1 = (int)t;
		p2 = (p1 + 1) % waypoints.size();
		p3 = (p2 + 1) % waypoints.size();
		p0 = (p1 >= 1) ? (p1 - 1) : (waypoints.size() - 1);
	}
	else {
		p1 = (int)t + 1;
		p2 = p1 + 1;
		p3 = p2 + 1;
		p0 = p1 - 1;
	}

	t = t - (int)t;

	float tt = t * t;
	float ttt = t * tt;



	/* Derivative for the gradient */
	{
		float q1 = -3.f * tt + 4.f * t - 1.f;
		float q2 = 9.f * tt - 10.f * t;
		float q3 = -9.f * tt + 8.f * t + 1.f;
		float q4 = 3.f * tt - 2.f * t;

		float tx = 0.5f * waypoints[p0].x * q1 + waypoints[p1].x * q2 + waypoints[p2].x * q3 + waypoints[p3].x * q4;
		float ty = 0.5f * waypoints[p0].y * q1 + waypoints[p1].y * q2 + waypoints[p2].y * q3 + waypoints[p3].y * q4;
		m_Gradients.emplace_back(tx, ty);
	}



	float q1 = -ttt + 2.f * tt - t;
	float q2 = 3.f * ttt - 5.f * tt + 2.f;
	float q3 = -3.f * ttt + 4.f * tt + t;
	float q4 = ttt - tt;

	float tx = waypoints[p0].x * q1 + waypoints[p1].x * q2 + waypoints[p2].x * q3 + waypoints[p3].x * q4;
	float ty = waypoints[p0].y * q1 + waypoints[p1].y * q2 + waypoints[p2].y * q3 + waypoints[p3].y * q4;

	return { 0.5f * tx, 0.5f * ty };
}

void Spline::calculateSplinePoints(const std::vector<sf::Vector2f>& waypoints, float precision, bool looped)
{
	float size = (float)waypoints.size();

	size += looped ? 0 : -3;

	for (float t = 0.f; t < size; t += precision) 
		m_Points.push_back(getSplinePoint(waypoints, t, looped));

	std::cout << m_Gradients.size() << " : " << m_Points.size() << "\n";
	system("PAUSE");

}

Spline::Spline(const std::vector<sf::Vector2f>& waypoints, float precision, bool isLooped)
	: m_Index(0), m_Looped(isLooped), m_Done(false), m_Precision(precision), m_Laps(0)
{
	calculateSplinePoints(waypoints, precision, isLooped);
}


void Spline::setWaypoints(const std::vector<sf::Vector2f>& waypoints)
{
	m_Points.clear();
	m_Gradients.clear();
	calculateSplinePoints(waypoints, m_Precision, m_Looped);
}

sf::Vector2f Spline::getNextPoint()
{
	sf::Vector2f retval;

	if (m_Index <= m_Points.size() - 1) {
		retval = m_Points[m_Index];
		++m_Index;
	}

	if (m_Looped) {
		m_Index %= m_Points.size();
		++m_Laps;
	}
	else if (m_Index == m_Points.size() - 1) {
		m_Done = true;
		--m_Index;
	}
	
	return retval;
}
