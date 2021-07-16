#pragma once
#include "SFML/Graphics.hpp"

namespace GUI
{
	/* Basis for other GUI components, can be moved, displayed */
	class Widget : public sf::Drawable
	{
	protected:
		friend class Containers;
		friend class VLayout;

		/* Default behavior, should be overloaded in inheriting classes */
		virtual bool processEvent(const sf::Event& sfevent, const sf::Vector2f& parent_pos);
		virtual void processEvents(const sf::Vector2f& parent_pos);
		/* If parent exists, update parent - propagates the update call through the entire tree */
		virtual void updateShape();

		/* Widget can be attached to another, so the reference to it is kept here */
		Widget* m_Parent;
		sf::Vector2f m_Position;

	public:

		Widget(Widget* parent = nullptr);
		virtual ~Widget();

		void setPosition(const sf::Vector2f& pos);
		void setPosition(float x, float y);
		const sf::Vector2f& getPosition() const;
		/* Each widget should return own size, since it depends on children */
		virtual sf::Vector2f getSize() const = 0;
	};

}