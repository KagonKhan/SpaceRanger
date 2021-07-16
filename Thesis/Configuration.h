#pragma once
#include "SFML/Graphics.hpp"
#include "ResourceManager.h"
#include "ActionMap.h"

class Player;
class Configuration
{
private:
	static int m_Score;
	static sf::Text m_Txt_Score;
	static sf::Sprite m_Spr_Life;

	static void initTextures();
	static void initFonts();
	static void initSounds();
	static void initMusics();

	static void initPlayerInputs();

public:
	Configuration() = delete;
	Configuration(const Configuration&) = delete;
	Configuration& operator= (const Configuration&) = delete;


	enum Textures : int {
		Player,
		PlayerLife,
		BigSaucer,
		SmallSaucer,
		BigMeteor1,
		BigMeteor2,
		BigMeteor3,
		BigMeteor4,
		MediumMeteor1,
		MediumMeteor2,
		SmallMeteor1,
		SmallMeteor2,
		SmallMeteor3,
		SmallMeteor4,
		ShootPlayer,
		ShootSaucer
	};
	enum Fonts : int {
		Gui
	};
	enum PlayerInputs : int {
		Up,
		Left,
		Right,
		Shoot,
		Hyperspace
	};
	enum Sounds : int {
		LaserPlayer,
		LaserEnemy,
		SaucerSpawn1,
		SaucerSpawn2,
		Boom1,
		Boom2,
		Explosion1,
		Explosion2,
		Explosion3,
		Jump
	};
	enum Musics : int {
		Theme
	};


	static ResourceManager<sf::Texture, int> textures;
	static ResourceManager<sf::SoundBuffer, int> sounds;
	static ResourceManager<sf::Music, int> musics;
	static ResourceManager<sf::Font, int> fonts;


	static ActionMap<int> playerInputs;


	static void initialize();
	static void reset();

	static bool isGameOver();

	static void addScore(int s);
	static int getScore();

	static class Player* player;
	static int level;
	static int lives;

	static void draw(sf::RenderTarget& target);
};

