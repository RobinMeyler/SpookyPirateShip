#pragma once

#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "GUIGlobals.h"
#include "ResourceManager.h"
#include "GUI.h"
#include "Xbox360Controller.h"

class Options
{
public:
	Options(ResourceManager& t_gameAssets);
	~Options();
	void clearGUI();
	void initialize();
	void update(sf::Time t_deltaTime, MyVector3 mouseClick, bool pressedc);
	void render(sf::RenderWindow & t_window);
	void handleControllerInput();
	void runAction(std::string & t_actionString);

private:
	sf::Texture m_bckGrndTexture;
	sf::Sprite m_bckGrndSprite;
	sf::Font m_font;
	GUI m_GUI;
	sf::RectangleShape m_volumeLevelRectangle;
	sf::Text m_volumeText;

	sf::Text m_info; // info to display

	int m_count{ 0 };

	ResourceManager* ptrGameAssets;

	sf::SoundBuffer clickSoundBuffer;
	sf::Sound clickSound;
};

