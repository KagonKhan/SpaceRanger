#include "pch.h"
#include "OptionsState.h"


void OptionsState::processEvents(const sf::Event& sfevent)
{
	ui.processEvent(sfevent);
}

OptionsState::OptionsState(sf::RenderWindow& window, std::stack<State*>& states, sf::Sprite& bgsprite)
	: State(window, states), ui(window), m_NavUI(window), m_BackgroundSprite(bgsprite),
	m_Title("OPTIONS")
{
	std::cout << "\nOptions State constructor\n";
	initGUI();
	initTitle();
}

OptionsState::~OptionsState()
{
	std::cout << "\nOptions State destructor\n";
}

void OptionsState::initGUI()
{
	Checkbox* fullscreen = new Checkbox("Fullscreen");
	fullscreen->on_click = [this](const sf::Event&, Button& button) {
		OptionsState::fullscreen(button);
	};

	TextButton* back = new TextButton("BACK");
	back->on_click = [this](const sf::Event&, Button& button) {
		m_States.pop();
	};

	VerticalLayout* layout = new VerticalLayout;
	layout->add(fullscreen);
	layout->add(back);

	layout->setPosition(sf::Vector2f(m_Window.getSize()) / 2.f);

	ui.addLayout(layout);



	std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();

	for (auto x : modes)
		std::cout << x.width << " " << x.height << "\n";

}

void OptionsState::initTitle()
{
	m_Title.setCharacterSize(100);
	m_Title.setLetterSpacing(8);
	m_Title.setOutlineThickness(9);
	m_Title.setOutlineColor(sf::Color::Blue);
	sf::Vector2f title_position((m_Window.getSize().x - m_Title.getSize().x) / 2.f, 150);

	m_Title.setPosition(title_position);

}

void OptionsState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_BackgroundSprite);
	target.draw(m_Title);
	target.draw(ui);
}

void OptionsState::fullscreen(Button& button)
{

	if (!button.getStatus())
		m_Window.create(sf::VideoMode(2560, 1440), "test", sf::Style::Fullscreen);
	else
		m_Window.create(sf::VideoMode(1920, 1080), "test", sf::Style::Default);

	m_Window.setFramerateLimit(120);
	Configuration::m_MainMenu->recalculatePositions();
	recalculatePositions();
}

void OptionsState::update(const sf::Time& deltaTime)
{
}



void OptionsState::recalculatePositions()
{
	Configuration::m_MainMenu->m_BackgroundTexture;

	sf::Vector2u win_size = m_Window.getSize();
	sf::Vector2u tex_size = Configuration::m_MainMenu->m_BackgroundTexture.getSize();
	sf::IntRect rect(unsigned(0), (tex_size - win_size).y / (unsigned)2, win_size.x, win_size.y);
	m_BackgroundSprite.setTextureRect(rect);


	sf::Vector2f title_position((m_Window.getSize().x - m_Title.getSize().x) / 2.f, 150);

	m_Title.setPosition(title_position);


	ui.setLayoutPosition(sf::Vector2f(m_Window.getSize()) / 2.f);
}
