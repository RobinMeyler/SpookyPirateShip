#pragma once

#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "ResourceManager.h"
#include "GUIGlobals.h"
#include "GUI.h"
#include "Xbox360Controller.h"

class Pause
{
public:
	Pause(ResourceManager& t_gameAssets);
	~Pause();
	void clearGUI();
	void initialize();
	void update(sf::Time t_deltaTime);
	void render(sf::RenderWindow & t_window);
	void handleControllerInput();
	void runAction(std::string & t_actionString);

private:
	
};

