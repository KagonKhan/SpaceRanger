#include "pch.h"
#include "HangarState.h"
#include "SpaceState.h"
#include "PlayerShip.h"

#pragma region Character Creation

void HangarState::CharacterCreation::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

	target.draw(m_AvatarFrame, states);

	target.draw(m_TextArea);
	target.draw(doneButton);
	target.draw(m_CharacterDescription);
	target.draw(m_AvatarSprites[sprite_id]);

	target.draw(m_UI);
}


HangarState::CharacterCreation::CharacterCreation(sf::RenderWindow& window, HangarState& hangar)
	: m_IsDone(false), m_UI(window), m_Window(window), m_Hangar(hangar)
{
	initShapes();
	initAvatars();
	initDescriptions();
	initGUI();
}

HangarState::CharacterCreation::~CharacterCreation()
{
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

void HangarState::CharacterCreation::finishedCreation()
{
	int val = Configuration::Textures::PlayerAvatar0 + sprite_id;

	m_Hangar.onCharacterCreationFinished(val);


	m_IsDone = true;
}

void HangarState::drawCharacterCreation(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (!m_Creation->getIsDone()) {
		target.draw(*m_Creation);
		return;
	}
}

void HangarState::processEventsCharacterCreation(const sf::Event& sfevent)
{
	if (!m_Creation->getIsDone()) {
		m_Creation->processEvents(sfevent);
		return;
	}
	// Free resources
	else
		m_Creation.reset();
}


#pragma endregion

void HangarState::onCharacterCreationFinished(int sprite_id)
{
	m_Player.emplace(Configuration::Textures(sprite_id), static_cast<sf::Vector2f>(m_Window.getSize()));
	m_PlayerInfoArea.emplace(m_Window, *this, m_Player);
}

#pragma region Player Info Area

void HangarState::PlayerInfoArea::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto&& rectangle : m_RectangleShapes)
		target.draw(rectangle);

	target.draw(m_Hangar.m_Player.value());

	for (auto&& text : m_TextPlayerStats)
		target.draw(text);
	
	target.draw(m_UI);

	target.draw(m_ShipSprite);

}

HangarState::PlayerInfoArea::PlayerInfoArea(sf::RenderWindow& window, HangarState& hangar, std::optional<Player>& player)
	: m_Window(window), m_Hangar(hangar), m_Player(player), m_UI(window)
{
	initRectangles();
	initPlayerStats();
	initGUI();
}

void HangarState::PlayerInfoArea::initRectangles()
{
	sf::Vector2f win_size(m_Window.getSize());


	
	/* ==========================    PLAYER AREA    ========================== */
	sf::RectangleShape& m_PlayerArea = m_RectangleShapes[RectangleShapesIDs::m_PlayerArea];
		m_PlayerArea.setSize(sf::Vector2f(win_size.x / 3.f, win_size.y - 200));
		m_PlayerArea.setFillColor(sf::Color(180, 200, 200, 200));
		m_PlayerArea.setPosition(win_size - m_PlayerArea.getSize());

	/* TOP PART */
	sf::RectangleShape& m_PlayerAreaTop = m_RectangleShapes[RectangleShapesIDs::m_PlayerAreaTop];
		m_PlayerAreaTop.setSize(sf::Vector2f(m_PlayerArea.getSize().x, m_PlayerArea.getSize().y / 2.f));
		m_PlayerAreaTop.setPosition(m_PlayerArea.getPosition());
		m_PlayerAreaTop.setFillColor(sf::Color::Red);

	/* PLAYER AVATAR */
	sf::RectangleShape& m_PlayerAvatar = m_RectangleShapes[RectangleShapesIDs::m_PlayerAvatar];
		m_PlayerAvatar.setPosition(m_PlayerArea.getPosition());
		m_PlayerAvatar.setSize(sf::Vector2f(200, 200));
		sf::Vector2f scale(m_PlayerAvatar.getSize()), avatar_size = m_Hangar.m_Player.value().getSpriteSize();
		scale.x /= avatar_size.x;
		scale.y /= avatar_size.y;
		m_Hangar.m_Player.value().setSpriteScale(scale);
		m_Hangar.m_Player.value().setPosition(m_PlayerAvatar.getPosition());

	/* BOTTOM AREA */
	sf::RectangleShape& m_PlayerAreaBottom = m_RectangleShapes[RectangleShapesIDs::m_PlayerAreaBottom];
		m_PlayerAreaBottom.setSize(m_PlayerAreaTop.getSize());
		m_PlayerAreaBottom.setPosition(m_PlayerArea.getPosition() + sf::Vector2f(0, m_PlayerAreaTop.getSize().y));
		m_PlayerAreaBottom.setFillColor(sf::Color::Yellow);




	/* ==========================    SHIP AREA    ========================== */



	sf::RectangleShape& m_ShipArea = m_RectangleShapes[RectangleShapesIDs::m_ShipArea];
		m_ShipArea.setSize(sf::Vector2f(m_Window.getSize().x - m_PlayerArea.getSize().x, m_PlayerArea.getSize().y));
		m_ShipArea.setPosition(0, m_PlayerArea.getPosition().y);
		m_ShipArea.setFillColor(sf::Color::Cyan);
		m_ShipSprite = m_Hangar.m_Player.value().getPlayerShipSprite();
		sf::Vector2f ship_size(m_ShipSprite.getGlobalBounds().width, m_ShipSprite.getGlobalBounds().height);
		sf::Vector2i ship_scale;
		ship_scale.x = m_ShipArea.getSize().x / ship_size.x;
		ship_scale.y = m_ShipArea.getSize().y / ship_size.y;
		ship_scale.x = ship_scale.x * 0.75f;
		ship_scale.y = ship_scale.y * 0.75f;
		m_ShipSprite.setScale(static_cast<sf::Vector2f>(ship_scale));
		sf::Vector2f ship_size_scaled(m_ShipSprite.getGlobalBounds().width, m_ShipSprite.getGlobalBounds().height);
		m_ShipSprite.setOrigin(0, 0);
		m_ShipSprite.setPosition(m_ShipArea.getPosition() + sf::Vector2f(m_ShipArea.getSize() - ship_size_scaled) / 2.f);




	/* ==========================    MISCELLANEOUS    ========================== */



	/* EXP BAR */
	sf::RectangleShape& m_ExpBarBackground = m_RectangleShapes[RectangleShapesIDs::m_ExpBarBackground];
		m_ExpBarBackground.setSize(sf::Vector2f(m_PlayerArea.getSize().x * 0.9f, 20));
		m_ExpBarBackground.setFillColor(sf::Color::Cyan);
		m_ExpBarBackground.setPosition(m_PlayerArea.getPosition().x + m_PlayerArea.getSize().x * 0.056f, m_PlayerArea.getPosition().y + m_Hangar.m_Player.value().getSpriteSize().y + 10);

	sf::RectangleShape& m_ExpBar = m_RectangleShapes[RectangleShapesIDs::m_ExpBar];
		m_ExpBar.setSize(sf::Vector2f(m_ExpBarBackground.getSize().x / 3, 20));
		m_ExpBar.setPosition(m_ExpBarBackground.getPosition());
		m_ExpBar.setFillColor(sf::Color::Green);
}

void HangarState::PlayerInfoArea::initPlayerStats()
{
	for (auto&& text : m_TextPlayerStats) {
		text.setFont(Configuration::fonts.get(Configuration::Fonts::SpaceGui));
		text.setCharacterSize(25);
		text.setFillColor(sf::Color::Black);
	}


	sf::RectangleShape& area = m_RectangleShapes[RectangleShapesIDs::m_PlayerAreaTop];
	const auto& stats = m_Player.value().getPlayerStats();
	sf::Vector2f pos_top(m_RectangleShapes[RectangleShapesIDs::m_ExpBarBackground].getPosition() + sf::Vector2f(0, m_RectangleShapes[RectangleShapesIDs::m_ExpBarBackground].getSize().y + 10));
	sf::Vector2f pos = pos_top;
	
	sf::Text& credits = m_TextPlayerStats[TextPlayerStatsIDs::credits];
	credits.setString("Credits:\t" + std::to_string(stats.credits));
	credits.setPosition(pos);
	if (area.getGlobalBounds().contains(pos.x, pos.y + credits.getGlobalBounds().height))
		pos.y += credits.getGlobalBounds().height + credits.getCharacterSize()/2.f;
	else
		pos = sf::Vector2f(pos_top.x + credits.getGlobalBounds().width, pos_top.y);


	sf::Text& level = m_TextPlayerStats[TextPlayerStatsIDs::level];
	level.setString("Level:\t" + std::to_string(stats.level));
	level.setPosition(pos);
	if (area.getGlobalBounds().contains(pos.x, pos.y + level.getGlobalBounds().height))
		pos.y += level.getGlobalBounds().height + credits.getCharacterSize() / 2.f;
	else
		pos = sf::Vector2f(pos_top.x + level.getGlobalBounds().width, pos_top.y);



	sf::Text& current_experience = m_TextPlayerStats[TextPlayerStatsIDs::current_experience];
	current_experience.setString("EXP:\t" + std::to_string(stats.current_experience));
	current_experience.setPosition(pos);
	if (area.getGlobalBounds().contains(pos.x, pos.y + current_experience.getGlobalBounds().height))
		pos.y += current_experience.getGlobalBounds().height + credits.getCharacterSize() / 2.f;
	else
		pos = sf::Vector2f(pos_top.x + current_experience.getGlobalBounds().width, pos_top.y);




	sf::Text& level_up_points = m_TextPlayerStats[TextPlayerStatsIDs::level_up_points];
	level_up_points.setString("Skill Points:\t" + std::to_string(stats.level_up_points));
	level_up_points.setPosition(pos);
	if (area.getGlobalBounds().contains(pos.x, pos.y + level_up_points.getGlobalBounds().height))
		pos.y += level_up_points.getGlobalBounds().height + credits.getCharacterSize() / 2.f;
	else
		pos = sf::Vector2f(pos_top.x + level_up_points.getGlobalBounds().width, pos_top.y);


	/* =================================    SECOND COLUMN    ================================= */

	pos = sf::Vector2f(pos_top.x + level_up_points.getGlobalBounds().width + 50, pos_top.y);


	sf::Text& piloting_proficiency = m_TextPlayerStats[TextPlayerStatsIDs::piloting_proficiency];
	piloting_proficiency.setString("Piloting:\t" + std::to_string(stats.piloting_proficiency));
	piloting_proficiency.setPosition(pos);
	if (area.getGlobalBounds().contains(pos.x, pos.y + piloting_proficiency.getGlobalBounds().height))
		pos.y += piloting_proficiency.getGlobalBounds().height + credits.getCharacterSize() / 2.f;
	else
		pos = sf::Vector2f(pos_top.x + piloting_proficiency.getGlobalBounds().width, pos_top.y);


	sf::Text& damage_proficiency = m_TextPlayerStats[TextPlayerStatsIDs::damage_proficiency];
	damage_proficiency.setString("Damage:\t" + std::to_string(stats.damage_proficiency));
	damage_proficiency.setPosition(pos);
	if (area.getGlobalBounds().contains(pos.x, pos.y + damage_proficiency.getGlobalBounds().height))
		pos.y += damage_proficiency.getGlobalBounds().height + credits.getCharacterSize() / 2.f;
	else
		pos = sf::Vector2f(pos_top.x + damage_proficiency.getGlobalBounds().width, pos_top.y);


	sf::Text& barter_proficiency = m_TextPlayerStats[TextPlayerStatsIDs::barter_proficiency];
	barter_proficiency.setString("Haggling:\t" + std::to_string(stats.barter_proficiency));
	barter_proficiency.setPosition(pos);
	if (area.getGlobalBounds().contains(pos.x, pos.y + barter_proficiency.getGlobalBounds().height))
		pos.y += barter_proficiency.getGlobalBounds().height + credits.getCharacterSize() / 2.f;
	else
		pos = sf::Vector2f(pos_top.x + barter_proficiency.getGlobalBounds().width, pos_top.y);


	sf::Text& learning_proficiency = m_TextPlayerStats[TextPlayerStatsIDs::learning_proficiency];
	learning_proficiency.setString("Learning:\t" + std::to_string(stats.learning_proficiency));
	learning_proficiency.setPosition(pos);
	if (area.getGlobalBounds().contains(pos.x, pos.y + learning_proficiency.getGlobalBounds().height))
		pos.y += learning_proficiency.getGlobalBounds().height + credits.getCharacterSize() / 2.f;
	else
		pos = sf::Vector2f(pos_top.x + learning_proficiency.getGlobalBounds().width, pos_top.y);


}

void HangarState::PlayerInfoArea::initGUI()
{
	VerticalLayout* layout = new VerticalLayout;
	m_UI.addLayout(layout);

	for (int i = 0; i < 4; i++) {
		TextButton* button = new TextButton("+");
		layout->add(button, false);
		const auto& text = m_TextPlayerStats[piloting_proficiency + i];
		sf::Vector2f pos(text.getPosition());
		sf::Vector2f size(text.getGlobalBounds().width, text.getGlobalBounds().height);

		button->setSize(sf::Vector2f(35, 35));
		button->setPosition(pos.x + size.x, pos.y);
		button->on_click = [this, i](const sf::Event&, Button& button) {
			addPoint(piloting_proficiency+i);
		};

	}

}

void HangarState::PlayerInfoArea::addPoint(int index)
{
	std::cout << index << "\n";
	auto& stats = m_Player.value().getPlayerStats();
	if (stats.level_up_points > 0) {
		switch (index) {
			
		case 5: //piloting_proficiency
			stats.piloting_proficiency++;
			m_TextPlayerStats[index].setString("Piloting:\t" + std::to_string(stats.piloting_proficiency));
			stats.level_up_points--;
			break;

		case 6: //damage_proficiency
			stats.damage_proficiency++;
			m_TextPlayerStats[index].setString("Damage:\t" + std::to_string(stats.damage_proficiency));
			stats.level_up_points--;
			break;

		case 7: //barter_proficiency
			stats.barter_proficiency++;
			m_TextPlayerStats[index].setString("Haggling:\t" + std::to_string(stats.barter_proficiency));
			stats.level_up_points--;
			break;

		case 8: //learning_proficiency
			stats.learning_proficiency++;
			m_TextPlayerStats[index].setString("Learning:\t" + std::to_string(stats.learning_proficiency));
			stats.level_up_points--;
			break;
		}
	}
}


HangarState::PlayerInfoArea::~PlayerInfoArea()
{
}

void HangarState::PlayerInfoArea::processEvents(const sf::Event& sfevent)
{
	m_UI.processEvent(sfevent);
}


#pragma endregion

























/* CAREFUL updates and draw call order is important since some objects do not exists immediately */
void HangarState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (m_Creation){
		drawCharacterCreation(target, states);
		return;
	}


	target.draw(m_Background);
	
	target.draw(m_PlayerInfoArea.value());

	target.draw(m_UI);

}


HangarState::HangarState(sf::RenderWindow& window, std::stack<State*>& states)
	: State(window, states),
	m_Background(Configuration::background_textures.get(Configuration::Backgrounds::Hangar)),
	m_UI(window),
	m_Player(std::nullopt),
	m_PlayerInfoArea(std::nullopt)
{
	initBackground();
	initGUI();

	m_Creation = std::make_unique<CharacterCreation>(window, *this);
	/* 
		it's a pointer so I can free the memory after, there is no reason for this to exist.
		Could've done differently, idk I might just make it stack allocated, and let it run out of scope
	*/
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
		m_States.push(new SpaceState(m_Window, m_States, m_Player.value().getPlayerShip()));
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

void HangarState::initBackground()
{
	sf::Vector2f window_size(m_Window.getSize());
	sf::Vector2f bg_size(m_Background.getGlobalBounds().width, m_Background.getGlobalBounds().height);

	sf::Vector2f scale;
	scale.x = window_size.x / bg_size.x;
	scale.y = window_size.y / bg_size.y;
	m_Background.setScale(scale);

}

void HangarState::processEvents(const sf::Event& sfevent)
{
	if (m_Creation) {
		processEventsCharacterCreation(sfevent);
		return;
	}
	m_PlayerInfoArea.value().processEvents(sfevent);
	m_UI.processEvent(sfevent);
}

void HangarState::update(const sf::Time& deltaTime)
{


}
