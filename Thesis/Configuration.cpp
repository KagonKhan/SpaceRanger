#include "Configuration.h"
ResourceManager<sf::Texture, int> Configuration::textures;
ResourceManager<sf::Font, int> Configuration::fonts;
ResourceManager<sf::SoundBuffer, int> Configuration::sounds;
ResourceManager<sf::Music, int> Configuration::musics;

ActionMap<int> Configuration::playerInputs;
ActionMap<int> Configuration::gui_inputs;

int Configuration::level;
int Configuration::lives;

Player* Configuration::player = nullptr;

int Configuration::m_Score;
sf::Text	Configuration::m_Txt_Score;
sf::Sprite	Configuration::m_Spr_Life;


void Configuration::initialize()
{
	initTextures();
	initFonts();
	initSounds();
	initMusics();

	initPlayerInputs();

	/*rand_init();
	m_Txt_Score.setFont(fonts.get(Fonts::Gui));
	m_Txt_Score.setCharacterSize(24);

	m_Spr_Life.setTexture(textures.get(Textures::PlayerLife));

	musics.get(Musics::Theme).setLoop(true);
	musics.get(Musics::Theme).play();*/

	lives = level = m_Score = -1;
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
	/*textures.load(Textures::Player, "../media/Player/Ship.png");
	textures.load(Textures::PlayerLife, "../media/Player/life.png");
	textures.load(Textures::BigSaucer, "../media/Saucer/Big.png");
	textures.load(Textures::SmallSaucer, "../media/Saucer/Small.png");
	textures.load(Textures::BigMeteor1, "../media/Meteor/Big1.png");
	textures.load(Textures::BigMeteor2, "../media/Meteor/Big2.png");
	textures.load(Textures::BigMeteor3, "../media/Meteor/Big3.png");
	textures.load(Textures::BigMeteor4, "../media/Meteor/Big4.png");
	textures.load(Textures::MediumMeteor1, "../media/Meteor/Medium1.png");
	textures.load(Textures::MediumMeteor2, "../media/Meteor/Medium2.png");
	textures.load(Textures::SmallMeteor1, "../media/Meteor/Small1.png");
	textures.load(Textures::SmallMeteor2, "../media/Meteor/Small2.png");
	textures.load(Textures::SmallMeteor3, "../media/Meteor/Small3.png");
	textures.load(Textures::SmallMeteor4, "../media/Meteor/Small4.png");
	textures.load(Textures::ShootPlayer, "../media/Shoot/Player.png");
	textures.load(Textures::ShootSaucer, "../media/Shoot/Saucer.png");*/
}


void Configuration::initFonts()
{
	fonts.load(Fonts::Gui, "../media/font/trs-million.ttf");
}

void Configuration::initSounds()
{
	////laser
	//sounds.load(Sounds::LaserPlayer, "../media/sounds/laser1.ogg");
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
	/*musics.load(Musics::Theme, "../media/musics/theme.ogg");*/
}

void Configuration::initPlayerInputs()
{
	/*playerInputs.Map(PlayerInputs::Up, Action(sf::Keyboard::Up));
	playerInputs.Map(PlayerInputs::Right, Action(sf::Keyboard::Right));
	playerInputs.Map(PlayerInputs::Left, Action(sf::Keyboard::Left));
	playerInputs.Map(PlayerInputs::Hyperspace, Action(sf::Keyboard::Down, Action::Type::Released));
	playerInputs.Map(PlayerInputs::Shoot, Action(sf::Keyboard::Space));*/
}


void Configuration::initGuiInputs()
{
	gui_inputs.map(GuiInputs::Escape, Action(sf::Keyboard::Escape, Action::Type::Pressed));
}



