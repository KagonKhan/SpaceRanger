#pragma once
#include "State.h"

class OptionsState :
	public State
{
	void draw(sf::RenderTarget& target, sf::RenderStates) const override final;
	enum class LayoutIndexes { graphics, back_button, navigation };
	
	
	UserInterface			m_UI;
	sf::Vector2f			m_WinSize;
	sf::Sprite&				m_BackgroundSprite;
	Label					m_Title				{ std::nullopt,"OPTIONS", Configuration::fonts.get(Configuration::Fonts::SpaceGui), 100 };

	void initTitle();
#pragma region GUI
	void initGUI();
		void addGUIGraphics();
			void addButtonResolutions(VerticalLayout::ptr& vert_layout);
			void addButtonFullscreen(VerticalLayout::ptr& vert_layout);
			void addButtonVSync(VerticalLayout::ptr& vert_layout);
		void initGUIMusic();
		void addGUINavigation();
			void addButtonBack(UnorderedLayout::ptr& unordered_layout);
			void addButtonApply(HorizontalLayout::ptr& horizontal_layout);
			void addButtonSave(HorizontalLayout::ptr& horizontal_layout);
#pragma endregion
	
	void readAndApplyButtonData();

	void goFullscreen(Button& button);
	void flipMusicState();
	void changeResolution(const sf::VideoMode& mode);
	void reposition();


public:
	OptionsState(sf::RenderWindow& window, std::stack<State::ptr>& states, sf::Sprite& bgsprite);

	void processEvents(const sf::Event& sfevent) override;
	void update(const sf::Time& deltaTime) override ;
};