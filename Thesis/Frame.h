#pragma once
#include "Container.h"
#include "ActionTarget.h"

namespace GUI
{
	class Frame : public Container, protected ActionTarget<int>
	{
	private:
		sf::RenderWindow& m_Window;

		virtual bool processEvent(const sf::Event& sfevent, const sf::Vector2f& parent_pos) override;
		virtual void processEvents(const sf::Vector2f& parent_pos) override;

	
	public:
		Frame(const Frame&) = delete;
		Frame& operator=(const Frame&) = delete;

		using ActionTarget<int>::FuncType;

		Frame(sf::RenderWindow& window);
		virtual ~Frame();

		void processEvents();
		bool processEvent(const sf::Event& sfevent);

		void bind(int key, const FuncType& callback);
		void unbind(int key);

		void draw();
		virtual sf::Vector2f getSize() const override;

	};

}