#pragma once

#include "ResourceManager.h"
#include "ActionMap.h"


class Player;
class OptionsState;
class MainMenuState;
class Configuration
{
private:
	static int m_Score;
	static sf::Text m_Txt_Score;
	static sf::Sprite m_Spr_Life;

	static void initTextures();
	static void initBackgrounds();
	static void initFonts();
	static void initSounds();
	static void initMusics();

	static void initPlayerInputs();
	static void initGuiInputs();

public:
	Configuration() = delete;
	Configuration(const Configuration&) = delete;
	Configuration& operator= (const Configuration&) = delete;

	struct Colors
	{
		static sf::Color button_fill;
		static sf::Color button_outline;
		static sf::Color label_text;

		static float lighting;
	};


	enum Textures : int {
		TEST_MENU = 0x000,
		Cursor,

		TEST_OPTIONS = 0x100,
	

		TEST_SCORES = 0x200,
	

		Hangar = 0x300,


		PLAYER_AVATARS = 0x400,
		PlayerAvatar0,
		PlayerAvatar1,
		PlayerAvatar2,
		PlayerAvatar3,
	

		LeftArrow = 0x500,
		RightArrow
	};
	


	enum Backgrounds : int {
		MainMenu,

	};
	enum Fonts : int {
		Gui,
		SpaceGui
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
		MainMenuTheme
	};

	enum GuiInputs : int {
		N,
		O,
		H,
		Q,
		Escape
	};

	static ResourceManager<sf::Texture, int> textures;
	static ResourceManager<sf::Texture, int> background_textures;
	static ResourceManager<sf::SoundBuffer, int> sounds;
	static ResourceManager<sf::Music, int> musics;
	static ResourceManager<sf::Font, int> fonts;
	
	static ActionMap<int> gui_inputs;
	static ActionMap<int> playerInputs;


	static void initialize();
	static void reset();

	static bool isGameOver();

	static void addScore(int s);
	static int getScore();

	static class Player* player;
	/* TODO: Decide if I want to hold pointers here, or just have State* in each class */
	static class OptionsState* m_Options;
	static class MainMenuState* m_MainMenu;

	static sf::Music* m_MainMenuMusic;

	static int level;
	static int lives;

	static void draw(sf::RenderTarget& target);
};

