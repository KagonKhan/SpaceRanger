#include "pch.h"
#include "Configuration.h"


short int Configuration::m_MasterVolume = 10;
short int Configuration::m_SoundEffectsVolume = 10;
short int Configuration::m_SoundVolume = 20;
short int Configuration::m_DialogueVolume = 20;


#pragma region TEXTURES
ResourceManager<sf::Texture, Configuration::TexturesGameState>		Configuration::textures_game;
ResourceManager<sf::Texture, Configuration::TexturesMenuState>		Configuration::textures_menu;
ResourceManager<sf::Texture, Configuration::TexturesHangarState>	Configuration::textures_hangar;
ResourceManager<sf::Texture, Configuration::TexturesOptionsState>	Configuration::textures_options;
ResourceManager<sf::Texture, Configuration::TexturesPlayer>			Configuration::textures_player;
ResourceManager<sf::Texture, Configuration::TexturesWeaponry>		Configuration::textures_weaponry;
ResourceManager<sf::Texture, Configuration::TexturesShips>			Configuration::textures_ships;
#pragma endregion


ResourceManager<sf::Font, int> Configuration::fonts;
ResourceManager<sf::SoundBuffer, int> Configuration::sounds;
ResourceManager<sf::Music, int> Configuration::musics;

ActionMap<int> Configuration::playerInputs;
ActionMap<int> Configuration::gui_inputs;



sf::Vector2f Configuration::boundaries;

sf::RectangleShape Configuration::tar;


//Player* Configuration::player = nullptr;
OptionsState* Configuration::m_OptionsState = nullptr;
MainMenuState* Configuration::m_MainMenu = nullptr;
sf::Music* Configuration::m_MainMenuMusic = nullptr;


sf::Color Configuration::Colors::button_fill(86, 20, 19);
sf::Color Configuration::Colors::button_outline(146, 20, 19);
sf::Color Configuration::Colors::label_text(180, 93, 23);
float Configuration::Colors::lighting = 1.4f;


void Configuration::initialize()
{
	initTextures();
	initFonts();
	initSounds();
	initMusics();

	initPlayerInputs();

	initGuiInputs();

	/*rand_init();
	m_Txt_Score.setFont(fonts.get(Fonts::Gui));
	m_Txt_Score.setCharacterSize(24);

	m_Spr_Life.setTexture(textures.get(Textures::PlayerLife));

	musics.get(Musics::Theme).setLoop(true);
	musics.get(Musics::Theme).play();*/

}

#pragma region INIT/TEXTURES
void Configuration::initTextures()
{
	initTexturesGameState();
	initTexturesMenuState();
	initTexturesHangarState();
	initTexturesOptionsState();
	initTexturesPlayer();
	initTexturesWeaponParts();
	initTexturesShips();
}

void Configuration::initTexturesGameState()
{
	textures_game.load(TexturesGameState::cursor, "../media/textures/cursors/Cursor.png");
}

void Configuration::initTexturesMenuState()
{
	textures_menu.load(TexturesMenuState::background	, "../media/backgrounds/MainMenuBG.jpg");
}

void Configuration::initTexturesHangarState()
{
	textures_hangar.load(TexturesHangarState::background	, "../media/backgrounds/hangar.jpg");

	textures_hangar.load(TexturesHangarState::left_arrow	, "../media/textures/left_arrow.png");
	textures_hangar.load(TexturesHangarState::right_arrow	, "../media/textures/right_arrow.png");
}

void Configuration::initTexturesOptionsState()
{
	textures_options.load(TexturesOptionsState::left_arrow	, "../media/textures/GUI/left_arrow.png");
	textures_options.load(TexturesOptionsState::right_arrow	, "../media/textures/GUI/right_arrow.png");

}

void Configuration::initTexturesPlayer()
{
	textures_player.load(TexturesPlayer::player_avatar_0, "../media/textures/avatars/avatar1.jpg");
	textures_player.load(TexturesPlayer::player_avatar_1, "../media/textures/avatars/avatar3.jpg");
	textures_player.load(TexturesPlayer::player_avatar_2, "../media/textures/avatars/avatar4.jpg");
	textures_player.load(TexturesPlayer::player_avatar_3, "../media/textures/avatars/avatar2.jpg");


}

void Configuration::initTexturesWeaponParts()
{

	textures_weaponry.load(TexturesWeaponry::ammo_laser				, "../media/textures/ammunition/lasers/laser_bullets.png");
	textures_weaponry.load(TexturesWeaponry::ammo_missile			, "../media/textures/ammunition/missiles/Missile.png");
	textures_weaponry.load(TexturesWeaponry::ammo_missile_thrusters	, "../media/textures/thrusters/missile_thrusters.png");
	textures_weaponry.load(TexturesWeaponry::ammo_beam				, "../media/textures/ammunition/beams/Red_Laser_Beam.png");

	textures_weaponry.load(TexturesWeaponry::turret_laser			, "../media/textures/weapons/turrettest.png");
}

void Configuration::initTexturesShips()
{
	textures_ships.load(TexturesShips::player_ship		, "../media/textures/ships/player/13B.png");
	textures_ships.load(TexturesShips::player_exhaust	, "../media/textures/thrusters/engine_exhaust.png");
}

#pragma endregion








/* TODO: have a get function that tries to find existing, or loads from file */
void Configuration::initFonts()
{
	fonts.load(Fonts::Gui, "../media/font/trs-million.ttf");
	fonts.load(Fonts::SpaceGui, "../media/font/Chopsic.ttf");
}

void Configuration::initSounds()
{
	////laser
	sounds.load(Sounds::LaserPlayer, "../media/textures/ammunition/lasers/Laser_Bullets.wav");
	sounds.load(Sounds::Missile, "../media/sounds/missile/missile.wav");
	sounds.load(Sounds::Beam, "../media/textures/ammunition/beams/Red_Laser_Beam.wav");

}
void Configuration::initMusics()
{
	musics.load(Musics::MainMenuTheme, "../media/musics/MainMenuTheme.ogg");
}

void Configuration::initPlayerInputs()
{
	playerInputs.map(PlayerInputs::Up,		Action(sf::Keyboard::Up));
	playerInputs.map(PlayerInputs::Right,	Action(sf::Keyboard::Right));
	playerInputs.map(PlayerInputs::Left,	Action(sf::Keyboard::Left));
	playerInputs.map(PlayerInputs::Down,	Action(sf::Keyboard::Down));

	playerInputs.map(PlayerInputs::Up,		Action(sf::Keyboard::W));
	playerInputs.map(PlayerInputs::Right,	Action(sf::Keyboard::D));
	playerInputs.map(PlayerInputs::Left,	Action(sf::Keyboard::A));
	playerInputs.map(PlayerInputs::Down,	Action(sf::Keyboard::S));


	playerInputs.map(PlayerInputs::Shoot,	Action(sf::Keyboard::Space));
}


void Configuration::initGuiInputs()
{
	gui_inputs.map(GuiInputs::N, Action(sf::Keyboard::N, Action::Type::Pressed));
	gui_inputs.map(GuiInputs::O, Action(sf::Keyboard::O, Action::Type::Pressed));
	gui_inputs.map(GuiInputs::H, Action(sf::Keyboard::H, Action::Type::Pressed));
	gui_inputs.map(GuiInputs::Q, Action(sf::Keyboard::Q, Action::Type::Pressed));
	gui_inputs.map(GuiInputs::Escape, Action(sf::Keyboard::Escape, Action::Type::Pressed));
}



