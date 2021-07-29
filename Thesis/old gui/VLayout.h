#pragma once
#include "Layout.h"
namespace GUI
{
	class VLayout : public Layout
	{
	private:
		std::vector<Widget*> m_Widgets;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


	public:
		VLayout(const VLayout&) = delete;
		VLayout& operator=(const VLayout&) = delete;
		
		VLayout(Widget* parent = nullptr);
		~VLayout();

		void add(Widget* widget);
		Widget* at(unsigned int index) const;
	
	};

}