#pragma once
#include "State.h"

class OptionsState :
	public State
{
	void draw(sf::RenderTarget& target, sf::RenderStates) const final;
	enum class LayoutIndexes { graphics, back_button, navigation };
	
	
	UserInterface			m_UI;
	sf::Vector2f			m_WinSize;
	sf::Sprite&				m_BackgroundSprite;
	Label					m_Title				{ std::nullopt,"OPTIONS", Configuration::fonts.get(Configuration::Fonts::SpaceGui), 100 };

	/// <summary>
	/// Sets style, color, position
	/// </summary>
	void initTitle();
#pragma region GUI
	/// <summary>
	/// Adds all the GUI components
	/// </summary>
	void initGUI();
		void addGUIGraphics(VerticalLayout::ptr& vert_layout);
			void addButtonResolutions(VerticalLayout::ptr& vert_layout);
			void addButtonFullscreen(VerticalLayout::ptr& vert_layout);
			void addButtonVSync(VerticalLayout::ptr& vert_layout);
		void initGUIMusic(VerticalLayout::ptr& vert_layout);
		void addGUINavigation();
#pragma endregion
	
	/// <summary>
	/// Reads all the buttons values, and applies the settings
	/// </summary>
	void readAndApplyButtonData();
	/// <summary>
	/// Obsolete right now. Worked mostly with checkboxes
	/// </summary>
	/// <param name="button"></param>
	void goFullscreen(Button& button);
	/// <summary>
	/// Flips the state between playing or paused
	/// </summary>
	void flipMusicState();
	/// <summary>
	/// Obsolete right now. Used with previous version of GUI
	/// </summary>
	/// <param name="mode"></param>
	void changeResolution(const sf::VideoMode& mode);
	/// <summary>
	/// Recalculate GUI, Background, title positions
	/// </summary>
	void reposition();


public:
	OptionsState(sf::RenderWindow& window, std::stack<State::ptr>& states, sf::Sprite& bgsprite);

	void processEvents(const sf::Event& sfevent) override;
	void update(const sf::Time& deltaTime) override ;
};