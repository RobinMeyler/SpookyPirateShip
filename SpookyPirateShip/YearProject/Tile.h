#pragma once

#include <iostream>
#include <string>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "GUIGlobals.h"
#include "GUI.h"
#include "ResourceManager.h"
#include "Selector.h"


class Tile
{
public:
	Tile() {};
	Tile(ResourceManager& t_gameAssets, std::string t_tag, int t_index, int t_rotation);
	~Tile();
	void setTexture(std::string st);
	void setPosition(sf::Vector2f pos);
	sf::Vector2f getPosition();
	sf::Sprite* getSprite();
	int getIndex();
	void setLayer(Layer L);
	void setRotation(int newRot);
	Layer getLayer();
	sf::Vector2f position;
	std::vector<sf::Vector2f> m_enemyPositionList;
	int rotDirection = 0;
private:
	sf::Sprite m_tileSprite;
	
	int index{ 0 };
	Layer m_tileLayer{ Layer::play };
	
};

