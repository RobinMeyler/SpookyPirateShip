#include "Winning.h"
#include "Game.h"
#include <fstream>


Winning::Winning(ResourceManager& t_gameAssets)
{
}


Winning::~Winning()
{
}


void Winning::update(sf::Time t_deltaTime, MyVector3 mouseClick, bool pressed)
{
	if (Game::m_saving == true)
	{
		m_delay += t_deltaTime.asSeconds();
		m_winningGUI.update(t_deltaTime);
		if (pressed == true && m_delay > 0.25f)
		{
			if (m_winningGUI.findSelected(mouseClick).first != "doSave")
			{
				std::string st = m_winningGUI.findSelected(mouseClick).first;
				m_name.setString(m_name.getString() + st);
				m_delay = 0;
			}
			else
			{
				doSave = true;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
		{
			doSave = true;
		}
		if (doSave == true)
		{
			doSave = false;
			bool skip = false;
			for (int i = 0; i < m_savedLevelNames.size(); i++)
			{
				if (m_name.getString() == m_savedLevelNames.at(i))
				{
					skip = true;
					break;
				}
			}
			Game::m_gameMode = GameMode::LevelEditor;
			Game::m_saving = false;
			Game::m_currentSaveName = m_name.getString();
			if (skip == false)
			{
				m_savedLevelNames.push_back(m_name.getString());
				sf::Color w = sf::Color::White;
				Button* button = new Button(w, 384, 128);
				button->setButtonTag(m_name.getString());
				button->setString(m_name.getString(), 40);
				button->setFont(m_font);
				button->resetOrigin();
				button->setIndex(0);
				button->setPosition(sf::Vector2f(200, 128 * (buttonCount)));
				button->setRotation(0);
				button->setOutline(sf::Color::Black, 3);

				m_deleteGUI.addWidget(button);
				m_name.setString("");
				buttonCount++;
			}
		}
	}
	else if (Game::m_loading == true)
	{
		m_deleteGUI.update(t_deltaTime);
		if (pressed == true)
		{
			std::string st = m_deleteGUI.findSelected(mouseClick).first;
			for (int i = 0; i < m_savedLevelNames.size(); i++)
			{
				if (st == m_savedLevelNames.at(i))
				{
					Game::m_currentLoadName = st;
					Game::m_gameMode = GameMode::LevelEditor;
					Game::m_loading = false;
				}
			}
		}

	}
	else if (Game::m_win == true)
	{
		m_endGUI.update(t_deltaTime, mouseClick);
		if (pressed == true)
		{
			if (m_winningGUI.findSelected(mouseClick).first != "Menu" && Game::m_screenChangeTimer < 0)
			{
				Game::m_screenChangeTimer = 0.5f;
				Game::m_resetPlay = true;
				Game::m_gameMode = GameMode::MainMenu;
			}
		}
	}
}

void Winning::render(sf::RenderWindow& t_window)
{
	if (Game::m_loading == true)
	{
		m_deleteGUI.render(t_window);
	}
	else if (Game::m_saving == true)
	{
		m_winningGUI.render(t_window);
	}
	else if (Game::m_win == true)
	{
		m_endGUI.render(t_window);
	}
	t_window.draw(m_name);
}

std::string Winning::newName(sf::Time t_deltaTime, MyVector3 mouseClick, bool pressed)
{
	std::string newName;
	while (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) == false)
	{
		m_delay += t_deltaTime.asSeconds();
		m_winningGUI.update(t_deltaTime);
		if (m_delay > 0.25f)
		{
			std::string st = m_winningGUI.findSelected(mouseClick).first;
			m_name.setString(m_name.getString() + st);
			m_delay = 0;
		}

	}
	newName = m_name.getString();
	m_name.setString("");
	return newName;
}


void Winning::clearGUI()
{
	m_winningGUI.clearGUI();
	m_deleteGUI.clearGUI();
	m_winningGUI.clearGUI();
}

void Winning::intialize()
{
	m_font.loadFromFile("digital-7.ttf");
	m_name.setFont(m_font);
	m_name.setCharacterSize(100);
	m_name.setPosition(200, 800);
	m_name.setString("");

	Label* title = new Label(m_font);
	title->setPosition(sf::Vector2f{ 400, 100 });
	title->setFont(m_font);
	title->setTextSize(60);
	title->setString("Enter your name:");

	title->setOrigin();
	m_winningGUI.addWidget(title);
	m_winningGUI.setViewMinMax(0, SCREEN_HEIGHT, 0);

	CharacterInput* nameInput = new CharacterInput(120, m_font);
	nameInput->setPosition(sf::Vector2f{ 100, 200 });


	sf::Color b = sf::Color::White;
	Button* buttonE = new Button(b, 1000, 100);
	buttonE->setString("Save", 40);
	buttonE->setTextColor(sf::Color(sf::Color::Blue));
	buttonE->setOutline(sf::Color::Blue, 2);
	buttonE->setButtonTag("doSave");
	buttonE->setFont(m_font);
	buttonE->setPosition(sf::Vector2f(100, 1000));
	buttonE->setRotation(0);
	m_winningGUI.addWidget(buttonE);
	m_winningGUI.addWidget(nameInput);

	m_winningGUI.setStartFocus(nameInput->getCurrentTableFocus());

	sf::Color c = sf::Color::White;
	Button* button1 = new Button(c, 600, 100);
	button1->setString("Play", 40);
	button1->setTextColor(sf::Color(sf::Color::Blue));
	button1->setOutline(sf::Color::Blue, 2);
	button1->setButtonTag("Play");
	button1->setFont(m_font);
	button1->setPosition(sf::Vector2f(100, 700));
	button1->setRotation(0);

	std::string name;
	std::string stg = "SavedLevels.txt";
	std::ifstream file(stg);

	// Read in names and scores from file
	if (file.is_open())
	{
		while (file >> name)
		{
			std::string lvl = name;
			m_savedLevelNames.push_back(name);

			Button* button = new Button(b, 384, 128);
			button->setButtonTag(lvl);
			button->setString(name, 40);
			button->setFont(m_font);
			button->resetOrigin();
			button->setIndex(0);
			button->setPosition(sf::Vector2f(0, 128 * (buttonCount)));
			button->setRotation(0);
			button->setOutline(sf::Color::Black, 3);
			m_deleteGUI.setStartFocus(button);
			m_deleteGUI.addWidget(button);
			buttonCount++;
		}
	}
	m_deleteGUI.setStartFocus(nameInput->getCurrentTableFocus());

	Label* title2 = new Label(m_font);
	title2->setPosition(sf::Vector2f{ 200, 100 });
	title2->setFont(m_font);
	title2->setTextSize(60);
	title2->setString("Good win bro");

	Button* button4 = new Button(b, 1000, 100);
	button4->setString("Menu", 40);
	button4->setTextColor(sf::Color(sf::Color::Blue));
	button4->setButtonTag("Menu");
	button4->setFont(m_font);
	button4->setPosition(sf::Vector2f(450, 975));
	button4->setRotation(0);
	button4->setOutline(sf::Color::Blue, 2);
	button4->resetOrigin();
	button4->setInputType(InputType::mouse);
	button4->setHighLightSpeed(10);
	button4->setFlashColor(sf::Color::Green);

	m_endGUI.addWidget(title2);
	m_endGUI.addWidget(button4);
	m_endGUI.setStartFocus(button4);
	button4->setAsStarter();
	m_endGUI.setInput(InputType::mouse);
	m_endGUI.setAnimationStyle(buttonAnimationStyle::FLASH);

}
