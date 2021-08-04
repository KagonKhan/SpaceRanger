#include "pch.h"
#include "HangarState.h"

void HangarState::CharacterCreation::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

	target.draw(m_AvatarFrame, states);
	target.draw(arrow, states);

	sf::Vector2f pos(m_AvatarFrame.getSize().x - arrow.getSize().x, 0);
	states.transform.translate(pos);
	target.draw(arrow, states);

	target.draw(m_TextArea);
	target.draw(doneButton);
	target.draw(m_CharacterDescription);

	target.draw(m_UI);
}


HangarState::CharacterCreation::CharacterCreation(sf::RenderWindow& window, Player* player)
	: m_IsDone(false), m_UI(window), m_Player(player)
{
	m_AvatarFrame.setSize(sf::Vector2f(400, 400));
	m_AvatarFrame.setPosition(sf::Vector2f(300, 300));
	m_AvatarFrame.setFillColor(sf::Color::Cyan);

	arrow.setSize(sf::Vector2f(50, 50));
	arrow.setPosition(m_AvatarFrame.getPosition());
	arrow.setFillColor(sf::Color::Red);

	m_TextArea.setSize(sf::Vector2f(800, 400));
	m_TextArea.setPosition(sf::Vector2f(700, 300));
	m_TextArea.setFillColor(sf::Color::Green);

	doneButton.setSize(sf::Vector2f(75, 30));
	doneButton.setFillColor(sf::Color::Magenta);
	doneButton.setPosition(m_TextArea.getPosition() + m_TextArea.getSize() - sf::Vector2f(75, 30));






	m_CharacterDescription.setFont(Configuration::fonts.get(Configuration::Fonts::SpaceGui));
	m_CharacterDescription.setCharacterSize(15);
	m_CharacterDescription.setLineSpacing(2);
	m_CharDescString = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";

	m_CharacterDescription.setString(m_CharDescString);
	m_CharacterDescription.setPosition(m_TextArea.getPosition());

	int string_size = m_CharDescString.getSize();
	float text_pos = m_TextArea.getPosition().x, text_size = m_TextArea.getSize().x;
	float limit = text_pos + text_size - 75;

	for (int i = 0; i < string_size; ++i) {
		float char_pos = m_CharacterDescription.findCharacterPos(i).x;
		if (char_pos > limit) {
			m_CharDescString.insert(i, "\n");
			m_CharacterDescription.setString(m_CharDescString);
		}
	}
	m_CharacterDescription.setString(m_CharDescString);

	initGUI();
}

bool HangarState::CharacterCreation::getIsDone() const
{
	return m_IsDone;
}

void HangarState::CharacterCreation::processEvents(const sf::Event& sfevent)
{
	m_UI.processEvent(sfevent);
}

void HangarState::CharacterCreation::initGUI()
{
	VerticalLayout* layout = new VerticalLayout;

	TextButton* right_arrow = new TextButton("next");
	TextButton* left_arrow  = new TextButton("prev");
	TextButton* confirm		= new TextButton("confirm");

	layout->add(right_arrow);
	layout->add(left_arrow);
	layout->add(confirm);

	right_arrow->on_click = [this](const sf::Event& sfevent, Button& button) {
		m_AvatarFrame.setFillColor(sf::Color::Blue);
	};
	left_arrow->on_click = [this](const sf::Event& sfevent, Button& button) {
		m_AvatarFrame.setFillColor(sf::Color::Magenta);
	};
	confirm->on_click = [this](const sf::Event& sfevent, Button& button) {
		finishedCreation();
	};

	m_UI.addLayout(layout);

	right_arrow->setPosition(m_AvatarFrame.getPosition());
	left_arrow->setPosition(m_AvatarFrame.getPosition() + sf::Vector2f(m_AvatarFrame.getSize().x - left_arrow->getSize().x, 0));
	confirm->setPosition(m_TextArea.getPosition() + m_TextArea.getSize() - confirm->getSize());

}

void HangarState::CharacterCreation::finishedCreation()
{
	m_IsDone = true;
}














void HangarState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_Background);

	if (!m_Creation.getIsDone()) {
		target.draw(m_Creation);
		return;
	}

	target.draw(m_UI);

}

void HangarState::initUI()
{
	VerticalLayout* navigation = new VerticalLayout;
	TextButton* back = new TextButton("BACK");
	back->on_click = [this](const sf::Event&, Button& button) {
		m_States.pop();
	};


	navigation->add(back);
	navigation->setPosition(sf::Vector2f(0, 0));
	m_UI.addLayout(navigation);

	m_UI.bind(Configuration::GuiInputs::Escape,
		[this](const sf::Event& sfevent)
		{
			m_States.pop();
		}
	);
}

HangarState::HangarState(sf::RenderWindow& window, std::stack<State*>& states)
	: State(window, states), m_Creation(window, nullptr), m_UI(window), m_Background(Configuration::textures.get(Configuration::Textures::Hangar))
{
	initUI();
}

void HangarState::processEvents(const sf::Event& sfevent)
{
	if (!m_Creation.getIsDone()) {
		m_Creation.processEvents(sfevent);
		return;
	}

	m_UI.processEvent(sfevent);
}

void HangarState::update(const sf::Time& deltaTime)
{

}
