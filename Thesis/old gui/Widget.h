#pragma once
#include "SFML/Graphics.hpp"

namespace GUI
{
	/* Basis for other GUI components, can be moved, displayed */
	class Widget : public sf::Drawable
	{
	protected:
		friend class Container;
		friend class VLayout;
		friend class HLayout;

		/* Widget can be attached to another, so the reference to it is kept here */
		Widget* m_Parent;


	public:
		Widget(const Widget&) = delete;
		Widget& operator=(const Widget&) = delete;

		Widget(Widget* parent = nullptr);
		virtual ~Widget();

	};

}