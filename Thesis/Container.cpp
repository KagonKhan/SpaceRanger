#include "Container.h"

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
		if (m_Layout != nullptr && m_Layout->m_Parent == this)
			m_Layout->m_Parent = nullptr;
		if ((m_Layout = layout) != nullptr) {
			m_Layout->m_Parent = this;
			m_Layout->updateShape();
		}
	}

	Layout* Container::getLayout() const
	{
		return m_Layout;
	}

	sf::Vector2f Container::getSize() const
	{
		sf::Vector2f res(0, 0);
		if (m_Layout)
			res = m_Layout->getSize();

		return res;
	}

	void Container::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		if (m_Layout)
			target.draw(*m_Layout, states);
	}

	bool Container::processEvent(const sf::Event& sfevent, const sf::Vector2f& parent_pos)
	{
		bool res = false;
		if (m_Layout)
			res = m_Layout->processEvent(sfevent, parent_pos);

		return res;
	}

	void Container::processEvents(const sf::Vector2f& parent_pos)
	{
		if (m_Layout)
			m_Layout->processEvents(parent_pos);
	}
}