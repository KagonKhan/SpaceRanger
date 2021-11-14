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
	


	void initTitle();
	/// <summary>
	/// Initializes all graphic components, adds functionality, assigns keybinds
	/// </summary>
	void initGUI();
	void initBackground();
	void initMusic() const;


	void updateBackground(const sf::Time& deltaTime);
	void updateTitle(const sf::Time& deltaTime);

	void draw(sf::RenderTarget& target, sf::RenderStates) const override ;

	void Options();
	void NewGame();

	void reposition();

public:
	MainMenuState(sf::RenderWindow& window, std::stack<State::ptr>& states);
	~MainMenuState() final;

	void processEvents(const sf::Event& sfevent) override;

	void update(const sf::Time& deltaTime)  override;
};

