#include "Licence.h"
#include "Game.h"


Licence::Licence(ResourceManager& t_gameAssets)
{
	

}


Licence::~Licence()
{
}

void Licence::initialize()
{

	// set up GUI..
	//Label
	try {
		m_font.loadFromFile("digital-7.ttf");
	}
	catch (...) {

	}
	m_bckGrndTexture.loadFromFile("Assets/Images/boatSkel.jpg");
	m_bckGrndSprite.setTexture(m_bckGrndTexture);


	sf::String labelString = "GHOST PIRATE SHIP";
	Label* licenceLabel = new Label(m_font);
	licenceLabel->setString(labelString);
	licenceLabel->setTextSize(90);
	licenceLabel->setPosition(sf::Vector2f{ 1200, 100 });
	licenceLabel->setTextColor(sf::Color::White);
	licenceLabel->setOutline(sf::Color::White, 2);
	licenceLabel->setUnderLined();
	
	m_GUI.addWidget(licenceLabel);
	m_GUI.setStartFocus(licenceLabel);
	licenceLabel->setAsStarter();
}

void Licence::update(sf::Time t_deltaTime)
{
	m_GUI.update(t_deltaTime);

	//timer bizz..
	dt = m_clock.restart();
	m_timer += dt.asSeconds();
	if (m_timer > 5)
	{
		Game::m_gameMode = GameMode::Splash;
	}
}

void Licence::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_bckGrndSprite);
	m_GUI.render(t_window);
}
