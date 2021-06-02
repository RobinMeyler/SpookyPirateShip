#include "Options.h"
#include "Game.h"



Options::Options(ResourceManager& t_gameAssets)
{
	ptrGameAssets = &t_gameAssets;
	
}


Options::~Options()
{
}

void Options::clearGUI()
{
	m_GUI.clearGUI();
}

void Options::initialize()
{
	if (!clickSoundBuffer.loadFromFile("Assets/Audio/buttonSound.wav"))
	{
		std::cout << "ERROR, loading click sound (main menu)" << std::endl;
	}
	clickSound.setBuffer(clickSoundBuffer);

	m_bckGrndTexture.loadFromFile("Assets/Images/boatSkel.jpg");
	m_bckGrndSprite.setTexture(m_bckGrndTexture);

	try {
		m_font.loadFromFile("BBrick.ttf");
	}
	catch (...) {

	}

	sf::String labelString = "Options";
	Label* optionsLabel = new Label(m_font);
	optionsLabel->setString(labelString);
	optionsLabel->setTextSize(120);
	optionsLabel->setTextColor(sf::Color::Red);
	optionsLabel->setOutline(sf::Color::White, 2);
	optionsLabel->setUnderLined();
	optionsLabel->setPosition(sf::Vector2f{ 150, 150 });
	

	sf::Color b = sf::Color::White;
	Button* button1 = new Button(b, 600, 100);
	button1->setString("Exit", 40);
	button1->setTextColor(sf::Color(sf::Color::Black));
	button1->setButtonTag("exit");
	button1->setFont(m_font);
	button1->resetOrigin();
	//button1->setOrigin(300, 50);
	button1->setPosition(sf::Vector2f(150, 1000));
	button1->setRotation(0);
	button1->setOutline(sf::Color::Magenta, 2);

	button1->setInputType(InputType::mouse);
	button1->setHighLightSpeed(10);
	button1->setFlashColor(sf::Color::Green);

	sf::Color blue = sf::Color(sf::Color::Blue);
	Button* soundVolume = new Button(blue, 420, 75);
	soundVolume->setString("Sound Volume:", 50);
	soundVolume->setTextColor(sf::Color(sf::Color::Red));
	soundVolume->setFont(m_font);
	//soundVolume->setOrigin(210, 37.5);
	soundVolume->setPosition(sf::Vector2f(70, 560));
	soundVolume->setOutline(sf::Color(sf::Color::White), 3);
	soundVolume->setHighLightSpeed(6);
	soundVolume->setFlashColor(sf::Color::Yellow);
	soundVolume->setActionString("Volume Change");

	// Volume Level button image
	m_volumeLevelRectangle.setTexture(NULL, true);
	m_volumeLevelRectangle.setSize(sf::Vector2f(100, 75));
	m_volumeLevelRectangle.setPosition(sf::Vector2f(870, 600));
	m_volumeLevelRectangle.setOrigin(m_volumeLevelRectangle.getLocalBounds().width / 2, m_volumeLevelRectangle.getLocalBounds().height / 2);
	m_volumeLevelRectangle.setFillColor(sf::Color::Blue);

	//Volume level text
	m_volumeText.setString(std::to_string(Game::MUSIC_VOLUME) + "%");
	m_volumeText.setFont(m_font);
	m_volumeText.setCharacterSize(35);
	m_volumeText.setFillColor(sf::Color::Green);
	m_volumeText.setPosition(sf::Vector2f(835, 570));

	VolumeKnob* volumeKnob = new VolumeKnob(ptrGameAssets->m_gameTextures["Volume Knob"]);
	volumeKnob->setPosition(sf::Vector2f(700, 600));
	volumeKnob->setActionString("Knob");


	m_GUI.addWidget(optionsLabel);
	m_GUI.addWidget(button1);
	m_GUI.addWidget(soundVolume);
	m_GUI.addWidget(volumeKnob);
	m_GUI.setStartFocus(volumeKnob);
	volumeKnob->setAsStarter();
	m_GUI.setInput(InputType::mouse);
	m_GUI.setAnimationStyle(buttonAnimationStyle::FLASH);


	m_info.setString("press the up and down \narrows to alter volume");
	m_info.setFont(m_font);
	m_info.setCharacterSize(45);
	m_info.setFillColor(sf::Color::Green);
	m_info.setPosition(sf::Vector2f(955, 470));
}

void Options::update(sf::Time t_deltaTime, MyVector3 mouseClick, bool pressed)
{
	m_GUI.update(t_deltaTime, mouseClick);
	if (pressed == true)
	{
		clickSound.play();

		std::string st = m_GUI.findSelected(mouseClick).first;
		if (st == "exit" && Game::m_screenChangeTimer < 0)
		{
			//Game::m_screenView = sf::View(sf::FloatRect(0, 0, 800, 600));
			Game::m_gameMode = GameMode::MainMenu;
			Game::m_screenChangeTimer = 0.5f;
		}
	}

	if (m_GUI.getCurrentWidget()->getActionString() == "Knob")	// volumeKnob actionString == Knob
	{
		if (m_count > 15)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				m_GUI.getCurrentWidget()->increaseRotation();
				m_GUI.getCurrentWidget()->increaseRotation();
				m_GUI.getCurrentWidget()->increaseRotation();
				if (Game::MUSIC_VOLUME < 100)
				{
					Game::MUSIC_VOLUME++;
				}
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				m_GUI.getCurrentWidget()->decreaseRotation();
				m_GUI.getCurrentWidget()->decreaseRotation();
				m_GUI.getCurrentWidget()->decreaseRotation();
				if (Game::MUSIC_VOLUME > 0)
				{
					Game::MUSIC_VOLUME--;
				}
			}
		}
	}
	m_count++;
	m_volumeText.setString(std::to_string(Game::MUSIC_VOLUME) + "%");
}

void Options::render(sf::RenderWindow & t_window)
{
	t_window.draw(m_bckGrndSprite);
	t_window.draw(m_volumeLevelRectangle);
	t_window.draw(m_volumeText);
	t_window.draw(m_info);
	m_GUI.render(t_window);
}

void Options::handleControllerInput()
{
	
}

void Options::runAction(std::string & t_actionString)
{
	
}
