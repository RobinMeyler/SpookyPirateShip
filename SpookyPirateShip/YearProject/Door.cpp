#include "Door.h"

Door::Door(sf::Vector2f placementPosition, ResourceManager& t_gameAssets) :
	m_openStat{ doorStatus::closed },
	m_isActive{true}, 
	m_position{ placementPosition },
	openingTime{0.0f},
	m_doorTexture(t_gameAssets.m_gameTextures["Test4"])		// Fix name
{
	// Make intRect and use for texture
	m_doorSprite.setTexture(m_doorTexture);
	m_doorSprite.setPosition(m_position);
}

void Door::update(sf::Time t_deltaTime, Player* t_player)
{
	if (m_openStat == doorStatus::closed)
	{
		// Check for player with key
		 
		float dist = (t_player->getPosition() - m_doorSprite.getPosition()).length();
		if(dist < 80)
		{
			std::vector<Key*> playerKeys = t_player->heldKeys();
			for (int i = 0; i < playerKeys.size(); i++)
			{
				if (playerKeys.at(i) == m_matchingKey)
				{
					m_openStat = doorStatus::opened;
				}
			}
		}
		
	}
	else if (m_openStat == doorStatus::opening)
	{
		openingTime += t_deltaTime.asSeconds();
		if (openingTime < 0.5f)
		{
			// IntRec 1
		}
		else if (openingTime < 1.f && openingTime > 0.5f)
		{
			// IntRec 2
		}
		else
		{
			// IntRec 3
			m_isActive = false;
		}

		// Small animation
	}
	else if (m_openStat == doorStatus::opened)
	{
		m_isActive = false;
	}

}

void Door::render(sf::RenderWindow& t_window, sf::Shader& lighting)
{
	if (m_isActive == true)
	{
		t_window.draw(m_doorSprite, & lighting);
	}
}

sf::Vector2f Door::getPosition()
{
	return m_doorSprite.getPosition();
}

bool Door::isActive()
{
	return m_isActive;
}

void Door::setColor(sf::Color c)
{
	m_doorSprite.setColor(c);
}

void Door::setKey(Key* t_key)
{
	m_matchingKey = t_key;
}
