#include "pch.h"
#include "HangarState.h"
#include "SpaceState.h"
#include "Player.h"

void HangarState::CharacterCreation::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

	target.draw(m_AvatarFrame, states);

	target.draw(m_TextArea);
	target.draw(doneButton);
	target.draw(m_CharacterDescription);
	target.draw(m_AvatarSprites[sprite_id]);

	target.draw(m_UI);
}


HangarState::CharacterCreation::CharacterCreation(sf::RenderWindow& window, Player* player)
	: m_IsDone(false), m_UI(window), m_Window(window)
{
	initShapes();
	initAvatars();
	initDescriptions();
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


	SpriteButton* left_arrow = new SpriteButton(Configuration::Textures::LeftArrow);
	SpriteButton* right_arrow = new SpriteButton(Configuration::Textures::LeftArrow);


	sf::Vector2f scale(100, 50);
	scale.x /= left_arrow->getSize().x;
	scale.y /= left_arrow->getSize().y;

	left_arrow->setScale(scale);
	right_arrow->setScale(scale);

	right_arrow->setRotation(180);

	left_arrow->on_click = [this](const sf::Event&, Button& button) {
		swapAvatarSprite(true);
	};
	right_arrow->on_click = [this](const sf::Event&, Button& button) {
		swapAvatarSprite(false);
	};

	TextButton* confirm		= new TextButton("confirm");

	layout->add(right_arrow);
	layout->add(left_arrow);
	layout->add(confirm);

	
	confirm->on_click = [this](const sf::Event& sfevent, Button& button) {
		finishedCreation();
	};

	m_UI.addLayout(layout);

	left_arrow->setPosition(m_AvatarFrame.getPosition());
	right_arrow->setPosition(m_AvatarFrame.getPosition() + sf::Vector2f(m_AvatarFrame.getSize().x, right_arrow->getSize().y));
	confirm->setPosition(m_TextArea.getPosition() + m_TextArea.getSize() - confirm->getSize());

}

void HangarState::CharacterCreation::initAvatars()
{
	m_AvatarSprites[0].setTexture(Configuration::textures.get(Configuration::Textures::PlayerAvatar0));
	m_AvatarSprites[1].setTexture(Configuration::textures.get(Configuration::Textures::PlayerAvatar1));
	m_AvatarSprites[2].setTexture(Configuration::textures.get(Configuration::Textures::PlayerAvatar2));
	m_AvatarSprites[3].setTexture(Configuration::textures.get(Configuration::Textures::PlayerAvatar3));

	sprite_id = 0;

	sf::Vector2f scale(m_AvatarFrame.getSize());
	scale.x /= m_AvatarSprites[0].getGlobalBounds().width;
	scale.y /= m_AvatarSprites[0].getGlobalBounds().height;
	m_AvatarSprites[0].setScale(scale);

	scale = (m_AvatarFrame.getSize());
	scale.x /= m_AvatarSprites[1].getGlobalBounds().width;
	scale.y /= m_AvatarSprites[1].getGlobalBounds().height;
	m_AvatarSprites[1].setScale(scale);

	scale = (m_AvatarFrame.getSize());
	scale.x /= m_AvatarSprites[2].getGlobalBounds().width;
	scale.y /= m_AvatarSprites[2].getGlobalBounds().height;
	m_AvatarSprites[2].setScale(scale);

	scale = (m_AvatarFrame.getSize());
	scale.x /= m_AvatarSprites[3].getGlobalBounds().width;
	scale.y /= m_AvatarSprites[3].getGlobalBounds().height;
	m_AvatarSprites[3].setScale(scale);

	m_AvatarSprites[0].setPosition(m_AvatarFrame.getPosition());
	m_AvatarSprites[1].setPosition(m_AvatarFrame.getPosition());
	m_AvatarSprites[2].setPosition(m_AvatarFrame.getPosition());
	m_AvatarSprites[3].setPosition(m_AvatarFrame.getPosition());
}

void HangarState::CharacterCreation::initShapes()
{
	m_AvatarFrame.setSize(sf::Vector2f(400, 400));
	m_AvatarFrame.setPosition(sf::Vector2f(300, 300));
	m_AvatarFrame.setFillColor(sf::Color::Transparent);

	m_TextArea.setSize(sf::Vector2f(800, 400));
	m_TextArea.setPosition(sf::Vector2f(700, 300));
	m_TextArea.setFillColor(sf::Color::Green);

	doneButton.setSize(sf::Vector2f(75, 30));
	doneButton.setFillColor(sf::Color::Transparent);
	doneButton.setPosition(m_TextArea.getPosition() + m_TextArea.getSize() - sf::Vector2f(75, 30));
}

void HangarState::CharacterCreation::initDescriptions()
{
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
}

void HangarState::CharacterCreation::finishedCreation()
{
	int val = Configuration::Textures::PlayerAvatar0 + sprite_id;
	Configuration::player = new Player((Configuration::Textures)val, sf::Vector2f(m_Window.getSize()));
	m_IsDone = true;
}

void HangarState::CharacterCreation::swapAvatarSprite(bool left)
{
	if (left) {
		sprite_id--;
		if (sprite_id < 0)
			sprite_id = 3;
	}
	else {
		sprite_id++;
		if (sprite_id >= 4)
			sprite_id = 0;
	}

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

void HangarState::initGUI()
{
	VerticalLayout* navigation = new VerticalLayout;
	TextButton* back = new TextButton("BACK");
	back->on_click = [this](const sf::Event&, Button& button) {
		m_States.pop();
	};
	TextButton* next = new TextButton("NEXT");
	next->on_click = [this](const sf::Event&, Button& button) {
		m_States.push(new SpaceState(m_Window, m_States));
	};


	navigation->add(back);
	navigation->setPosition(sf::Vector2f(0, 0));
	navigation->add(next);
	m_UI.addLayout(navigation);

	next->setPosition(m_Window.getSize().x -next->getSize().x, 0);
	m_UI.bind(Configuration::GuiInputs::Escape,
		[this](const sf::Event& sfevent)
		{
			m_States.pop();
		}
	);
}

HangarState::HangarState(sf::RenderWindow& window, std::stack<State*>& states)
	: State(window, states), m_Creation(window, nullptr), m_UI(window),
	m_Background(Configuration::textures.get(Configuration::Textures::HANGAR_STATE))
{
	initGUI();
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
