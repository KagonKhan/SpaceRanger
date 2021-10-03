#include "pch.h"
#include "Animation.h"

Animation::Animation(sf::Texture* texture)
	: m_Texture(texture)
{
}



Animation& Animation::addFrame(const sf::IntRect& rect)
{
	m_Frames.emplace_back(rect);
	return *this;
} 

/// <param name="number_x">how many frames on x axis</param>
/// <param name="number_y">how many frames on y axis</param>
/// <param name="line">start at l-th line</param>
/// <param name="offset_x">start from n-th frame</param>
/// <param name="limit_x">stop at m-th frame</param>
Animation& Animation::addFrames(Animation::Line frames)
{
	const sf::Vector2u size = m_Texture->getSize();
	const float dx = size.x / float(frames.number_x);
	const float dy = size.y / float(frames.number_y);

	for (int i = frames.offset_x; i < frames.number_x - frames.limit_x; ++i)
		addFrame(sf::IntRect(i * dx, frames.line * dy, dx, dy));
	return *this;
}

/// <param name="number_x">how many frames on x axis</param>
/// <param name="number_y">how many frames on y axis</param>
/// <param name="column">start at l-th column</param>
/// <param name="offset_y">start from n-th frame</param>
/// <param name="limit_y">stop at m-th frame</param>
Animation& Animation::addFrames(Animation::Column frames)
{
	const sf::Vector2u size = m_Texture->getSize();
	const float dx = size.x / float(frames.number_x);
	const float dy = size.y / float(frames.number_y);

	for (int i = frames.offset_y; i < frames.number_y - frames.limit_y; ++i)
		addFrame(sf::IntRect(frames.column * dx, i * dy, dx, dy));

	return *this;
}
