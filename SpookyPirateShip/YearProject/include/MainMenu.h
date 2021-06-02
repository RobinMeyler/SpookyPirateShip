#pragma once

#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "GUIGlobals.h"
#include "ResourceManager.h"
#include "GUI.h"
#include "Xbox360Controller.h"


class MainMenu
{
public:
	MainMenu(ResourceManager& t_gameAssets);
	~MainMenu();

	void initialize();
	void update(sf::Time t_deltaTime, MyVector3 mouseClick, bool pressed);
	void render(sf::RenderWindow& t_window);

private:
	sf::Texture m_bckGrndTexture;
	sf::Sprite m_bckGrndSprite;
	sf::Font m_font;
	MyVector3 m_mousePos;
	sf::Sprite m_body;
	sf::Sprite renderSprite;
	sf::RenderTexture renderTexture;
	sf::Texture distortionMap;
	sf::Shader shader1;
	sf::Clock clock;

	GUI m_GUI;

	sf::SoundBuffer clickSoundBuffer;
	sf::Sound clickSound;
};