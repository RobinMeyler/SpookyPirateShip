#include "Key.h"

Key::Key(Door * t_door, ResourceManager& t_gameAssets) :
	m_matchingDoor{t_door},
	isHeld{false},
	m_keyTexture{ t_gameAssets.m_gameTextures["Key"] }
{
	m_keySprite.setTexture(m_keyTexture);
	m_keySprite.setScale(0.5f, 0.5f);
}

void Key::render(sf::RenderWindow& t_window, sf::Shader& lighting)
{
	if (isHeld == false)
	{
		t_window.draw(m_keySprite, &lighting);
	}
	else
	{
		t_window.draw(m_keySprite);
	}
}

void Key::setPosition(sf::Vector2f t_position)
{
	m_keySprite.setPosition(t_position);
}

sf::Vector2f Key::getPosition()
{
	return m_keySprite.getPosition();
}

bool Key::held()
{
	return isHeld;
}

void Key::nameKey(std::string name)
{
	m_keyName = name;
}

void Key::setHeld(bool t_isHeld)
{
	isHeld = t_isHeld;
}

void Key::setColor(sf::Color c)
{
	m_keySprite.setColor(c);
}


