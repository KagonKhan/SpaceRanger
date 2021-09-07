#pragma once
#include "UI.h"

class HangarState;
class Player;
class PlayerInfoSheet : 
	public sf::Drawable
{
private:
	void draw(sf::RenderTarget& target, sf::RenderStates) const override final;


	enum class RectangleShapesIDs { m_PlayerArea, m_PlayerAreaTop, m_PlayerAvatar, m_PlayerAreaBottom, m_ShipArea, m_ExpBarBackground, m_ExpBar, COUNT_RECTANGLES};
	sf::RectangleShape m_RectangleShapes[static_cast<unsigned int>(RectangleShapesIDs::COUNT_RECTANGLES)];

	enum class TextPlayerStatsIDs { credits, level, current_experience, luck, level_up_points, piloting_proficiency, damage_proficiency, barter_proficiency, learning_proficiency, COUNT_TEXTSTATS };
	Label m_TextPlayerStats[static_cast<unsigned int>(TextPlayerStatsIDs::COUNT_TEXTSTATS)];

	enum class TextShipStatsIDs { m_CurrentHp, m_MaxHp, m_Armor, m_Plating, COUNT_TEXTSTATS_SHIP };
	Label m_TextShipStats[static_cast<unsigned int>(TextShipStatsIDs::COUNT_TEXTSTATS_SHIP)];


	sf::RenderWindow& m_Window;
	HangarState& m_Hangar;
	Player& m_Player;

	UserInterface m_UI;
	sf::Sprite m_ShipSprite;


	void initRectangles();
		void initPlayerArea();
			void initPlayerAreaTop(sf::RectangleShape& playerArea);
				void initPlayerAvatar(sf::RectangleShape& playerArea);
				void initExpBar(sf::RectangleShape& playerArea);
			void initPlayerAreaBot(sf::RectangleShape& playerArea);
	void initPlayerStats();
		void initStatsCredits	(sf::Vector2f& pos);
		void initStatsLevel		(sf::Vector2f& pos);
		void initStatsCurrentExp(sf::Vector2f& pos);
		void initStatsPoints	(sf::Vector2f& pos);
		void initStatsPiloting	(sf::Vector2f& pos);
		void initStatsDamage	(sf::Vector2f& pos);
		void initStatsBarter	(sf::Vector2f& pos);
		void initStatsLearning	(sf::Vector2f& pos);
	
	void initShipArea();
	void initShipStats();
		void initStatsHP(sf::Vector2f& pos);
		void initStatsArmor(sf::Vector2f& pos);


	void initGUI();

	void addPoint(int index);

public:
	PlayerInfoSheet(sf::RenderWindow& window, HangarState& hangar, Player& player);
	~PlayerInfoSheet();

	void processEvents(const sf::Event& sfevent);
};

