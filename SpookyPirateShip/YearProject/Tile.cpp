#include "Tile.h"

Tile::Tile(ResourceManager& t_gameAssets, std::string t_tag, int t_index, int t_direction) :
	index{ t_index },
	rotDirection{ t_direction }
{
	m_tileSprite.setTexture(t_gameAssets.m_gameTextures[t_tag]);
	//int temp = rotDirection;
	//m_tileSprite.setOrigin(32, 32);
	//while (temp > 0)
	//{
	//	m_tileSprite.rotate(90);
	//	temp--;
	//}
	//m_tileSprite.rotate(90);
	//m_tileSprite.setOrigin(0, 0);
}

Tile::~Tile()
{
}

void Tile::setTexture(std::string st)
{
}

void Tile::setPosition(sf::Vector2f pos)
{
	position = pos;
	m_tileSprite.setPosition(position);
}

sf::Vector2f Tile::getPosition()
{
	return position;
}

sf::Sprite* Tile::getSprite()
{
	return &m_tileSprite;
}

int Tile::getIndex()
{
	return index;
}

void Tile::setLayer(Layer L)
{
	m_tileLayer = L;
}

void Tile::setRotation(int newRot)
{
	rotDirection = newRot;
}

Layer Tile::getLayer()
{
	return m_tileLayer;
}
