#pragma once

#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "GUIGlobals.h"
#include "ResourceManager.h"
#include "GUI.h"


class Selector
{
public:

	Selector(ResourceManager& t_gameAssets);
	~Selector();
	void clearGUI();
	void update(sf::Time t_deltaTime, MyVector3 mouseClick, int scroll, bool pressed);
	void render(sf::RenderWindow& t_window);
	void initialize();
	void setPosition(MyVector3 t_position);
	void setLength(float lenght);
	std::pair<std::string, int> selectTile(MyVector3 mousePos);

	void runAction(std::string& t_actionString);
	void handleControllerInput();

	void moveWidgets(sf::Vector2f mv);
	void updateWids(sf::Vector2f t_diffOfWid);

private:
	sf::RectangleShape m_displayBox;
	sf::Vertex c1;
	sf::Vertex c2;
	sf::Vertex c3;

	GUI m_slelectorGUI;
	ResourceManager *gameassets;
	float startY = 0;
	sf::VertexArray triangle;
	MyVector3 m_position;
	std::vector<sf::Vector2f> widgetPosArray;
};

