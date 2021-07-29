#include "Layout.h"
#include <vector>

namespace GUI
{
	class HLayout : public Layout
	{
	private:
		std::vector<Widget*> m_Widgets;
		
		virtual void updateShape() override;
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	protected:
		virtual bool processEvent(const sf::Event& sfevent, const sf::Vector2f& parent_pos) override;
		virtual void processEvents(const sf::Vector2f& parent_pos) override;

	public:
		HLayout(const HLayout&) = delete;
		HLayout& operator=(const HLayout&) = delete;

		HLayout(Widget* parent = nullptr);
		~HLayout();

		void add(Widget* widget);
		Widget* at(unsigned int index) const;

		virtual sf::Vector2f getSize() const override;

		virtual void clear();

	};

}