#pragma once


#include "GUIGlobals.h"
#include "ResourceManager.h"
	
class Door;

class Key
{
public:
	Key(Door * t_door, ResourceManager& t_gameAssets);
	void render(sf::RenderWindow& t_window, sf::Shader& lighting);
	void setPosition(sf::Vector2f t_position);
	sf::Vector2f getPosition();
	bool held();
	void nameKey(std::string name);
	void setHeld(bool t_isHeld);
	void setColor(sf::Color c);
private:
	bool isHeld;
	std::string m_keyName;
	sf::Vector2f m_position;
	sf::Texture m_keyTexture;
	sf::Sprite m_keySprite;
	Door* m_matchingDoor;
};

#include "Door.h"