#include "Game.h"

// Made by: Robin Meyler, Josh Browne

// Preset Static variables for the whole project
// These span across all screens and can be altered in many ---------------------------------------------------
GameMode Game::m_gameMode{ GameMode::Licence };
GameMode Game::m_previousMode{ GameMode::Licence };			// Used to allow many pathways to screens E.G Options
std::string Game::m_currentSaveName{ "" };
std::string Game::m_currentLoadName{ "" };
bool Game::m_loading{ false };
bool Game::m_saving{ false };
bool Game::m_resetPlay{ false };
bool Game::m_win{ true };
sf::View Game::m_screenView{ sf::FloatRect(0,0, 1920, 1280) };
float Game::m_screenChangeTimer{ 0.5f };
int Game::MUSIC_VOLUME{ 100 };
// Contructor
Game::Game() :
	m_renderWin{ sf::VideoMode{ 1920, 1280, 1 }, "Year Project"}
{
	intialize();
	srand(time(nullptr));
}

/// Destructor
Game::~Game()
{
	if (m_rulesScreen != nullptr)				// Don't delete nothing.
	{
		delete m_rulesScreen;					// Delete the heap memory allocated in the initialize
	}
	if (m_licenceScreen != nullptr)
	{
		delete m_licenceScreen;
	}
	if (m_soundOptionsScreen != nullptr)
	{
		delete m_soundOptionsScreen;
	}
	if (m_splashScreen != nullptr)
	{
		delete m_splashScreen;
	}
	if (m_gameplayScreen != nullptr)
	{
		delete m_gameplayScreen;
	}
	if (m_pauseScreen != nullptr)				// Don't delete nothing.
	{
		delete m_pauseScreen;					// Delete the heap memory allocated in the initialize
	}
	
	if (m_mainMenuScreen != nullptr)
	{
		delete m_mainMenuScreen;
	}

	if (m_winningScreen != nullptr)
	{
		delete m_winningScreen;
	}
	if (m_levelEditor != nullptr)
	{
		delete m_levelEditor;
	}
	if (m_gameOverScreen != nullptr)
	{
		delete m_gameOverScreen;
	}
	if (m_optionsScreen != nullptr)
	{
		delete m_optionsScreen;
	}
}

// Loop designed to work at equal speed on all PCs
// If a PC is slower, it will update the same amount of times
// And render less often
void Game::run()
{
	sf::Clock gameClock;											// Game clock
	sf::Time timeTakenForUpdate = sf::Time::Zero;					// No lag on first input
	sf::Time timePerFrame = sf::seconds(1.f / 60.f);				// 60 frames per second
	while (m_renderWin.isOpen())									// Loop
	{
		processInput();												// Check for input
		timeTakenForUpdate += gameClock.restart();					// Returns time take to do the loop
		while (timeTakenForUpdate > timePerFrame)					// Update enough times to catch up on updates missed during the lag time
		{
			timeTakenForUpdate -= timePerFrame;						// Decrement lag
			processInput();											// More checks, the more accurate input to display will be
			update(timePerFrame);									// Update
		}
		render();
	}
}

// Process PC input
void Game::processInput()
{
	sf::Event event;
	while (m_renderWin.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
		{
			m_renderWin.close();
		}
		if (sf::Event::KeyPressed == event.type)
		{
			if (sf::Keyboard::Escape == event.key.code)
			{
				m_renderWin.close();
			}
		}
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				m_mouseClicked = true;
			}
			if (event.mouseButton.button == sf::Mouse::Right)
			{
				m_mouseClickedRight = true;
			}
		}
		if (event.type == sf::Event::MouseButtonReleased)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				m_mouseClicked = false;
			}
			if (event.mouseButton.button == sf::Mouse::Right)
			{
				m_mouseClickedRight = false;
			}
		}
		if (event.type == sf::Event::MouseWheelMoved)
		{
			// display number of ticks mouse wheel has moved
			m_scroll = event.mouseWheel.delta;
			//std::cout << event.mouseWheel.delta << '\n';
		}
	}

}

// Updates Game
void Game::update(sf::Time t_deltaTime)
{
	m_mousePosition = sf::Mouse::getPosition(m_renderWin);
	Game::m_screenChangeTimer -= t_deltaTime.asSeconds();
	switch (m_gameMode)					// Switch to control the screens
	{
	case GameMode::Licence:
		m_licenceScreen->update(t_deltaTime);
		break;
	case GameMode::Splash:
		m_splashScreen->update(t_deltaTime, m_mousePosition, m_mouseClicked);
		break;
	case GameMode::MainMenu:
		m_mainMenuScreen->update(t_deltaTime, m_mousePosition, m_mouseClicked);
		break;
	case GameMode::Gameplay:
		m_gameplayScreen->update(t_deltaTime, m_mousePosition, m_mouseClicked, m_renderWin);
		break;
	case GameMode::Options:
		m_optionsScreen->update(t_deltaTime, m_mousePosition, m_mouseClicked);
		break;
	case GameMode::LevelEditor:
		m_levelEditor->update(t_deltaTime, m_mousePosition, m_scroll, m_mouseClicked, m_mouseClickedRight, m_renderWin);
		break;
	case GameMode::Rules:
		m_rulesScreen->update(t_deltaTime);
		break;
	case GameMode::SoundOptions:
		m_soundOptionsScreen->update(t_deltaTime);
		break;
	case GameMode::Pause:
		m_pauseScreen->update(t_deltaTime);
		break;
	case GameMode::Winning:
		m_winningScreen->update(t_deltaTime, m_mousePosition, m_mouseClicked);
		break;
	case GameMode::GameOver:
		m_gameOverScreen->update(t_deltaTime, m_mousePosition, m_mouseClicked);
		break;
	default:
		break;
	}
//	m_mouseClicked = false;
	//m_mouseClickedRight = false;
	m_scroll = 0;

	m_gameplayScreen->updateVolume(); // do this so volume always updates
}

// Renders
void Game::render()
{
	m_renderWin.clear(sf::Color::Black);
	m_renderWin.setView(Game::m_screenView);
	switch (m_gameMode)								// Swtich to control the screens
	{
	case GameMode::Licence:
		m_licenceScreen->render(m_renderWin);
		break;
	case GameMode::Splash:
		m_splashScreen->render(m_renderWin);
		break;
	case GameMode::MainMenu:
		m_mainMenuScreen->render(m_renderWin);
		break;
	case GameMode::Gameplay:
		m_gameplayScreen->render(m_renderWin);
		break;
	case GameMode::Options:
		m_optionsScreen->render(m_renderWin);
		break;
	case GameMode::LevelEditor:
		m_levelEditor->render(m_renderWin);
		break;
	case GameMode::Rules:
		m_rulesScreen->render(m_renderWin);
		break;
	case GameMode::SoundOptions:
		m_soundOptionsScreen->render(m_renderWin);
		break;
	case GameMode::Pause:
		m_pauseScreen->render(m_renderWin);
		break;
	case GameMode::Winning:
		m_winningScreen->render(m_renderWin);
		break;
	case GameMode::GameOver:
		m_gameplayScreen->render(m_renderWin);
		m_gameOverScreen->render(m_renderWin);
		break;
	default:
		break;
	}
	
	m_renderWin.display();
}

void Game::intialize()
{
	m_gameAssets.addTexture("Test0", "Assets/Images/CornerBlockDark.png");
	m_gameAssets.addTexture("Test1", "Assets/Images/WallUp.png");
	m_gameAssets.addTexture("Test2", "Assets/Images/BackBorderWall.png");
	m_gameAssets.addTexture("Test3", "Assets/Images/WallSide.png");
	m_gameAssets.addTexture("Test4", "Assets/Images/SpookyDoor.png");
	m_gameAssets.addTexture("Test5", "Assets/Images/player.png");
	m_gameAssets.addTexture("Test6", "Assets/Images/enemy.png");
	m_gameAssets.addTexture("Test7", "Assets/Images/SpookyFloorLight.png");
	m_gameAssets.addTexture("Test8", "Assets/Images/sword.png");
	m_gameAssets.addTexture("Test9", "Assets/Images/crate.png");
	m_gameAssets.addTexture("Test10", "Assets/Images/SpookyFloor.png");
	m_gameAssets.addTexture("Test12", "Assets/Images/crate.png");
	m_gameAssets.addTexture("Test11", "Assets/Images/crate2.png");
	m_gameAssets.addTexture("Test13", "Assets/Images/tnt.png");
	m_gameAssets.addTexture("Test14", "Assets/Images/Door.png");
	m_gameAssets.addTexture("Test20", "Assets/Images/KeyFull.png");
	m_gameAssets.addTexture("Rock", "Assets/Images/Rock.png");
	m_gameAssets.addTexture("Key", "Assets/Images/Key.png");
	m_gameAssets.addTexture("Volume Knob", "Assets/Images/knob-png-2.png");


	// Initialize screens
	m_rulesScreen = new Rules(m_gameAssets);
	m_gameplayScreen = new Gameplay(m_gameAssets);
	//m_soundOptionsScreen = new SoundOptions(m_gameAssets);
	m_splashScreen = new Splash(m_gameAssets);
	m_licenceScreen = new Licence(m_gameAssets);
	m_mainMenuScreen = new MainMenu(m_gameAssets);
	m_pauseScreen = new Pause(m_gameAssets);
	m_optionsScreen = new Options(m_gameAssets);
	m_levelEditor = new LevelEditor(m_gameAssets);
	m_winningScreen = new Winning(m_gameAssets);
	m_gameOverScreen = new GameOver(m_gameAssets);

	// Screen intializing -------------------
	m_winningScreen->intialize();
	m_levelEditor->initialize();
	m_licenceScreen->initialize();
	m_rulesScreen->initialize();
	m_gameplayScreen->initialize();
	m_splashScreen->initialize();
	m_mainMenuScreen->initialize();
	m_pauseScreen->initialize();
	m_optionsScreen->initialize();
	m_gameOverScreen->initialize();

}
