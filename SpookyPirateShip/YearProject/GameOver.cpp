#include "GameOver.h"
#include "Game.h"

GameOver::GameOver(ResourceManager& t_gameAssets)
{
}

GameOver::~GameOver()
{
}

void GameOver::initialize()
{
	// set up GUI..
	//Label
	try {
		m_font.loadFromFile("BBrick.ttf");
	}
	catch (...) {

	}

	sf::String labelString = "You failed to complete the\nlevel. Better luck next time!\nPress the 'E' key to exit.";
	Label* gameOverText = new Label(m_font);
	gameOverText->setString(labelString);
	gameOverText->setTextSize(40);
	gameOverText->setTextColor(sf::Color::Red);
	gameOverText->setOutline(sf::Color::White, 2);
	gameOverText->setUnderLined();
	gameOverText->setOrigin(sf::Vector2f(gameOverText->getSize().x / 2, gameOverText->getSize().y / 2));
	gameOverText->setPosition(Game::m_screenView.getCenter());


	/*sf::Color b = sf::Color::White;
	Button* button1 = new Button(b, 600, 100);
	button1->setString("Retry!", 40);
	button1->setTextColor(sf::Color(sf::Color::Black));
	button1->setButtonTag("retry");
	button1->setFont(m_font);
	button1->resetOrigin();
	button1->setOrigin(300, 50);
	button1->setPosition(sf::Vector2f(Game::m_screenView.getCenter().x, Game::m_screenView.getCenter().y + 200));
	button1->setRotation(0);
	button1->setOutline(sf::Color::Magenta, 2);

	button1->setInputType(InputType::mouse);
	button1->setHighLightSpeed(10);
	button1->setFlashColor(sf::Color::Black);*/


	m_GUI.addWidget(gameOverText);
	//m_GUI.addWidget(button1);
	m_GUI.setStartFocus(gameOverText);
	gameOverText->setAsStarter();
	//m_GUI.setInput(InputType::mouse);
	//m_GUI.setAnimationStyle(buttonAnimationStyle::FLASH);
}

void GameOver::update(sf::Time t_deltaTime, MyVector3 mouseClick, bool pressed)
{
	m_mousePos = mouseClick;
	m_GUI.update(t_deltaTime);
	m_GUI.getWidgets().at(0)->setPosition(sf::Vector2f(Game::m_screenView.getCenter().x, Game::m_screenView.getCenter().y - 200));
	//m_GUI.getWidgets().at(1)->setPosition(sf::Vector2f(Game::m_screenView.getCenter().x, Game::m_screenView.getCenter().y + 200));
	if (pressed == true)
	{
		std::string st = m_GUI.findSelected(sf::Vector2f(mouseClick.x, mouseClick.y + 200)).first;
		if (st == "retry")
		{
			Game::m_gameMode = GameMode::MainMenu;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		Game::m_gameMode = GameMode::MainMenu;
		Game::m_screenView = sf::View(sf::FloatRect(0, 0, 1920, 1280));
		Game::m_screenView.setCenter(955, 640);
	}
}

void GameOver::render(sf::RenderWindow& t_window)
{
	m_GUI.render(t_window);
}
