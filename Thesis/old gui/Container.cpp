#include "Container.h"
#include "Layout.h"

namespace GUI
{
	Container::Container(Widget* parent)
		: Widget(parent), m_Layout(nullptr)
	{

	}

	Container::~Container()
	{
		if (m_Layout != nullptr && m_Layout->m_Parent == this) {
			m_Layout->m_Parent = nullptr;
			delete m_Layout;
		}
	}

	void Container::setLayout(Layout* layout)
	{
		if (m_Layout != nullptr && m_Layout->m_Parent == this) {
			m_Layout->m_Parent = nullptr;
			delete m_Layout;
		}
		if ((m_Layout = layout) != nullptr) {
			m_Layout->m_Parent = this;
		}
	}


	void Container::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{

		target.draw(*m_Layout, states);
		
	}

	
}