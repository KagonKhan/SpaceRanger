#pragma once
#include "Widget.h"
namespace GUI {
	class Layout : virtual protected Widget
	{
	protected:
		friend class Container;
		friend class Frame;

		float m_Space;

	public:
		Layout(const Layout&) = delete;
		Layout& operator=(const Layout&) = delete;

		Layout(Widget* parent = nullptr);
		virtual ~Layout();

		virtual void clear() = 0;

		void setSpace(float pixels);
	};

}