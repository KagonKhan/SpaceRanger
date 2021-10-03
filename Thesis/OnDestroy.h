#pragma once
#include "AnimatedSprite.h"

class Entity;
class OnDestroy	:
	public sf::Drawable
{
private:
	void draw(sf::RenderTarget& target, sf::RenderStates) const override;


	bool m_CanBeDeleted{ false };
	bool m_MarkedForDeletion{ false };
	std::function<void(const sf::Time&)> deathFunction;

	std::optional<Animation>		m_DeathAnimation;
	std::optional<AnimatedSprite>	m_DeathAnimatedSprite;
	std::optional<sf::Sound>		m_DeathSound;

	Entity&			m_Parent;


	bool isSoundDone()	const;
	bool isAnimationDone()	const;
	bool isShipEventsDone()	const;

	void updateDeathEvents(const sf::Time& deltaTime);
	void checkCanBeDeleted();

public:
	explicit OnDestroy(Entity& parent);

	void initAnimation(sf::Texture* animation, std::variant<Animation::Line, Animation::Column> addFrames, sf::Time frameTime, sf::Vector2f scale);
	void addFrames(std::variant<Animation::Line, Animation::Column> frames);
	void initSound(const sf::SoundBuffer& sound);


	void update(const sf::Time& deltaTime);

	void start(bool forceDelete = false);

	bool canBeDeleted() const			{	return m_CanBeDeleted;			}
	bool isMarkedForDeletion() const	{	return m_MarkedForDeletion;		}

};