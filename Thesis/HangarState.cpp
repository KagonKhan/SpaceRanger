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
void HangarState::draw(sf::RenderTarget& target, sf::RenderStates) const
{
	if (!m_Creation.isDone()) {
		target.draw(m_Creation);
		return;
	}
	target.draw(m_Background);
	target.draw(m_PlayerInfoArea.value());
	target.draw(m_UI);
}

HangarState::HangarState(sf::RenderWindow& window, std::stack<State::ptr>& states)
	: State(window, states),
	m_Creation(m_Window, *this)
{
	initBackground();
	initGUI();
}




/* ==================================      INITIALIZERS      ================================== */
void HangarState::initGUI()
{
	addGUINavigation();

	initGUIKeybinds();
	
}
void HangarState::addGUINavigation()
{
	auto navigation = std::make_unique<UnorderedLayout>(opt_ref(m_UI));
	addButtonBack(navigation);
	addButtonNext(navigation);	
	m_UI.addLayout(std::move(navigation));
}
void HangarState::addButtonBack(UnorderedLayout::ptr& unordered_layout)
{
	auto back = std::make_unique<TextButton>(opt_ref(*unordered_layout), std::nullopt, sf::Color::Red, "BACK");
	back->on_click = [this](const sf::Event&, Button&) {
		m_ShouldQuit = true;
	};
	unordered_layout->add(std::move(back));
}
void HangarState::addButtonNext(UnorderedLayout::ptr& unordered_layout)
{
	auto next = std::make_unique<TextButton>(opt_ref(*unordered_layout), std::nullopt, sf::Color::Red, "NEXT");
	next->on_click = [this](const sf::Event&, Button&) {
		m_States.emplace(new SpaceState(m_Window, m_States));
	};

	next->setPosition(sf::Vector2f(static_cast<float>(m_Window.getSize().x) - next->getSize().x, 0.f));
	unordered_layout->add(std::move(next));
}
void HangarState::initGUIKeybinds()
{
	m_UI.bind(Configuration::GuiInputs::Escape, [this](const sf::Event&) {
		m_ShouldQuit = true;
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
	if (sfevent.type == sf::Event::KeyPressed)
		if (sfevent.key.code == sf::Keyboard::Key::Escape)
			m_ShouldQuit = true;

	if (!m_Creation.isDone()) {
		m_Creation.processEvents(sfevent);
		return;
	}

	m_PlayerInfoArea.value().processEvents(sfevent);
	m_UI.processEvent(sfevent);
}
void HangarState::update(const sf::Time& deltaTime)
{
	if (m_ShouldQuit)
		m_States.pop();

}


/* ==================================      FUNCTIONS      ================================== */