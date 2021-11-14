#include "pch.h"
#include "HangarState.h"
#include "CharacterCreation.h"

void CharacterCreation::draw(sf::RenderTarget& target, sf::RenderStates) const
{
	target.draw(m_AvatarFrame);

	target.draw(m_TextArea);
	target.draw(doneButton);
	target.draw(m_CharacterDescription[sprite_id]);
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

void CharacterCreation::initShapes()
{
	sf::RectangleShape back_shape{ sf::Vector2f(1200,400) };
	back_shape.setPosition(((sf::Vector2f)m_Window.getSize() - back_shape.getSize()) / 2.f);

	m_AvatarFrame.setSize(sf::Vector2f(400, 400));
	m_AvatarFrame.setPosition(back_shape.getPosition());
	m_AvatarFrame.setFillColor(sf::Color::Transparent);

	m_TextArea.setSize(sf::Vector2f(800, 400));
	m_TextArea.setPosition(back_shape.getPosition() + sf::Vector2f(m_AvatarFrame.getSize().x, 0));
	m_TextArea.setFillColor(sf::Color::Green);

	doneButton.setSize(sf::Vector2f(75, 30));
	doneButton.setFillColor(sf::Color::Transparent);
	doneButton.setPosition(m_TextArea.getPosition() + m_TextArea.getSize() - sf::Vector2f(75, 30));
}

void CharacterCreation::initAvatars()
{
	sprite_id = 0;
	for (int i = 0; i < 4; ++i) {
		m_AvatarSprites[i].setTexture(Configuration::textures_player.get(Configuration::TexturesPlayer(i)));

		sf::Vector2f scale(m_AvatarFrame.getSize());
		scale.x /= m_AvatarSprites[i].getGlobalBounds().width;
		scale.y /= m_AvatarSprites[i].getGlobalBounds().height;
		m_AvatarSprites[i].setScale(scale);

		m_AvatarSprites[i].setPosition(m_AvatarFrame.getPosition());
	}
}

void CharacterCreation::initDescriptions()
{
	m_CharDescString[0] = "Bryany Binson: Male Explorer. Bryany has straight red hair and grey eyes. He wears a technical jumpsuit and carries a semi-automatic pistol. Bryany is wrongly sought by the law for espionage.";
	m_CharDescString[1] = "Albed Hilly: Male Engineer. Albed has a square face, with copper hair and soft white eyes. He wears a white jumpsuit and carries a semi-automatic pistol. Albed is faithful and decisive.";
	m_CharDescString[2] = "Peterr Mitchy: Male Rogue. Peterr has a narrow face, with matted violet hair and red eyes. He wears an old uniform and carries a tablet computer. Peterr is superstitious and modest.";
	m_CharDescString[3] = "Jeffry Smillee: Male Scientist. Jeffry is short and overweight, with blue hair and silver eyes. He wears a technical jumpsuit and carries a tablet computer. Jeffry seeks to prove himself to his peers.";

	int index = 0;
	for (auto&& text : m_CharacterDescription) {
		text.setFont(Configuration::fonts.get(Configuration::Fonts::SpaceGui));
		text.setCharacterSize(25);
		text.setLineSpacing(2);

		text.setString(m_CharDescString[index]);
		index++;
		text.setPosition(m_TextArea.getPosition());
	}

	for (int index = 0; index < 4; index++) {
		int string_size = m_CharDescString[index].getSize();
		float text_pos = m_TextArea.getPosition().x;
		float text_size = m_TextArea.getSize().x;
		float limit = text_pos + text_size - 75;

		for (int i = 0; i < string_size; ++i) {
			float char_pos = m_CharacterDescription[index].findCharacterPos(i).x;
			if (char_pos > limit) {
				m_CharDescString[index].insert(i, "\n");
				m_CharacterDescription[index].setString(m_CharDescString[index]);
			}
		}
		m_CharacterDescription[index].setString(m_CharDescString[index]);

	}
}

void CharacterCreation::initGUI()
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