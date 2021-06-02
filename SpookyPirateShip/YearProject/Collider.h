#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class Collider
{
public:

	bool static collisionPosSize(sf::Vector2f t_Pos1, sf::Vector2f t_size1, sf::Vector2f t_Pos2, sf::Vector2f t_size2);   // AABB - AABB collision
	bool static collisionSpriteSprite(const sf::Sprite& object1, const sf::Sprite& object2);	// Sprite collider

};

