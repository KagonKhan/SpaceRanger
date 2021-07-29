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

	

	void Frame::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{

		Container::draw(target, states);
	}



	void Frame::bind(int key, const FuncType& callback)
	{
		ActionTarget::bind(key, callback);
	}

	void Frame::unbind(int key)
	{
		ActionTarget::unbind(key);
	}

	
}
