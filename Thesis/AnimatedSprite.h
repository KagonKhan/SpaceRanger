#pragma once

#include "Animation.h"



class AnimatedSprite : public sf::Drawable, public sf::Transformable
{
private:
	/* reference to the animation container*/
	Animation* m_Animation;
	sf::Time m_Delta;
	sf::Time m_Elapsed;
	bool m_Loop;
	/* amount of repetitions */
	int m_Repetitions;

	enum Status : int;
	Status m_Status;

	size_t m_CurrentFrame;
	sf::Vertex m_Vertices[4];

	void setFrame(size_t index, bool resetTime);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:

	using FuncType = std::function<void()>;
	static FuncType defaultFunc;
	FuncType onFinished;
	enum Status { Stopped, Paused, Playing };

	AnimatedSprite(const AnimatedSprite&) = default;
	AnimatedSprite& operator=(const AnimatedSprite&) = default;
	AnimatedSprite(AnimatedSprite&&) = default;
	AnimatedSprite& operator=(AnimatedSprite&&) = default;
	AnimatedSprite(Animation* animation = nullptr, Status status = Playing, const sf::Time& dt = sf::seconds(0.15), bool loop = true, int repeat = 0);


	void setAnimation(Animation* animation);
	void setFrameTime(const sf::Time& dt);
	void setLoop(bool loop);
	void setRepeat(int nb);
	void setFrame(size_t index);
	void setColor(const sf::Color& color);

	Animation* getAnimation() const;
	bool getLoop() const;
	int getRepeat() const;
	Status getStatus() const;
	const sf::Vector2f& getSize() const;

	/* forward time, change frame, check if end etc*/
	void update(const sf::Time& dt);
	/* set status */
	void play();
	/* set status */
	void pause();
	/* set status */
	void stop();
};