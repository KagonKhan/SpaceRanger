#pragma once
#include "State.h"

class OptionsState :
	public State
{
	void draw(sf::RenderTarget& target, sf::RenderStates) const override final;

	UserInterface m_UI;
	Label m_Title;

	sf::Sprite& m_BackgroundSprite;

	void initTitle();
#pragma region GUI
	void initGUI();
		void addGUIGraphics();
			void addGUIResolutions(VerLayPtr& vert_layout);
			void addGUIFullscreen(VerLayPtr& vert_layout);
			void addGUIVSync(VerLayPtr& vert_layout);
		void initGUIMusic();
		void addGUINavigation();
			void addGUIBack(UnoLayPtr& unordered_layout);
			void addGUIApply(HorLayPtr& horizontal_layout);
			void addGUISave(HorLayPtr& horizontal_layout);
#pragma endregion
	
	void readAndApplyButtonData();

	void goFullscreen(Button& button);
	void flipMusicState();
	void changeResolution(const sf::VideoMode& mode);
	void reposition();


public:
	OptionsState(sf::RenderWindow& window, std::stack<State*>& states, sf::Sprite& bgsprite);
	virtual ~OptionsState();

	void processEvents(const sf::Event& sfevent);
	void update(const sf::Time& deltaTime) override final;
};