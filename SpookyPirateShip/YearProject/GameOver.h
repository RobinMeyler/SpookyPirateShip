#pragma once

#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "GUIGlobals.h"
#include "ResourceManager.h"
#include "GUI.h"
#include "Label.h"
#include <ctime>

class GameOver
{
public:
	GameOver(ResourceManager& t_gameAssets);
	~GameOver();

	void initialize();
	void update(sf::Time t_deltaTime, MyVector3 mouseClick, bool pressed);
	void render(sf::RenderWindow& t_window);

private:
	sf::Font m_font;

	MyVector3 m_mousePos;
	GUI m_GUI;
};
