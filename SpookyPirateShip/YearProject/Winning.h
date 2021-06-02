#pragma once

#include <iostream>
#include "SFML/Graphics.hpp"
#include "ResourceManager.h"
#include "SFML/Audio.hpp"
#include "GUIGlobals.h"
#include "GUI.h"

enum class state
{
	loading,
	saving
};
class Winning
{
public:
	Winning() {};
	Winning(ResourceManager& t_gameAssets);
	~Winning();

	void clearGUI();
	void intialize();
	void update(sf::Time t_deltaTime, MyVector3 mouseClick, bool pressed);
	void render(sf::RenderWindow & t_window);

	std::string newName(sf::Time t_deltaTime, MyVector3 mouseClick, bool pressed);


private:
	GUI m_winningGUI;
	GUI m_deleteGUI;
	GUI m_endGUI;
	std::vector<std::string> m_savedLevelNames;
	sf::Text m_name;
	sf::Font m_font;
	int m_count{ 0 };
	float m_delay{ 0 };
	int buttonCount{ 0 };
	state m_state;
	float doSave{ false };
};

