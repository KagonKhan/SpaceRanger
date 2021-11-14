#pragma once
#include "SpaceState.h"


class MainMenuState :
	public State
{
private:
friend class OptionsState;

	sf::Texture&				m_BackgroundTexture		{ Configuration::textures_menu.get(Configuration::TexturesMenuState::background) };
	sf::Sprite					m_BackgroundSprite;
	UserInterface				m_UI;
	Label						m_Title					{ std::nullopt, "SPACE RANGER" };
	



	/// <summary>
	/// Initializes all graphic components, adds functionality, assigns keybinds
	/// </summary>
	void initGUI();
	/// <summary>
	/// Sets the texture, crops it appropriately and sets the position
	/// </summary>
	void initBackground();
	/// <summary>
	/// Sets position, color and style
	/// </summary>
	void initTitle();
	/// <summary>
	/// Loads the resource, sets volume and plays
	/// </summary>
	void initMusic() const;

	/// <summary>
	/// Pans the texture rectangle right-left
	/// switches direction when gets to the end
	/// </summary>
	/// <param name="deltaTime">Time between frames</param>
	void updateBackground(const sf::Time& deltaTime);
	/// <summary>
	/// Flashes the color, by changing the Red value
	/// </summary>
	/// <param name="deltaTime"></param>
	void updateTitle(const sf::Time& deltaTime);

	void draw(sf::RenderTarget& target, sf::RenderStates) const override ;
	/// <summary>
	/// Pushes the options state on stack
	/// </summary>
	void Options();
	/// <summary>
	/// Pushes the new game state on stack and stops music
	/// </summary>
	void NewGame();
	/// <summary>
	/// Recalculates title and GUI positions. Call after window resizes
	/// </summary>
	void reposition();

public:
	MainMenuState(sf::RenderWindow& window, std::stack<State::ptr>& states);
	~MainMenuState() final;

	void processEvents(const sf::Event& sfevent) override;

	void update(const sf::Time& deltaTime)  override;
};

