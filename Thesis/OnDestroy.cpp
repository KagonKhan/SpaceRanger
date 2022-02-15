#include "pch.h"
#include "OnDestroy.h"

#include "BeamShip.h"
#include "Ammunition.h"




void OnDestroy::draw(sf::RenderTarget& target, sf::RenderStates) const
{
	if(m_DeathAnimatedSprite.has_value() && m_DeathAnimatedSprite.value().getStatus() == AnimatedSprite::Status::Playing)
		target.draw(m_DeathAnimatedSprite.value());
}


OnDestroy::OnDestroy(Entity& parent)
	: m_Parent(parent)
{
}

void OnDestroy::initAnimation(sf::Texture* animation, std::variant<Animation::Line, Animation::Column> addFrames, sf::Time frameTime, sf::Vector2f scale)
{
	m_DeathAnimation.emplace(animation);
	auto& anim = m_DeathAnimation.value();

	// Possibly change impl in animation to accept variants, reducing code
	if (auto result = std::get_if<Animation::Line>(&addFrames); result != nullptr)
		anim.addFrames(*result);
	if (auto result = std::get_if<Animation::Column>(&addFrames); result != nullptr)
		anim.addFrames(*result);


	m_DeathAnimatedSprite.emplace(&anim, AnimatedSprite::Paused, frameTime, false, 0);
	auto& sprite = m_DeathAnimatedSprite.value();

	sprite.setOrigin(sprite.getSize() / 2.f);
	sprite.setScale(scale);
}

void OnDestroy::addFrames(std::variant<Animation::Line, Animation::Column> frames)
{
	auto& anim = m_DeathAnimation.value();

	// Possibly change impl in animation to accept variants, reducing code
	if (auto result = std::get_if<Animation::Line>(&frames); result != nullptr)
		anim.addFrames(*result);
	if (auto result = std::get_if<Animation::Column>(&frames); result != nullptr)
		anim.addFrames(*result);

}

void OnDestroy::initSound(const sf::SoundBuffer& sound)
{
	m_DeathSound.emplace(sound);
}



void OnDestroy::start(bool forceDelete)
{
	m_MarkedForDeletion = true;
	if (forceDelete) {
		m_CanBeDeleted = true;
		return;
	}


	sf::Vector2f position = m_Parent.getPosition();
	if (m_DeathAnimatedSprite.has_value()) {
		auto& sprite = m_DeathAnimatedSprite.value();
		sprite.setPosition(position);
		sprite.play();
	}
	if (m_DeathSound.has_value()) {
		auto& sound = m_DeathSound.value();
		
		sound.setPosition(position.x, -position.y, 0.f);
		sound.setVolume(50);
		sound.setAttenuation(1);
		sound.setMinDistance(std::sqrtf(200.f * 200.f + 300.f * 300.f));

		sound.play();
	}
	if (auto ship = dynamic_cast<Ship*>(&m_Parent); ship != nullptr) {
		ship->setPosition(-99.f, -99.f);
		ship->setAreActionsBlocked(true);

		if (auto beamship = dynamic_cast<BeamShip*>(&m_Parent); beamship != nullptr) {
			beamship->stopShooting();
		}
	}
}

void OnDestroy::update(const sf::Time& deltaTime)
{
	updateDeathEvents(deltaTime);
}

void OnDestroy::updateDeathEvents(const sf::Time& deltaTime)
{
	if (m_DeathAnimatedSprite.has_value() && isAnimationDone() == false)
		m_DeathAnimatedSprite.value().update(deltaTime);

	checkCanBeDeleted();

}

void OnDestroy::checkCanBeDeleted()
{
	m_CanBeDeleted = true;

	if (!isAnimationDone()) {
		m_CanBeDeleted = false;
		return;
	}
	if (!isSoundDone()) {
		m_CanBeDeleted = false;
		return;
	}

	if (!isShipEventsDone()) {
		m_CanBeDeleted = false;

		return;
	}
}


bool OnDestroy::isSoundDone()	const
{
	if (!m_DeathSound.has_value())
		return true;

	if(m_DeathSound.value().getStatus() == sf::Sound::Status::Stopped)
		return true;

	return false;
}

bool OnDestroy::isAnimationDone()	const
{
	if (!m_DeathAnimatedSprite.has_value())
		return true;

	if (m_DeathAnimatedSprite.value().getStatus() == AnimatedSprite::Status::Playing)
		return false;


	return true;
}

bool OnDestroy::isShipEventsDone()	const
{
	if (auto ship = dynamic_cast<Ship*>(&m_Parent); ship != nullptr) {
		if (ship->getAmmoOnScreen().empty())
			return true;
		else
			return false;
	}
	else
		return true;
}
