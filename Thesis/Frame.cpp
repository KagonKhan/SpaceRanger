#include "Frame.h"

namespace GUI
{
	Frame::Frame(sf::RenderWindow& window)
		: Container(nullptr), ActionTarget(Configuration::gui_inputs), m_Window(window)
	{

	}

	Frame::~Frame()
	{
	}

	void Frame::processEvents()
	{
		sf::Vector2f parent_pos(0, 0);
		processEvents(parent_pos);
	}

	bool Frame::processEvent(const sf::Event& sfevent)
	{
		return false;
	}

	void Frame::processEvents(const sf::Vector2f& parent_pos)
	{
		ActionTarget::processEvents();
		Container::processEvents(parent_pos);

		sf::Event sfevent;
		while (m_Window.pollEvent(sfevent))
			Container::processEvent(sfevent, parent_pos);
	}

	/* TODO: check validity */
	bool Frame::processEvent(const sf::Event& sfevent, const sf::Vector2f& parent_pos)
	{
		bool res = ActionTarget::processEvent(sfevent);
		if (not res)
			res = Container::processEvent(sfevent, parent_pos);
		return res;
	}

	void Frame::bind(int key, const FuncType& callback)
	{
		ActionTarget::bind(key, callback);
	}

	void Frame::unbind(int key)
	{
		ActionTarget::unbind(key);
	}

	void Frame::draw()
	{
		m_Window.draw(*this);
	}

	sf::Vector2f Frame::getSize() const
	{	
		return static_cast<sf::Vector2f>(m_Window.getSize());
	}

}
