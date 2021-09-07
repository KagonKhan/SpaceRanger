#pragma once
#include "State.h"

class OptionsState :
	public State
{
	void draw(sf::RenderTarget& target, sf::RenderStates) const override final;
	enum class LayoutIndexes { graphics, back_button, navigation };
	UserInterface m_UI;
	Label m_Title;

	sf::Sprite& m_BackgroundSprite;

	void initTitle();
#pragma region GUI
	void initGUI();
		void addGUIGraphics();
			void addButtonResolutions(VerLayPtr& vert_layout);
			void addButtonFullscreen(VerLayPtr& vert_layout);
			void addButtonVSync(VerLayPtr& vert_layout);
		void initGUIMusic();
		void addGUINavigation();
			void addButtonBack(UnoLayPtr& unordered_layout);
			void addButtonApply(HorLayPtr& horizontal_layout);
			void addButtonSave(HorLayPtr& horizontal_layout);
#pragma endregion
	
	void readAndApplyButtonData();

	void goFullscreen(Button& button);
	void flipMusicState();
	void changeResolution(const sf::VideoMode& mode);
	void reposition();


public:
	OptionsState(sf::RenderWindow& window, std::stack<State::ptr>& states, sf::Sprite& bgsprite);
	virtual ~OptionsState();

	void processEvents(const sf::Event& sfevent);
	void update(const sf::Time& deltaTime) override final;
};