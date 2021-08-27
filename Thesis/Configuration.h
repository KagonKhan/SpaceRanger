#pragma once

#include "ResourceManager.h"
#include "ActionMap.h"


class PlayerShip;
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


	static short int m_MasterVolume;
	static short int m_SoundEffectsVolume;
	static short int m_SoundVolume;
	static short int m_DialogueVolume;

	static 	sf::RectangleShape tar;

	static ResourceManager<sf::Texture, int> textures;
	static ResourceManager<sf::Texture, int> background_textures;
	static ResourceManager<sf::SoundBuffer, int> sounds;
	static ResourceManager<sf::Music, int> musics;
	static ResourceManager<sf::Font, int> fonts;

	static ActionMap<int> gui_inputs;
	static ActionMap<int> playerInputs;

	static sf::Vector2f boundaries;
	struct Colors
	{
		static sf::Color button_fill;
		static sf::Color button_outline;
		static sf::Color label_text;

		static float lighting;
	};



	enum Textures : int {
		MENU_STATE = 0x000,
		Cursor,

		OPTIONS_STATE = 0x100,
	

		HANGAR_STATE = 0x200,
		LeftArrow,
		RightArrow,

		TEST_SCORES = 0x300,
	

		PLAYER_AVATARS = 0x400,
		PlayerAvatar0,
		PlayerAvatar1,
		PlayerAvatar2,
		PlayerAvatar3,
	

		SHIPS = 0x600,
		PlayerShip,


		PARTS,
		PlayerExhaust,
		Thrusters,
		Ammo_Missile_Thrusters,


		TURRETS = 0x700,
		Turret_Laser,
		Turret_Rocket,
		Turret_Beam,

		AMMUNITION = 0x800,
		Ammo_Laser,
		Ammo_Missile,
		Ammo_Beam


	};
	


	enum Backgrounds : int {
		MainMenu,
		Hangar,

	};
	enum Fonts : int {
		Gui,
		SpaceGui,
	};
	enum PlayerInputs : int {
		Up,
		Left,
		Right,
		Down,
		Shoot,
	};
	enum Sounds : int {
		LaserPlayer,
		Missile,
		Beam
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

	

	static void initialize();

	static void CreateWindow(sf::RenderWindow& window);
	static void LoadFileToString(const std::filesystem::path& path, std::string& loadTo);
	static void ReplaceFirstOccurance(std::string& s, const std::string& toReplace, const std::string& replaceWith);
	
	// return vec2f from global bounds 

	// Receives position, and checks if contained in area
	static bool CheckIfPointContainedInArea(const sf::Vector2f& pos, const sf::Vector2f& area);

	static void reset();

	static bool isGameOver();

	static void addScore(int s);


	static int getScore();

	static class PlayerShip* player;
	/* TODO: Decide if I want to hold pointers here, or just have State* in each class */
	static class OptionsState* m_Options;
	static class MainMenuState* m_MainMenu;

	static sf::Music* m_MainMenuMusic;

	static int level;
	static int lives;

	static void draw(sf::RenderTarget& target);
};

