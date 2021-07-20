#pragma once
#include "Widget.h"

namespace GUI
{
	class Layout;
	class Container : virtual public Widget
	{
	private:
		/* Container has a particular layout to which components are added */
		Layout* m_Layout;
		
	protected:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		virtual bool processEvent(const sf::Event& sfevent, const sf::Vector2f& parent_pos) override;
		virtual void processEvents(const sf::Vector2f& parent_pos) override;
		
		sf::RectangleShape m_Shape;

		virtual void updateShape() override;

	public:
		Container(const Container&) = delete;
		Container& operator=(const Container&) = delete;

		Container(Widget* parent = nullptr);
		virtual ~Container();

		void setLayout(Layout* layout);
		Layout* getLayout() const;

		void clear();

		void setFillColor(const sf::Color& color);
		void setOutlineColor(const sf::Color& color);
		void setOutlineThickness(float thickness);

		virtual sf::Vector2f getSize() const override;
	};

}