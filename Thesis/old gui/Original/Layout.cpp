#include "Layout.h"

namespace GUI
{
	Layout::Layout(Widget* parent)
		: Widget(parent), m_Space(5)
	{

	}

	Layout::~Layout()
	{

	}

	void Layout::setSpace(float pixels)
	{
		if (pixels >= 0) {
			m_Space = pixels;
			updateShape();
		}
		else throw std::invalid_argument("[ERROR] pixel value must be >= 0");
	}
}