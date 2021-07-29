#pragma once
#include "Container.h"
#include "ActionTarget.h"

namespace GUI
{
	class Frame : public Container, protected ActionTarget<int>
	{
	private:
		sf::RenderWindow& m_Window;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	
	public:
		Frame(const Frame&) = delete;
		Frame& operator=(const Frame&) = delete;

		Frame(sf::RenderWindow& window);

		virtual ~Frame();

		void bind(int key, const FuncType& callback);
		void unbind(int key);

		void draw();

		
	};

}