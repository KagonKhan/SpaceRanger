#include "pch.h"
#include "HangarState.h"
#include "CharacterCreation.h"

void CharacterCreation::draw(sf::RenderTarget& target, sf::RenderStates) const
{
	target.draw(m_AvatarFrame);

	target.draw(m_TextArea);
	target.draw(doneButton);
	target.draw(m_CharacterDescription);
	target.draw(m_AvatarSprites[sprite_id]);

	target.draw(m_UI);
}


CharacterCreation::CharacterCreation(sf::RenderWindow& window, HangarState& hangar)
	: m_Window(window), m_Hangar(hangar)
{
	initShapes();
	initAvatars();
	initDescriptions();
	initGUI();
}


/* ==================================      INITIALIZERS      ================================== */
void CharacterCreation::initGUI()
{
	addGUINavigation();

	
}
void CharacterCreation::addGUINavigation()
{
	auto unordered_layout = std::make_unique<UnorderedLayout>(Widget::opt_ref(m_UI));
	    addButtonArrows(unordered_layout);
	    addButtonConfirm(unordered_layout);
	m_UI.addLayout(std::move(unordered_layout));
}
void CharacterCreation::addButtonArrows(UnorderedLayout::ptr& unordered_layout)
{
	auto left_arrow = std::make_unique<SpriteButton>(Widget::opt_ref(*unordered_layout), sf::Vector2f(100, 50), Configuration::textures_hangar.get(Configuration::TexturesHangarState::left_arrow));
	left_arrow->on_click = [this](const sf::Event&, Button& ) {
		swapAvatarSprite(true);
	};
	left_arrow->setPosition(m_AvatarFrame.getPosition());
	unordered_layout->add(std::move(left_arrow));

	auto right_arrow = std::make_unique<SpriteButton>(Widget::opt_ref(*unordered_layout), sf::Vector2f(100, 50), Configuration::textures_hangar.get(Configuration::TexturesHangarState::right_arrow));
	right_arrow->on_click = [this](const sf::Event&, Button& ) {
		swapAvatarSprite(false);
	};
	right_arrow->setPosition(m_AvatarFrame.getPosition() + sf::Vector2f(m_AvatarFrame.getSize().x - right_arrow->getSize().x, 0.f));
	unordered_layout->add(std::move(right_arrow));

}
void CharacterCreation::addButtonConfirm(UnorderedLayout::ptr& unordered_layout)
{
	auto confirm = std::make_unique<TextButton>(Widget::opt_ref(*unordered_layout), sf::Vector2f(250, 50), sf::Color::Red, "confirm");
	confirm->on_click = [this](const sf::Event&, Button&) {
		finishedCreation();
	};
	confirm->setPosition(m_TextArea.getPosition() + m_TextArea.getSize() - confirm->getSize());

	unordered_layout->add(std::move(confirm));
}


void CharacterCreation::initAvatars()
{
	m_AvatarSprites[0].setTexture(Configuration::textures_player.get(Configuration::TexturesPlayer::player_avatar_0));
	m_AvatarSprites[1].setTexture(Configuration::textures_player.get(Configuration::TexturesPlayer::player_avatar_1));
	m_AvatarSprites[2].setTexture(Configuration::textures_player.get(Configuration::TexturesPlayer::player_avatar_2));
	m_AvatarSprites[3].setTexture(Configuration::textures_player.get(Configuration::TexturesPlayer::player_avatar_3));

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
void CharacterCreation::initShapes()
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
void CharacterCreation::initDescriptions()
{
	m_CharacterDescription.setFont(Configuration::fonts.get(Configuration::Fonts::SpaceGui));
	m_CharacterDescription.setCharacterSize(15);
	m_CharacterDescription.setLineSpacing(2);
	m_CharDescString = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";

	m_CharacterDescription.setString(m_CharDescString);
	m_CharacterDescription.setPosition(m_TextArea.getPosition());

	int string_size = m_CharDescString.getSize();
	float text_pos = m_TextArea.getPosition().x;
	float text_size = m_TextArea.getSize().x;
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


/* ==================================      UPDATES      ================================== */
void CharacterCreation::processEvents(const sf::Event& sfevent)
{
	m_UI.processEvent(sfevent);
}



/* ==================================      FUNCTIONS      ================================== */
void CharacterCreation::swapAvatarSprite(bool left)
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
bool CharacterCreation::isDone() const
{
	return m_IsDone;
}
void CharacterCreation::finishedCreation()
{
	int val = static_cast<int>(Configuration::TexturesPlayer::player_avatar_0) + sprite_id;

	m_Hangar.onCharacterCreationFinished(val);

	m_IsDone = true;
}