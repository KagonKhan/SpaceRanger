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
	

	public:
		Container(const Container&) = delete;
		Container& operator=(const Container&) = delete;

		Container(Widget* parent = nullptr);
		virtual ~Container();

		void setLayout(Layout* layout);
	
	};

}