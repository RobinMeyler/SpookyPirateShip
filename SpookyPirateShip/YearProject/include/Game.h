#pragma once

// Made by: Robin Meyler, Josh Browne

// Extra ----------------------------
#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "GUIGlobals.h"
#include "MyVector3.h"
#include "Xbox360Controller.h"
#include <String>
#include <ctime>
#include "ResourceManager.h"
#include "Player.h"
#include "Enemy.h"
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */


// Screens -------------------------
#include "Licence.h"
#include "Splash.h"
#include "MainMenu.h"
#include "Gameplay.h"
#include "Options.h"
#include "Rules.h"
#include "SoundOptions.h"
#include "Pause.h"
#include "LevelEditor.h"
#include "Winning.h"
#include "GameOver.h"

// GUI -----------------------------
#include "CharacterInput.h"
#include "CheckBox.h"
#include "HorizontalSlider.h"
#include "VerticalSlider.h"
#include "Button.h"
#include "RadioButton.h"
#include "GUI.h"

class Game
{
public:
	Game();
	~Game();
	void run();
	// Intialized and commented in cpp -------------------------
	static GameMode m_gameMode;
	static GameMode m_previousMode;
	static std::string m_currentSaveName;
	static std::string m_currentLoadName;
	static bool m_loading;
	static bool m_saving;
	static bool m_resetPlay;
	static bool m_win;
	static float m_screenChangeTimer;
	static sf::View m_screenView;
	static int MUSIC_VOLUME;

protected:
	void intialize();
	void update(sf::Time t_deltaTime);
	void processInput();
	void render();

	// SFML parts ---------------------------
	sf::Music m_mainMusic;
	sf::RenderWindow m_renderWin;
	sf::Text m_name;
	sf::Font m_font;

	/*Screens*/
	Licence *m_licenceScreen;
	Splash *m_splashScreen;
	MainMenu *m_mainMenuScreen;
	Gameplay *m_gameplayScreen;
	Options *m_optionsScreen;
	LevelEditor *m_levelEditor;
	Rules *m_rulesScreen;
	SoundOptions *m_soundOptionsScreen;
	Winning* m_winningScreen;
	Pause *m_pauseScreen;
	GameOver* m_gameOverScreen;

	GUI myGUI;
	Widget * m_currentWidgetFocus{ nullptr };



private:
	MyVector3 m_mousePosition;
	bool m_mouseClicked{ false };
	bool m_mouseClickedRight{ false };
	int m_scroll;
	ResourceManager m_gameAssets;


	Player m_player;
	Enemy m_enemyOne;
};

