#pragma once

#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "GUIGlobals.h"
#include "ResourceManager.h"
#include "GUI.h"
#include "Label.h"
#include <ctime>

class Licence
{
public:
	Licence(ResourceManager& t_gameAssets);
	~Licence();

	void initialize();
	void update(sf::Time t_deltaTime);
	void render(sf::RenderWindow& t_window);

private:
	sf::Texture m_bckGrndTexture;
	sf::Sprite m_bckGrndSprite;
	sf::Font m_font;

	sf::Clock m_clock;
	sf::Time dt;
	float m_timer{ 0.0 };	// timer for screen change (from licence to splash)

	GUI m_GUI;

};

