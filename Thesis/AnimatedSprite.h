#pragma once

#include "Animation.h"



class AnimatedSprite :
	public sf::Drawable, 
	public sf::Transformable
{
private:
	/* reference to the animation container*/
	Animation* m_Animation;
	sf::Time m_Delta;
	sf::Time m_Elapsed;
	bool m_Loop;
	/* amount of repetitions */
	int m_Repetitions;

	size_t m_CurrentFrame;
	sf::Vertex m_Vertices[4];


	sf::Vector2f m_OffsetPosition, m_Position;

	
	void setFrame(size_t index, bool resetTime);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:

	using FuncType = std::function<void()>;
	static FuncType defaultFunc;
	FuncType onFinished;
	enum Status { Stopped, Paused, Playing } m_Status;

	AnimatedSprite(AnimatedSprite&) = default;
	AnimatedSprite& operator=(AnimatedSprite&) = default;
	AnimatedSprite(AnimatedSprite&&) = default;
	AnimatedSprite& operator=(AnimatedSprite&&) = default;
	AnimatedSprite(Animation* animation = nullptr, Status status = Playing, const sf::Time& dt = sf::seconds(0.15f), bool loop = true, int repeat = 0);


	void setAnimation(Animation* animation);
	void setFrameTime(const sf::Time& dt);
	void setLoop(bool loop);
	void setRepeat(int nb);
	void setFrame(size_t index);
	void setColor(const sf::Color& color);

	Animation* getAnimation() const	{		return m_Animation;		};
	bool getLoop() const			{		return m_Loop;			};
	int getRepeat() const			{		return m_Repetitions;	};
	Status getStatus() const		{		return m_Status;		};
	sf::Vector2f getSize() const;


	void setPosition(const sf::Vector2f& pos);
	void setOffset(const sf::Vector2f& pos)	{	m_OffsetPosition = pos;	};


	/* forward time, change frame, check if end etc*/
	void update(const sf::Time& dt);
	/* set status */
	void play()		{		m_Status = Playing;		};
	/* set status */
	void pause()	{		m_Status = Paused;		};
	/* set status */
	void stop()		{		m_Status = Stopped;		};
};