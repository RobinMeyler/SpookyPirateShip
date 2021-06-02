#include "Collider.h"


bool Collider::collisionPosSize(sf::Vector2f t_Pos1, sf::Vector2f t_size1, sf::Vector2f t_Pos2, sf::Vector2f t_size2)
{
	sf::Vector2f m_Pos1Min = t_Pos1;
	sf::Vector2f m_Pos1Max = t_Pos1 + t_size1;
	sf::Vector2f m_Pos2Min = t_Pos2;
	sf::Vector2f m_Pos2max = t_Pos2 + t_size2;

	if ((m_Pos2max.x < m_Pos1Min.x)
		|| (m_Pos1Max.x < m_Pos2Min.x)
		|| (m_Pos2max.y < m_Pos1Min.y)
		|| (m_Pos1Max.y < m_Pos2Min.y))
	{
		return false;
	}
	return true;
}

bool Collider::collisionSpriteSprite(const sf::Sprite & object1, const sf::Sprite & object2)
{
	int collsionNum = 0;

	int X1min = object1.getPosition().x;
	int x1Max = X1min + object1.getTexture()->getSize().x;
	int Y1min = object1.getPosition().y;
	int Y1max = Y1min + object1.getTexture()->getSize().y;

	int X2min = object2.getPosition().x;
	int x2Max = X2min + object2.getTexture()->getSize().x;
	int Y2min = object2.getPosition().y;
	int Y2max = Y2min + object2.getTexture()->getSize().y;

	// Bottom Right / Top left
	if ((x1Max > X2min)
		&& (X1min < X2min)

		&& (Y1max > Y2min)
		&& (Y1min < Y2min))
	{
		std::cout << " Bottom Right" << std::endl;
		collsionNum++;
	}

	// Top Right / Bottom left
	if ((x1Max > X2min)
		&& (X1min < X2min)

		&& (Y1max > Y2max)
		&& (Y1min < Y2max))
	{
		std::cout << " Top Right" << std::endl;
		collsionNum++;
	}

	// Bottom Left / Top Right
	if ((x1Max > x2Max)
		&& (X1min < x2Max)

		&& (Y1max > Y2min)
		&& (Y1min < Y2min))
	{
		std::cout << " Bottom Left" << std::endl;
		collsionNum++;
	}

	// Top Left / Bottom right
	if ((x1Max > x2Max)
		&& (X1min < x2Max)

		&& (Y1max > Y2max)
		&& (Y1min < Y2max))
	{
		std::cout << " Top Left" << std::endl;
		collsionNum++;
	}

	if (collsionNum > 0)
	{
		return true;
	}
	return false;
}
