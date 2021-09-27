#pragma once
#include "Ship.h"


class Spline
{
private:
	std::vector<sf::Vector2f> m_Points;
	std::vector<sf::Vector2f> m_Gradients;
	int m_Index, m_Laps;
	bool m_Looped, m_Done;
	float m_Precision;


	sf::Vector2f getSplineGradient(const std::vector<sf::Vector2f>& waypoints, float t, bool looped = false) {

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

		float q1 = -3.f * tt + 4.f * t - 1.f;
		float q2 = 9.f * tt - 10.f * t;
		float q3 = -9.f * tt + 8.f * t + 1.f;
		float q4 = 3.f * tt - 2.f * t;

		float tx = waypoints[p0].x * q1 + waypoints[p1].x * q2 + waypoints[p2].x * q3 + waypoints[p3].x * q4;
		float ty = waypoints[p0].y * q1 + waypoints[p1].y * q2 + waypoints[p2].y * q3 + waypoints[p3].y * q4;

		return { 0.5f * tx, 0.5f * ty };
	}


	sf::Vector2f getSplinePoint(const std::vector<sf::Vector2f>& waypoints, float t, bool looped = false) {

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

		float q1 = -ttt + 2.f * tt - t;
		float q2 = 3.f * ttt - 5.f * tt + 2.f;
		float q3 = -3.f * ttt + 4.f * tt + t;
		float q4 = ttt - tt;

		float tx = waypoints[p0].x * q1 + waypoints[p1].x * q2 + waypoints[p2].x * q3 + waypoints[p3].x * q4;
		float ty = waypoints[p0].y * q1 + waypoints[p1].y * q2 + waypoints[p2].y * q3 + waypoints[p3].y * q4;

		return { 0.5f * tx, 0.5f * ty };
	}

	void calculateSplinePoints(const std::vector<sf::Vector2f>& waypoints, float precision, bool looped) {
		float size = (float)waypoints.size();

		size += looped ? 0 : -3;

		for (float t = 0.f; t < size; t += precision) {
			m_Points.push_back(getSplinePoint(waypoints, t, looped));
			m_Gradients.push_back(getSplineGradient(waypoints, t, looped));
		}
	}

public:
	explicit Spline(const std::vector<sf::Vector2f>& waypoints, float precision = 0.01f, bool isLooped = false)
		: m_Index(0), m_Looped(isLooped), m_Done(false), m_Precision(precision), m_Laps(0) {
		calculateSplinePoints(waypoints, precision, isLooped);
	}

	bool isDone()const { return m_Done; }
	const std::vector<sf::Vector2f>& getPath()const { return m_Points; }
	int getLaps() const { return m_Laps; }



	void setWaypoints(const std::vector<sf::Vector2f>& waypoints) {
		m_Points.clear();
		m_Gradients.clear();
		calculateSplinePoints(waypoints, m_Precision, m_Looped);
	}

	sf::Vector2f getPoint(std::optional<int> index = std::nullopt) {

		sf::Vector2f retval;
		if (index.has_value()) {
			retval = m_Points[index.value()];
		}
		else {
			if (m_Index <= m_Points.size() - 1) {
				retval = m_Points[m_Index];
				++m_Index;
			}

			if (m_Looped) {
				m_Index %= m_Points.size();
				++m_Laps;
			}
			else if (m_Index == m_Points.size() - 1)
				m_Done = true;
		}
		return retval;
	}
	sf::Vector2f getGradient() {
		return m_Gradients[m_Index];
	}
};



class EnemyShip :
	public Ship
{
private:


public:
	EnemyShip(float maxHp, Configuration::TexturesShips tex_id);
	virtual ~EnemyShip();

	typedef std::unique_ptr<EnemyShip> ptr;
};