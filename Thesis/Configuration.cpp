#include "pch.h"
#include "Configuration.h"


short int Configuration::m_MasterVolume = 10;
short int Configuration::m_SoundEffectsVolume = 10;
short int Configuration::m_SoundVolume = 20;
short int Configuration::m_DialogueVolume = 20;



ResourceManager<sf::Texture, int> Configuration::textures;
ResourceManager<sf::Texture, int> Configuration::background_textures;
ResourceManager<sf::Font, int> Configuration::fonts;
ResourceManager<sf::SoundBuffer, int> Configuration::sounds;
ResourceManager<sf::Music, int> Configuration::musics;

ActionMap<int> Configuration::playerInputs;
ActionMap<int> Configuration::gui_inputs;

int Configuration::level;
int Configuration::lives;

sf::Vector2f Configuration::boundaries;

sf::RectangleShape Configuration::tar;


PlayerShip* Configuration::player = nullptr;
OptionsState* Configuration::m_Options = nullptr;
MainMenuState* Configuration::m_MainMenu = nullptr;
sf::Music* Configuration::m_MainMenuMusic = nullptr;




int Configuration::m_Score;
sf::Text	Configuration::m_Txt_Score;
sf::Sprite	Configuration::m_Spr_Life;

sf::Color Configuration::Colors::button_fill(86, 20, 19);
sf::Color Configuration::Colors::button_outline(146, 20, 19);
sf::Color Configuration::Colors::label_text(180, 93, 23);
float Configuration::Colors::lighting = 1.4;


void Configuration::initialize()
{
	initTextures();
	initBackgrounds();
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

	lives = level = m_Score = -1;
}

void Configuration::CreateWindow(sf::RenderWindow& window)
{

	std::string title;
	int x = 400, y = 400;
	int framerate = 120;
	bool fullscreen = 0, borderless = 0, vsync = 0;

	std::ifstream settings("../media/config/screen.txt");
	if (!settings.is_open())
		return;


	std::stringstream buffer;
	buffer << settings.rdbuf();
	settings.close();

	std::string name;
	while (buffer >> name) {
		if (name == "title") {
			buffer >> title;
		}
		else if (name == "resolution") {
			buffer >> x >> y;
		}
		else if (name == "framerate") {
			buffer >> framerate;
		}
		else if (name == "fullscreen") {
			buffer >> fullscreen;
		}
		else if (name == "borderless") {
			buffer >> borderless;
		}
		else if (name == "vsync") {
			buffer >> vsync;
		}
	}

	using namespace sf::Style;

	if (fullscreen) {
		if (borderless)
			window.create(sf::VideoMode::getDesktopMode(), title, None);
		else
			window.create(sf::VideoMode::getDesktopMode(), title, Titlebar | Close | Fullscreen);
	}
	else
		window.create(sf::VideoMode(x, y), title, Titlebar | Close);


	window.setFramerateLimit(framerate);
	window.setVerticalSyncEnabled(vsync);
	window.setMouseCursorVisible(false);

	boundaries = sf::Vector2f(window.getSize());
}

void Configuration::ReplaceFirstOccurance(std::string& string, const std::string& toReplace, const std::string& replaceWith)
{
	std::size_t pos = string.find(toReplace);
	if (pos == std::string::npos)
		return;

	string.replace(pos, toReplace.length(), replaceWith);
}

bool Configuration::CheckIfPointContainedInArea(const sf::Vector2f& pos, const sf::Vector2f& size)
{
	if (pos.x > size.x || pos.x < -size.x || pos.y > size.y || pos.y < -size.y)
		return false;
	return true;
}

void Configuration::LoadFileToString(const std::filesystem::path& path, std::string& loadTo)
{
	std::ifstream file(path, std::ios::in | std::ios::binary);
	
	/*const auto  size = std::filesystem::file_size(path);
	loadTo = std::string(size, '\0');
	file.read(loadTo.data(), size);*/
	std::string line;
	while (std::getline(file, line))
		loadTo += line;
}


void Configuration::reset()
{
	level = 1;
	lives = 3;
	m_Score = 3;
	m_Txt_Score.setString("0");
}

bool Configuration::isGameOver()
{
	return lives < 0;
}

void Configuration::addScore(int s)
{
	int old_score = m_Score;
	m_Score += s * level;
	lives += m_Score / 10000 - old_score / 10000;
	m_Txt_Score.setString(std::to_string(m_Score));
}

int Configuration::getScore()
{
	return m_Score;
}

void Configuration::draw(sf::RenderTarget& target)
{
	target.draw(m_Txt_Score);
	for (int i = 0; i < lives; ++i) {
		m_Spr_Life.setPosition(40 * i, 40);
		target.draw(m_Spr_Life);
	}
}
void Configuration::initTextures()
{

	textures.load(Textures::Cursor, "../media/textures/cursors/Cursor.png");	

	textures.load(Textures::LeftArrow, "../media/textures/left_arrow.png");


	textures.load(Textures::PlayerAvatar0, "../media/textures/avatars/avatar1.jpg");
	textures.load(Textures::PlayerAvatar1, "../media/textures/avatars/avatar2.jpg");
	textures.load(Textures::PlayerAvatar2, "../media/textures/avatars/avatar3.jpg");
	textures.load(Textures::PlayerAvatar3, "../media/textures/avatars/avatar4.jpg");



	textures.load(Textures::PlayerShip, "../media/textures/ships/player/13B.png");
	textures.load(Textures::PlayerExhaust, "../media/textures/thrusters/engine_exhaust.png");



	textures.load(Textures::Ammo_Laser, "../media/textures/ammunition/lasers/laser_bullets.png");
	textures.load(Textures::Ammo_Missile, "../media/textures/ammunition/missiles/Missile.png");
	textures.load(Textures::Ammo_Missile_Thrusters, "../media/textures/thrusters/missile_thrusters.png");
	textures.load(Textures::Ammo_Beam, "../media/textures/ammunition/beams/Red_Laser_Beam.png");




	textures.load(Textures::Turret_Laser, "../media/textures/weapons/turrettest.png");
}

void Configuration::initBackgrounds()
{
	background_textures.load(Backgrounds::MainMenu, "../media/backgrounds/MainMenuBG.jpg");
	background_textures.load(Backgrounds::Hangar, "../media/backgrounds/hangar.jpg");
}

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
	//sounds.load(Sounds::LaserEnemy, "../media/sounds/laser2.ogg");
	////saucers
	//sounds.load(Sounds::SaucerSpawn1, "../media/sounds/spawn1.flac");
	//sounds.load(Sounds::SaucerSpawn2, "../media/sounds/spawn2.flac");
	//// Boom
	//sounds.load(Sounds::Boom1, "../media/sounds/boom.flac");
	//sounds.load(Sounds::Boom2, "../media/sounds/boom2.flac");
	//// Explosion
	//sounds.load(Sounds::Explosion1, "../media/sounds/explosion1.flac");
	//sounds.load(Sounds::Explosion2, "../media/sounds/explosion2.flac");
	//sounds.load(Sounds::Explosion3, "../media/sounds/explosion3.flac");
	////others
	//sounds.load(Sounds::Jump, "../media/sounds/hyperspace.flac");
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



