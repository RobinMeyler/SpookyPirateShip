#pragma once

#include "GUIGlobals.h"
#include "Player.h"
#include "Key.h"
#include "ResourceManager.h"

class Door
{
public:

	Door(sf::Vector2f placementPosition, ResourceManager & t_gameAssets);
	void update(sf::Time t_deltaTime, Player * t_player);
	void render(sf::RenderWindow& t_window, sf::Shader& lighting);
	sf::Vector2f getPosition();
	bool isActive();
	void setColor(sf::Color c);
	void setKey(Key * t_key);
private:
	doorStatus m_openStat;
	bool m_isActive;
	sf::Vector2f m_position;
	sf::Texture m_doorTexture;
	sf::Sprite m_doorSprite;
	Key* m_matchingKey;
	float openingTime;
	ResourceManager* m_gameAssets;
};