#include "pch.h"
#include "Animation.h"

Animation::Animation(sf::Texture* texture)
	: m_Texture(texture)
{
}

Animation::~Animation()
{
}

void Animation::setTexture(sf::Texture* texture)
{
	m_Texture = texture;
}

sf::Texture* Animation::getTexture() const
{
	return m_Texture;
}

const sf::IntRect& Animation::getRect(size_t index) const
{
	return m_Frames[index];
}

size_t Animation::size() const
{
	return m_Frames.size();
}

Animation& Animation::addFrame(const sf::IntRect& rect)
{
	m_Frames.emplace_back(rect);
	return *this;
}
/// <summary>
/// 
/// </summary>
/// <param name="number_x">how many frames on x axis</param>
/// <param name="number_y">how many frames on y axis</param>
/// <param name="line">start at l-th line</param>
/// <param name="offset_x">start from n-th frame</param>
/// <param name="limit_x">stop at m-th frame</param>
/// <returns></returns>
Animation& Animation::addFramesLine(int number_x, int number_y, int line, int offset_x, int limit_x)
{
	const sf::Vector2u size = m_Texture->getSize();
	const float dx = size.x / float(number_x);
	const float dy = size.y / float(number_y);

	for (int i = offset_x; i < number_x - limit_x; ++i)
		addFrame(sf::IntRect(i * dx, line * dy, dx, dy));
	return *this;
}
/// <summary>
/// 
/// </summary>
/// <param name="number_x">how many frames on x axis</param>
/// <param name="number_y">how many frames on y axis</param>
/// <param name="column">start at l-th column</param>
/// <param name="offset_y">start from n-th frame</param>
/// <param name="limit_y">stop at m-th frame</param>
/// <returns></returns>
Animation& Animation::addFramesColumn(int number_x, int number_y, int column, int offset_y, int limit_y)
{
	const sf::Vector2u size = m_Texture->getSize();
	const float dx = size.x / float(number_x);
	const float dy = size.y / float(number_y);

	for (int i = offset_y; i < number_y - limit_y; ++i)
		addFrame(sf::IntRect(column * dx, i * dy, dx, dy));

	return *this;
}
