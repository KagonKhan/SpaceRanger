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

Animation& Animation::addFramesLine(int number_x, int number_y, int line)
{
	const sf::Vector2u size = m_Texture->getSize();
	const float dx = size.x / float(number_x);
	const float dy = size.y / float(number_y);

	for (int i = 0; i < number_x; ++i)
		addFrame(sf::IntRect(i * dx, line * dy, dx, dy));
	return *this;
}

Animation& Animation::addFramesColumn(int number_x, int number_y, int column)
{
	const sf::Vector2u size = m_Texture->getSize();
	const float dx = size.x / float(number_x);
	const float dy = size.y / float(number_y);

	for (int i = 0; i < number_y; ++i)
		addFrame(sf::IntRect(column * dx, i * dy, dx, dy));

	return *this;
}
