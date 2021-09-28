#include "pch.h"
#include "PlayerInfoSheet.h"
#include "Player.h"
#include "HangarState.h"


void PlayerInfoSheet::draw(sf::RenderTarget& target, sf::RenderStates ) const
{
	for (auto&& rectangle : m_RectangleShapes)
		target.draw(rectangle);

	target.draw(m_Hangar.m_Player.value());

	for (auto&& text : m_TextPlayerStats)
		target.draw(text);

	

	for (auto&& text : m_TextShipStats)
		target.draw(text);

	if (m_Player.getPlayerStats().level_up_points > 0)
		target.draw(m_UI);

	target.draw(m_ShipSprite);

}

PlayerInfoSheet::PlayerInfoSheet(sf::RenderWindow& window, HangarState& hangar, Player& player)
	: m_Window(window), m_Hangar(hangar), m_Player(player)
{
	initRectangles();
	initPlayerStats();
	initShipStats();
	initGUI();
}


/* ==================================      INITIALIZERS      ================================== */
void PlayerInfoSheet::initRectangles()
{
	for (auto&& rectangle : m_RectangleShapes) {
		rectangle.setOutlineColor(sf::Color::Black);
		rectangle.setOutlineThickness(1.f);
		rectangle.setFillColor(sf::Color(0,0,0,170));
	}

	initPlayerArea();
	initPlayerStats();

	initShipArea();
	initShipStats();
}


/* This whole section is a mess ... */
#pragma region INIT/RECTAGLES
void PlayerInfoSheet::initPlayerArea() {
	sf::RectangleShape& m_PlayerArea = m_RectangleShapes[static_cast<unsigned int>(RectangleShapesIDs::m_PlayerArea)];
	const sf::Vector2f win_size(m_Window.getSize());

	m_PlayerArea.setSize(sf::Vector2f(win_size.x * 0.33f, win_size.y * 0.8f));
	m_PlayerArea.setPosition(win_size - m_PlayerArea.getSize());


	initPlayerAreaTop(m_PlayerArea);
	initPlayerAreaBot(m_PlayerArea);
}
void PlayerInfoSheet::initPlayerAreaTop(sf::RectangleShape& playerArea) {
	sf::RectangleShape& m_PlayerAreaTop = m_RectangleShapes[static_cast<unsigned int>(RectangleShapesIDs::m_PlayerAreaTop)];

	m_PlayerAreaTop.setSize(sf::Vector2f(playerArea.getSize().x, playerArea.getSize().y / 2.f));
	m_PlayerAreaTop.setPosition(playerArea.getPosition());


	initPlayerAvatar(playerArea);
	initExpBar(playerArea);
}
void PlayerInfoSheet::initPlayerAvatar(sf::RectangleShape& playerArea) {
	sf::RectangleShape& m_PlayerAvatar = m_RectangleShapes[static_cast<unsigned int>(RectangleShapesIDs::m_PlayerAvatar)];

	m_PlayerAvatar.setPosition(playerArea.getPosition());
	m_PlayerAvatar.setSize(sf::Vector2f(200, 200));

	/* PLAYER AVATAR */
	sf::Vector2f avatar_size(m_Hangar.m_Player.value().getSpriteSize());
	sf::Vector2f scale(m_PlayerAvatar.getSize().x / avatar_size.x, m_PlayerAvatar.getSize().y / avatar_size.y);
	
	auto& player = m_Hangar.m_Player.value();
	player.setSpriteScale(scale);
	player.setPosition(m_PlayerAvatar.getPosition());
}
void PlayerInfoSheet::initExpBar(sf::RectangleShape& playerArea) {

	/* EXP BAR */
	sf::RectangleShape& m_ExpBarBackground = m_RectangleShapes[static_cast<unsigned int>(RectangleShapesIDs::m_ExpBarBackground)];
	m_ExpBarBackground.setSize(sf::Vector2f(playerArea.getSize().x * 0.9f, 20));
	m_ExpBarBackground.setFillColor(sf::Color::Cyan);
	m_ExpBarBackground.setPosition(playerArea.getPosition().x + playerArea.getSize().x * 0.056f, playerArea.getPosition().y + m_Hangar.m_Player.value().getSpriteSize().y + 10);

	sf::RectangleShape& m_ExpBar = m_RectangleShapes[static_cast<unsigned int>(RectangleShapesIDs::m_ExpBar)];
	m_ExpBar.setSize(sf::Vector2f(m_ExpBarBackground.getSize().x / 3, 20));
	m_ExpBar.setPosition(m_ExpBarBackground.getPosition());
	m_ExpBar.setFillColor(sf::Color::Green);
}
void PlayerInfoSheet::initPlayerAreaBot(sf::RectangleShape& playerArea) {
	sf::RectangleShape& m_PlayerAreaBottom = m_RectangleShapes[static_cast<unsigned int>(RectangleShapesIDs::m_PlayerAreaBottom)];
	const sf::Vector2f win_size(m_Window.getSize());

	/* BOTTOM AREA */
	m_PlayerAreaBottom.setSize(sf::Vector2f(playerArea.getSize().x, playerArea.getSize().y/2.f));
	m_PlayerAreaBottom.setPosition(playerArea.getPosition().x, playerArea.getPosition().y + m_PlayerAreaBottom.getSize().y);
}
void PlayerInfoSheet::initShipArea() {
	sf::RectangleShape& m_ShipArea = m_RectangleShapes[static_cast<unsigned int>(RectangleShapesIDs::m_ShipArea)];
	sf::RectangleShape& m_PlayerArea = m_RectangleShapes[static_cast<unsigned int>(RectangleShapesIDs::m_PlayerArea)];

	const sf::Vector2f win_size(m_Window.getSize());


	m_ShipArea.setSize(sf::Vector2f(m_Window.getSize().x - m_PlayerArea.getSize().x, m_PlayerArea.getSize().y));
	m_ShipArea.setPosition(0, m_PlayerArea.getPosition().y);
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

}
#pragma endregion

void PlayerInfoSheet::initPlayerStats()
{
	for (auto&& text : m_TextPlayerStats) {
		text.setFont(Configuration::fonts.get(Configuration::Fonts::SpaceGui));
		text.setCharacterSize(25);
		text.setFillColor(sf::Color::White);
	}

	sf::RectangleShape& area = m_RectangleShapes[static_cast<unsigned int>(RectangleShapesIDs::m_PlayerAreaTop)];

	sf::Vector2f pos_top(m_RectangleShapes[static_cast<unsigned int>(RectangleShapesIDs::m_ExpBarBackground)].getPosition());
	pos_top.y += m_RectangleShapes[static_cast<unsigned int>(RectangleShapesIDs::m_ExpBarBackground)].getSize().y + 10;
	
	sf::Vector2f pos = pos_top;
	initStatsCredits	(pos);
	initStatsLevel		(pos);
	initStatsCurrentExp	(pos);
	initStatsPoints		(pos);

	/* =================================    SECOND COLUMN    ================================= */

	pos = sf::Vector2f(pos_top.x + area.getSize().x /2.f + 20.f, pos_top.y);
	initStatsPiloting	(pos);
	initStatsDamage		(pos);
	initStatsBarter		(pos);
	initStatsLearning	(pos);
}


#pragma region INIT/PLAYERSTATS
void PlayerInfoSheet::initStatsCredits(sf::Vector2f& pos) {
	const auto& stats = m_Player.getPlayerStats();
	Label& credits = m_TextPlayerStats[static_cast<unsigned int>(TextPlayerStatsIDs::credits)];

	credits.setString("Credits:\t" + std::to_string(stats.credits));
	credits.setPosition(pos);

	pos.y += credits.getSize().y + credits.getCharacterSize() / 2.f;

}
void PlayerInfoSheet::initStatsLevel(sf::Vector2f& pos) {
	const auto& stats = m_Player.getPlayerStats();
	Label& level = m_TextPlayerStats[static_cast<unsigned int>(TextPlayerStatsIDs::level)];
	
	level.setString("Level:\t" + std::to_string(stats.level));
	level.setPosition(pos);

	pos.y += level.getSize().y + level.getCharacterSize() / 2.f;

}
void PlayerInfoSheet::initStatsCurrentExp(sf::Vector2f& pos) {
	const auto& stats = m_Player.getPlayerStats();
	Label& current_experience = m_TextPlayerStats[static_cast<unsigned int>(TextPlayerStatsIDs::current_experience)];
	
	current_experience.setString("EXP:\t" + std::to_string(stats.current_experience));
	current_experience.setPosition(pos);
	
	pos.y += current_experience.getSize().y + current_experience.getCharacterSize() / 2.f;


}
void PlayerInfoSheet::initStatsPoints(sf::Vector2f& pos) {
	const auto& stats = m_Player.getPlayerStats();
	Label& level_up_points = m_TextPlayerStats[static_cast<unsigned int>(TextPlayerStatsIDs::level_up_points)];
	
	level_up_points.setString("Skill Points:\t" + std::to_string(stats.level_up_points));
	level_up_points.setPosition(pos);
	
	pos.y += level_up_points.getSize().y + level_up_points.getCharacterSize() / 2.f;
}
void PlayerInfoSheet::initStatsPiloting(sf::Vector2f& pos) {
	const auto& stats = m_Player.getPlayerStats(); 
	Label& piloting_proficiency = m_TextPlayerStats[static_cast<unsigned int>(TextPlayerStatsIDs::piloting_proficiency)];
	
	piloting_proficiency.setString("Piloting:\t" + std::to_string(stats.piloting_proficiency));
	piloting_proficiency.setPosition(pos);
	
	pos.y += piloting_proficiency.getSize().y + piloting_proficiency.getCharacterSize() / 2.f;
}
void PlayerInfoSheet::initStatsDamage(sf::Vector2f& pos) {
	const auto& stats = m_Player.getPlayerStats();
	Label& damage_proficiency = m_TextPlayerStats[static_cast<unsigned int>(TextPlayerStatsIDs::damage_proficiency)];
	
	damage_proficiency.setString("Damage:\t" + std::to_string(stats.damage_proficiency));
	damage_proficiency.setPosition(pos);
	
	pos.y += damage_proficiency.getSize().y + damage_proficiency.getCharacterSize() / 2.f;
}
void PlayerInfoSheet::initStatsBarter(sf::Vector2f& pos) {
	const auto& stats = m_Player.getPlayerStats(); 
	Label& barter_proficiency = m_TextPlayerStats[static_cast<unsigned int>(TextPlayerStatsIDs::barter_proficiency)];
	
	barter_proficiency.setString("Haggling:\t" + std::to_string(stats.barter_proficiency));
	barter_proficiency.setPosition(pos);
	
	pos.y += barter_proficiency.getSize().y + barter_proficiency.getCharacterSize() / 2.f;
}
void PlayerInfoSheet::initStatsLearning(sf::Vector2f& pos) {
	const auto& stats = m_Player.getPlayerStats(); 
	Label& learning_proficiency = m_TextPlayerStats[static_cast<unsigned int>(TextPlayerStatsIDs::learning_proficiency)];
	
	learning_proficiency.setString("Learning:\t" + std::to_string(stats.learning_proficiency));
	learning_proficiency.setPosition(pos);
	
	pos.y += learning_proficiency.getSize().y + learning_proficiency.getCharacterSize() / 2.f;
}
#pragma endregion


void PlayerInfoSheet::initShipStats()
{
	for (auto&& text : m_TextShipStats) {
		text.setFont(Configuration::fonts.get(Configuration::Fonts::SpaceGui));
		text.setCharacterSize(25);
		text.setFillColor(sf::Color::White);
	}

	sf::RectangleShape& area = m_RectangleShapes[static_cast<unsigned int>(RectangleShapesIDs::m_PlayerAreaBottom)];

	sf::Vector2f pos_top(area.getPosition());
	sf::Vector2f pos = pos_top;

	initStatsHP(pos);
	initStatsArmor(pos);




}
void PlayerInfoSheet::initStatsHP(sf::Vector2f& pos) {
	const auto& stats = m_Player.getPlayerShip().getShipStats();
	Label& current_hp = m_TextShipStats	[static_cast<unsigned int>(TextShipStatsIDs::m_CurrentHp)];
	Label& max_hp = m_TextShipStats		[static_cast<unsigned int>(TextShipStatsIDs::m_MaxHp)];


	std::ostringstream oss_current_hp;
	oss_current_hp << std::setprecision(4) << std::noshowpoint << stats.m_CurrentHp;
	std::ostringstream oss_max_hp;
	oss_max_hp << std::setprecision(4) << std::noshowpoint << stats.m_MaxHp;
	current_hp.setString("HP:\t" + oss_current_hp.str());
	max_hp.setString(" / " + oss_max_hp.str());
	current_hp.setPosition(pos);
	max_hp.setPosition(pos.x + current_hp.getSize().x, pos.y);

	
	pos.y += current_hp.getSize().y + current_hp.getCharacterSize() / 2.f;

}
void PlayerInfoSheet::initStatsArmor(sf::Vector2f& pos) {
	const auto& stats = m_Player.getPlayerShip().getShipStats();
	Label& m_Armor = m_TextShipStats[static_cast<unsigned int>(TextShipStatsIDs::m_Armor)];

	std::ostringstream oss;

	oss << std::setprecision(1) << std::noshowpoint << stats.m_Armor;
	m_Armor.setString("Armor:\t" + oss.str());
	m_Armor.setPosition(pos);

	
	pos.y += m_Armor.getSize().y + m_Armor.getCharacterSize() / 2.f;

}

void PlayerInfoSheet::initGUI()
{
	/*std::unique_ptr<VerticalLayout> layout(new VerticalLayout(opt_ref(m_UI), 2.f));

	for (int i = 0; i < 4; i++) {
		std::unique_ptr<TextButton> button(new TextButton(opt_ref(*layout), sf::Vector2f(25, 25), sf::Color::Red, "+"));
		const auto& text = m_TextPlayerStats[piloting_proficiency + i];
		sf::Vector2f pos(text.getPosition());
		sf::Vector2f size(text.getSize());

		button->setSize(sf::Vector2f(35, 35));
		sf::Vector2f posi(m_RectangleShapes[RectangleShapesIDs::m_ExpBarBackground].getPosition().x + m_RectangleShapes[RectangleShapesIDs::m_ExpBarBackground].getSize().x - 35, pos.y);
		button->setPosition(posi);
		button->on_click = [this, i](const sf::Event&, Button& button) {
			addPoint(piloting_proficiency + i);
		};

		layout->add(std::move(button));
	}

	m_UI.addLayout(std::move(layout));*/

}


/* ==================================      UPDATES      ================================== */
void PlayerInfoSheet::processEvents(const sf::Event& sfevent)
{
	m_UI.processEvent(sfevent);
}



/* ==================================      FUNCTIONS      ================================== */
void PlayerInfoSheet::addPoint(int index)
{
	auto& stats = m_Player.getPlayerStats();
	if (stats.level_up_points > 0 && index <= 8 && index >= 5) {
		switch (index) {

		case 5: //piloting_proficiency
			++stats.piloting_proficiency;
			m_TextPlayerStats[index].setString("Piloting:\t" + std::to_string(stats.piloting_proficiency));
			break;

		case 6: //damage_proficiency
			++stats.damage_proficiency;
			m_TextPlayerStats[index].setString("Damage:\t" + std::to_string(stats.damage_proficiency));
			break;

		case 7: //barter_proficiency
			++stats.barter_proficiency;
			m_TextPlayerStats[index].setString("Haggling:\t" + std::to_string(stats.barter_proficiency));
			break;

		case 8: //learning_proficiency
			++stats.learning_proficiency;
			m_TextPlayerStats[index].setString("Learning:\t" + std::to_string(stats.learning_proficiency));
			break;


		}
		--stats.level_up_points;
		m_TextPlayerStats[static_cast<unsigned int>(TextPlayerStatsIDs::level_up_points)].setString("Skill Points:\t" + std::to_string(stats.level_up_points));
	}
}
