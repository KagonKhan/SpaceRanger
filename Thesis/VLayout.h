#pragma once
#include "Layout.h"
namespace GUI
{
	class VLayout : public Layout
	{
	private:
		std::vector<Widget*> m_Widgets;

		virtual void updateShape() override;
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	protected:
		virtual bool processEvent(const sf::Event& sfevent, const sf::Vector2f& parent_pos) override;
		virtual void processEvents(const sf::Vector2f& parent_pos) override;

	public:
		VLayout(const VLayout&) = delete;
		VLayout& operator=(const VLayout&) = delete;
		
		VLayout(Widget* parent = nullptr);
		~VLayout();

		void add(Widget* widget);
		Widget* at(unsigned int index) const;
		virtual sf::Vector2f getSize() const override;
	};

}