#include "pch.h"
#include "Spline.h"

Spline::Spline(const std::vector<sf::Vector2f>& waypoints, float precision, bool isLooped)
	: m_Looped(isLooped), m_Precision(precision)
{
	m_WayPoints = waypoints;
	calculateSplinePoints(waypoints, precision, isLooped);
}

void Spline::calculateSplinePoints(const std::vector<sf::Vector2f>& waypoints, float precision, bool looped)
{
	float size = static_cast<float>(waypoints.size());

	size += looped ? 0.f : -3.f;

	for (float t = 0.f; t < size; t += precision)
		m_Points.push_back(getSplinePoint(waypoints, t, looped));

}

sf::Vector2f Spline::getSplinePoint(const std::vector<sf::Vector2f>& waypoints, float t, bool looped)
{
	int p0;
	int p1;
	int p2;
	int p3;

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

	t = t - std::floorf(t);

	float tt = t * t;
	float ttt = t * tt;



	/* Derivative for the gradient */
	float q1 = -3.f * tt + 4.f * t - 1.f;
	float q2 = 9.f * tt - 10.f * t;
	float q3 = -9.f * tt + 8.f * t + 1.f;
	float q4 = 3.f * tt - 2.f * t;

	float tx = 0.5f * waypoints[p0].x * q1 + waypoints[p1].x * q2 + waypoints[p2].x * q3 + waypoints[p3].x * q4;
	float ty = 0.5f * waypoints[p0].y * q1 + waypoints[p1].y * q2 + waypoints[p2].y * q3 + waypoints[p3].y * q4;
	m_Gradients.emplace_back(tx, ty);
	

	/* Spline points */
	q1 = -ttt + 2.f * tt - t;
	q2 = 3.f * ttt - 5.f * tt + 2.f;
	q3 = -3.f * ttt + 4.f * tt + t;
	q4 = ttt - tt;

	tx = waypoints[p0].x * q1 + waypoints[p1].x * q2 + waypoints[p2].x * q3 + waypoints[p3].x * q4;
	ty = waypoints[p0].y * q1 + waypoints[p1].y * q2 + waypoints[p2].y * q3 + waypoints[p3].y * q4;

	return { 0.5f * tx, 0.5f * ty };
}

void Spline::setWaypoints(const std::vector<sf::Vector2f>& waypoints)
{
	m_Points.clear();
	m_Gradients.clear();
	m_WayPoints.clear();
	m_WayPoints = waypoints;
	calculateSplinePoints(waypoints, m_Precision, m_Looped);
}

sf::Vector2f Spline::getNextPoint()
{
	sf::Vector2f retval;

	if (m_Index <= static_cast<int>(m_Points.size()) - 1) {
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

Spline Spline::getMirroredPath(bool mirrorByX)
{
	std::vector<sf::Vector2f>	mirrored_waypoints;

	for (auto point : m_WayPoints)
	{
		static float maxX = Configuration::boundaries.x;
		sf::Vector2f pnt(maxX - point.x, point.y);
		mirrored_waypoints.push_back(pnt);
	}

	Spline result(mirrored_waypoints, m_Precision, m_Looped);
	
	return result;
}
