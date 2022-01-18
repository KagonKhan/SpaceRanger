#include "pch.h"
#include "AnimatedSprite.h"

AnimatedSprite::FuncType AnimatedSprite::defaultFunc = []()->void {};

AnimatedSprite::AnimatedSprite(Animation* animation, Status status, const sf::Time& dt, bool loop, int repeat)
	: onFinished(defaultFunc), m_Delta(dt), m_Loop(loop), m_Repetitions(repeat), m_Status(status)
{
	setAnimation(animation);
}

void AnimatedSprite::setFrame(size_t index, bool resetTime)
{
	if (m_Animation) {
		sf::IntRect rect = m_Animation->getRect(index);

		m_Vertices[0].position = sf::Vector2f(0.f, 0.f);
		m_Vertices[1].position = sf::Vector2f(0.f, rect.height);
		m_Vertices[2].position = sf::Vector2f(rect.width, rect.height);
		m_Vertices[3].position = sf::Vector2f(rect.width, 0.f);

		float left	 =   static_cast<float>(rect.left);
		float right  =  static_cast<float>(left + rect.width);
		float top	 = static_cast<float>(rect.top);
		float bottom = static_cast<float>(top + rect.height);

		m_Vertices[0].texCoords = sf::Vector2f(left, top);
		m_Vertices[1].texCoords = sf::Vector2f(left, bottom); 
		m_Vertices[2].texCoords = sf::Vector2f(right, bottom);
		m_Vertices[3].texCoords = sf::Vector2f(right, top);

	}
	if (resetTime)
		m_Elapsed = sf::Time::Zero;
}

void AnimatedSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (m_Animation && m_Animation->m_Texture) {
		states.transform *= getTransform();
		states.texture = m_Animation->m_Texture;
		target.draw(m_Vertices, 4, sf::Quads, states);
	}
}

void AnimatedSprite::setAnimation(Animation* animation)
{
	if (m_Animation != animation) {
		m_Animation = animation;
		m_Elapsed = sf::Time::Zero;
		m_CurrentFrame = 0;
		setFrame(0, true);
	}
}

void AnimatedSprite::setFrameTime(const sf::Time& dt)
{
	m_Delta = dt;
}

void AnimatedSprite::setLoop(bool loop)
{
	m_Loop = loop;
}

void AnimatedSprite::setRepeat(int nb)
{
	m_Repetitions = nb;
}

void AnimatedSprite::setFrame(size_t index)
{
	assert(m_Animation);
	m_CurrentFrame = index % m_Animation->size();
	setFrame(m_CurrentFrame, true);
}

void AnimatedSprite::setColor(const sf::Color& color)
{
	m_Vertices[0].color = color;
	m_Vertices[1].color = color;
	m_Vertices[2].color = color;
	m_Vertices[3].color = color;
}

sf::Vector2f AnimatedSprite::getSize() const
{
	sf::IntRect rect = m_Animation->getRect(0);
	return sf::Vector2f(rect.width, rect.height);
}

void AnimatedSprite::setPosition(const sf::Vector2f& pos)
{
	m_Position = pos;
	Transformable::setPosition(m_Position + m_OffsetPosition);

}

void AnimatedSprite::update(const sf::Time& dt)
{ 
	if (m_Status == Playing && m_Animation) {
		m_Elapsed += dt;

		if (m_Elapsed > m_Delta) {
			m_Elapsed -= m_Delta;

			if (m_CurrentFrame + 1 < m_Animation->size())
				++m_CurrentFrame;
			else if (m_Loop || m_Repetitions > 0) {
				m_CurrentFrame = 0;

				if (!m_Loop) {
					--m_Repetitions;

					if (m_Repetitions <= 0) {
						m_Status = Stopped;

						onFinished();
						return;
					}
				}
			}
			else
				m_Status = Stopped;
		}
		setFrame(m_CurrentFrame, false);
	}
}
