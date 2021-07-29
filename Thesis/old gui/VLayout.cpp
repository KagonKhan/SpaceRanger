#include "VLayout.h"

namespace GUI
{
	GUI::VLayout::VLayout(Widget* parent)
		: Layout(parent)
	{

	}

	GUI::VLayout::~VLayout()
	{
	
	}



	Widget* GUI::VLayout::at(unsigned int index) const
	{
		return m_Widgets.at(index);
	}

	void GUI::VLayout::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		for (Widget* widget : m_Widgets)
			target.draw(*widget, states);
	}
}