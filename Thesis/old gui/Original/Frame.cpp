#include "Frame.h"
#include "Configuration.h"

namespace GUI
{
	/* TODO: change later*/
	Frame::Frame(sf::RenderWindow& window)
		: Container(nullptr), ActionTarget(Configuration::gui_inputs), m_Window(window)
	{

	}

	Frame::~Frame()
	{
	}

	void Frame::processEvents()
	{
		processEvents(sf::Vector2f(0, 0));
	}

	bool Frame::processEvent(const sf::Event& sfevent)
	{
		return processEvent(sfevent, sf::Vector2f(0,0));
	}

	void Frame::processEvents(const sf::Vector2f& parent_pos)
	{

		if (m_IsVisible) {
			ActionTarget::processEvents();
			Container::processEvents(parent_pos);
		}
		
	}

	void Frame::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		if (m_IsVisible) {
			sf::View view = target.getView();
			target.setView(m_View);

			Container::draw(target, states);

			target.setView(view);
		}
	}

	/* TODO: check validity */
	bool Frame::processEvent(const sf::Event& sfevent, const sf::Vector2f& parent_pos)
	{
		bool res = false;
		if (m_IsVisible) {
			res = ActionTarget::processEvent(sfevent);
			if(!res)
				res = Container::processEvent(sfevent, parent_pos);
		}
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
		sf::Vector2f res = m_Size;
		sf::Vector2u wsize = m_Window.getSize();
		if (m_Size.x <= 0)
			res.x += wsize.x;
		if (m_Size.y <= 0)
			res.y += wsize.y;

		return res;
	}

	void Frame::setSize(const sf::Vector2f& size)
	{
		m_Size = size;
	}

}
