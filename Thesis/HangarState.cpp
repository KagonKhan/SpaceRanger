#include "pch.h"
#include "HangarState.h"
#include "SpaceState.h"
#include "PlayerShip.h"
#include "Player.h"

void HangarState::onCharacterCreationFinished(int sprite_id)
{
	m_Player.emplace(static_cast<Configuration::TexturesPlayer>(sprite_id), static_cast<sf::Vector2f>(m_Window.getSize()));
	m_PlayerInfoArea.emplace(m_Window, *this, m_Player.value());
}


/* CAREFUL updates and draw call order is important since some objects do not exists immediately */
void HangarState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (!m_Creation.isDone()) {
		target.draw(m_Creation);
		return;
	}
	target.draw(m_Background);
	target.draw(m_PlayerInfoArea.value());
	target.draw(m_UI);
}

HangarState::HangarState(sf::RenderWindow& window, std::stack<State*>& states)
	: State(window, states),
	m_Background(Configuration::textures_hangar.get(Configuration::TexturesHangarState::background)),
	m_Creation(m_Window, *this),
	m_Player(std::nullopt),
	m_PlayerInfoArea(std::nullopt)
{
	initBackground();
	initGUI();
}

HangarState::~HangarState()
{

}


/* ==================================      INITIALIZERS      ================================== */
void HangarState::initGUI()
{
	addGUINavigation();

	initGUIKeybinds();
	
}
void HangarState::addGUINavigation()
{
	UnoLayPtr navigation(new UnorderedLayout(opt_ref(m_UI)));
	addButtonBack(navigation);
	addButtonNext(navigation);	
	m_UI.addLayout(std::move(navigation));
}
void HangarState::addButtonBack(UnoLayPtr& unordered_layout)
{
	std::unique_ptr<TextButton> back(new TextButton(opt_ref(*unordered_layout), std::nullopt, sf::Color::Red, "BACK"));
	back->on_click = [this](const sf::Event&, Button& button) {
		m_States.pop();
	};
	unordered_layout->add(std::move(back));
}
void HangarState::addButtonNext(UnoLayPtr& unordered_layout)
{
	std::unique_ptr<TextButton> next(new TextButton(opt_ref(*unordered_layout), std::nullopt, sf::Color::Red, "NEXT"));
	next->on_click = [this](const sf::Event&, Button& button) {
		m_States.push(new SpaceState(m_Window, m_States, m_Player.value().getPlayerShip()));
	};
	next->setPosition(sf::Vector2f(m_Window.getSize().x - next->getSize().x, 0.f));
	unordered_layout->add(std::move(next));
}
void HangarState::initGUIKeybinds()
{
	m_UI.bind(Configuration::GuiInputs::Escape, [this](const sf::Event& sfevent) {
		m_States.pop();
		});

}
void HangarState::initBackground()
{
	sf::Vector2f window_size(m_Window.getSize());
	sf::Vector2f bg_size(m_Background.getGlobalBounds().width, m_Background.getGlobalBounds().height);

	sf::Vector2f scale;
	scale.x = window_size.x / bg_size.x;
	scale.y = window_size.y / bg_size.y;
	m_Background.setScale(scale);
}


/* ==================================      UPDATES      ================================== */
void HangarState::processEvents(const sf::Event& sfevent)
{
	if (!m_Creation.isDone()) {
		m_Creation.processEvents(sfevent);
		return;
	}

	m_PlayerInfoArea.value().processEvents(sfevent);
	m_UI.processEvent(sfevent);
}
void HangarState::update(const sf::Time& deltaTime)
{


}


/* ==================================      FUNCTIONS      ================================== */