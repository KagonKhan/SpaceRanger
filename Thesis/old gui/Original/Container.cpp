#include "Container.h"
#include "Layout.h"

namespace GUI
{
	Container::Container(Widget* parent)
		: Widget(parent), m_Layout(nullptr)
	{
		setFillColor(sf::Color(255, 255, 255, 0));
		setOutlineColor(sf::Color(255, 255, 255, 0));
		setOutlineThickness(0);
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
			m_Layout->updateShape();
		}
	}

	Layout* Container::getLayout() const
	{
		return m_Layout;
	}

	void Container::clear()
	{
		if (m_Layout) {
			m_Layout->clear();
			updateShape();
		}
	}

	void Container::setFillColor(const sf::Color& color)
	{
		m_Shape.setFillColor(color);
	}
	void Container::setOutlineColor(const sf::Color& color)
	{
		m_Shape.setOutlineColor(color);
	}
	void Container::setOutlineThickness(float thickness)
	{
		m_Shape.setOutlineThickness(thickness);
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
		if (m_IsVisible && m_Layout) {
			states.transform.translate(m_Position);
			target.draw(m_Shape, states);
			target.draw(*m_Layout, states);
		}
	}

	bool Container::processEvent(const sf::Event& sfevent, const sf::Vector2f& parent_pos)
	{
		bool res = false;
		if (m_IsVisible && m_Layout)
			res = m_Layout->processEvent(sfevent, m_Position + parent_pos);

		return res;
	}

	void Container::processEvents(const sf::Vector2f& parent_pos)
	{
		if (m_IsVisible && m_Layout)
			m_Layout->processEvents(m_Position + parent_pos);
	}

	void Container::updateShape()
	{
		m_Shape.setSize(getSize());
		Widget::updateShape();
	}
} 