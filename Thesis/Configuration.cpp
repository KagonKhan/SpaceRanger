
#include "pch.h"
#include "Configuration.h"


short int Configuration::m_MasterVolume = 50;
short int Configuration::m_SoundEffectsVolume = 50; 
short int Configuration::m_SoundVolume = 50;
short int Configuration::m_DialogueVolume = 20;


#pragma region TEXTURES
ResourceManager<sf::Texture, Configuration::TexturesGameState>		Configuration::textures_game;
ResourceManager<sf::Texture, Configuration::TexturesMenuState>		Configuration::textures_menu;
ResourceManager<sf::Texture, Configuration::TexturesHangarState>	Configuration::textures_hangar;
ResourceManager<sf::Texture, Configuration::TexturesOptionsState>	Configuration::textures_options;
ResourceManager<sf::Texture, Configuration::TexturesSpaceState>		Configuration::textures_space;
ResourceManager<sf::Texture, Configuration::TexturesPlayer>			Configuration::textures_player;
ResourceManager<sf::Texture, Configuration::TexturesWeaponry>		Configuration::textures_weaponry;
ResourceManager<sf::Texture, Configuration::TexturesShips>			Configuration::textures_ships;
#pragma endregion


ResourceManager<sf::Font, int> Configuration::fonts;
ResourceManager<sf::SoundBuffer, Configuration::Sounds> Configuration::sounds;
ResourceManager<sf::Music, int> Configuration::musics;

ActionMap<int> Configuration::playerInputs;
ActionMap<int> Configuration::gui_inputs;



sf::Vector2f Configuration::boundaries;

sf::RectangleShape Configuration::tar;


MainMenuState* Configuration::m_MainMenu = nullptr;
sf::Music* Configuration::m_MainMenuMusic = nullptr;
PlayerShip* Configuration::player = nullptr;



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
}

#pragma region INIT/TEXTURES

void Configuration::initTextures()
{
	initTexturesGameState();
	initTexturesMenuState();
	initTexturesHangarState();
	initTexturesOptionsState();
	initTexturesSpaceState();
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
	textures_menu.load(TexturesMenuState::background	,	"../media/backgrounds/MainMenuBG.jpg");

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
void Configuration::initTexturesSpaceState()
{
	textures_space.load(TexturesSpaceState::background	, "../media/textures/space/stars.png").setRepeated(true);
	textures_space.load(TexturesSpaceState::nebula_0	, "../media/textures/space/nebula1.png");
	textures_space.load(TexturesSpaceState::nebula_1	, "../media/textures/space/nebula2.png");
	textures_space.load(TexturesSpaceState::nebula_2	, "../media/textures/space/nebula3.png");
	textures_space.load(TexturesSpaceState::planet_0	, "../media/textures/space/planet1.png");
	textures_space.load(TexturesSpaceState::planet_1	, "../media/textures/space/planet2.png");
	textures_space.load(TexturesSpaceState::planet_2	, "../media/textures/space/planet3.png");
	textures_space.load(TexturesSpaceState::planet_3	, "../media/textures/space/planet4.png");
	textures_space.load(TexturesSpaceState::planet_4	, "../media/textures/space/planet5.png");

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
	textures_weaponry.load(TexturesWeaponry::ammo_laser_hit			, "../media/textures/ammunition/lasers/laser_hit.png");
	
	textures_weaponry.load(TexturesWeaponry::ammo_missile			, "../media/textures/ammunition/missiles/Missile.png");
	textures_weaponry.load(TexturesWeaponry::ammo_missile_thrusters	, "../media/textures/thrusters/missile_thrusters.png");
	textures_weaponry.load(TexturesWeaponry::ammo_missile_death_anim, "../media/textures/ammunition/missiles/missile_death_anim.png");
	
	textures_weaponry.load(TexturesWeaponry::ammo_beam				, "../media/textures/ammunition/beams/Red_Laser_Beam.png");

	textures_weaponry.load(TexturesWeaponry::turret_laser			, "../media/textures/weapons/turrettest.png");
}
void Configuration::initTexturesShips()
{
	textures_ships.load(TexturesShips::player_ship		, "../media/textures/ships/player/13B.png");
	textures_ships.load(TexturesShips::player_exhaust	, "../media/textures/thrusters/engine_exhaust.png");

	textures_ships.load(TexturesShips::enemy_ship_minigun	, "../media/textures/ships/enemy/minigun.png");
	textures_ships.load(TexturesShips::enemy_ship_support	, "../media/textures/ships/enemy/support.png");
	textures_ships.load(TexturesShips::enemy_ship_beam		, "../media/textures/ships/enemy/beam.png");
	textures_ships.load(TexturesShips::enemy_ship_rocket	, "../media/textures/ships/enemy/rocket.png");
	textures_ships.load(TexturesShips::enemy_ship_scout		, "../media/textures/ships/enemy/scout.png");
	textures_ships.load(TexturesShips::enemy_ship_tank		, "../media/textures/ships/enemy/tank.png");
	textures_ships.load(TexturesShips::enemy_ship_scout_v2	, "../media/textures/ships/enemy/scout_v2.png");
	textures_ships.load(TexturesShips::enemy_ship_stealth	, "../media/textures/ships/enemy/stealth.png");
	textures_ships.load(TexturesShips::enemy_ship_boss		, "../media/textures/ships/enemy/boss.png");

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
	sounds.load(Sounds::laser, "../media/sounds/laser/laser.wav");
	sounds.load(Sounds::laser_hit, "../media/sounds/laser/laser_hit.wav");

	sounds.load(Sounds::missile, "../media/sounds/missile/missile.wav");
	sounds.load(Sounds::missile_explosion, "../media/sounds/missile/explosion_4.wav");
	
	
	sounds.load(Sounds::beam, "../media/textures/ammunition/beams/Red_Laser_Beam.wav");

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



