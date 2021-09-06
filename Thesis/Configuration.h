#pragma once

#include "ResourceManager.h"
#include "ActionMap.h"


class PlayerShip;
class OptionsState;
class MainMenuState;
class Configuration
{
private:


	static void initTextures();
		static void initTexturesGameState();
		static void initTexturesMenuState();
		static void initTexturesHangarState();
		static void initTexturesOptionsState();
		static void initTexturesPlayer();
		static void initTexturesWeaponParts();
		static void initTexturesShips();



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


	enum class TexturesGameState {
		cursor,
	};
	enum class TexturesMenuState {
		background,
	};
	enum class TexturesHangarState {
		background, left_arrow, right_arrow,
	};
	enum class TexturesOptionsState {
		left_arrow,
		right_arrow,
	};
	enum class TexturesPlayer {
		player_avatar_0, player_avatar_1, player_avatar_2, player_avatar_3,

	};
	enum class TexturesWeaponry {
		turret_laser, turret_rocket, turret_beam,

		ammo_laser, ammo_missile, ammo_missile_thrusters, ammo_beam,
	};
	enum class TexturesShips
	{
		player_ship, player_exhaust,
	};


	static ResourceManager<sf::Texture, TexturesGameState>		textures_game;
	static ResourceManager<sf::Texture, TexturesMenuState>		textures_menu;
	static ResourceManager<sf::Texture, TexturesHangarState>	textures_hangar;
	static ResourceManager<sf::Texture, TexturesOptionsState>	textures_options;
	static ResourceManager<sf::Texture, TexturesPlayer>			textures_player;
	static ResourceManager<sf::Texture, TexturesWeaponry>		textures_weaponry;
	static ResourceManager<sf::Texture, TexturesShips>			textures_ships;


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



	static class PlayerShip* player;
	/* TODO: Decide if I want to hold pointers here, or just have State* in each class */
	static class OptionsState* m_Options;
	static class MainMenuState* m_MainMenu;

	static sf::Music* m_MainMenuMusic;



};

