#pragma once

class Animation
{
private:
	friend class AnimatedSprite;
	/* frames */
	std::vector<sf::IntRect> m_Frames;
	sf::Texture* m_Texture;

public:
	Animation(sf::Texture* texture = nullptr);

	/* emplace back a frame */
	Animation& addFrame(const sf::IntRect& rect);


	struct Line		{ int number_x, number_y, line,	  offset_x{ 0 }, limit_x{ 0 }; };
	struct Column	{ int number_x, number_y, column, offset_y{ 0 }, limit_y{ 0 }; };
	Animation& addFrames(Line frames);
	Animation& addFrames(Column frames);


	void setTexture(sf::Texture* texture)				{		m_Texture = texture;		};
	sf::Texture* getTexture() const						{		return m_Texture;			};
	size_t size() const									{		return m_Frames.size();		};
	const sf::IntRect& getRect(size_t index) const		{		return m_Frames[index];		};
};