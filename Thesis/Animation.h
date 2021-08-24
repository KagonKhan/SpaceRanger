#pragma once

class Animation
{
private:
	friend class AnimatedSprite;
	/* frames */
	std::vector<sf::IntRect> m_Frames;
	/* reference to the texture */
	sf::Texture* m_Texture;

public:
	Animation(sf::Texture* texture = nullptr);
	~Animation();

	/* assign existing texture */
	void setTexture(sf::Texture* texture);
	/* return current texture */
	sf::Texture* getTexture() const;

	/* emplace back a frame */
	Animation& addFrame(const sf::IntRect& rect);
	/* add many horizontal frames */
	Animation& addFramesLine(int number_x, int number_y, int line, int offset_x = 0, int limit_x = 0);
		/* add many vertical frames */
	Animation& addFramesColumn(int number_x, int number_y, int column, int offset_y = 0, int limit_y = 0);

	/* get amount of frames */
	size_t size() const;
	/* return frame at index */
	const sf::IntRect& getRect(size_t index) const;
};