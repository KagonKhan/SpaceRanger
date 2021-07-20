#pragma once
#include "Widget.h"
namespace GUI {
	class Layout : protected Widget
	{
	protected:
		friend class Container;
		float m_Space;

	public:
		Layout(Widget* parent = nullptr);
		virtual ~Layout();

		void setSpace(float pixels);
	};

}