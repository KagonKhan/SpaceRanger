#include "State.h"

class OptionsState : public State
{
	UI ui;
	void initGUI();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override final;

	void Options();
	void NewGame();
public:

	void processEvents(const sf::Event& sfevent);
	OptionsState(sf::RenderWindow& window, std::stack<State*>& states);
	~OptionsState();


	void update(const sf::Time& deltaTime)  override final;
};