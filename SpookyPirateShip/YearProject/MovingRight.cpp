#include "MovingRight.h"

MovingRight::MovingRight(int t_animationType)
{
	m_animationType = t_animationType;
	switch (t_animationType)
	{
	case 0:
	{
		// Player Case
		/*texture.loadFromFile("Assets\\playerSpriteSheet.png");
		animatedSprite = new AnimatedSprite(texture);
		sf::IntRect rectOne(0, 77.5 * 3, 64, 77.5);
		sf::IntRect rectTwo(64, 77.5 * 3, 64, 77.5);
		sf::IntRect rectThree(64 * 2, 77.5 * 3, 64, 77.5);
		animatedSprite->addFrame(rectOne);
		animatedSprite->addFrame(rectTwo);
		animatedSprite->addFrame(rectThree);*/

		texture.loadFromFile("Assets\\Lorenzo.png");
		animatedSprite = new AnimatedSprite(texture);
		sf::IntRect rectOne(64, 128, 64, 64);
		sf::IntRect rectTwo(128, 128, 64, 64);
		sf::IntRect rectThree(192, 128, 64, 64);
		sf::IntRect rectFour(0, 192, 64, 64);
		animatedSprite->addFrame(rectOne);
		animatedSprite->addFrame(rectTwo);
		animatedSprite->addFrame(rectThree);
		animatedSprite->addFrame(rectFour);
		break;
	}
	case 1:
	{
		//Enemy Case
		/*texture.loadFromFile("Assets\\zombie_n_skeleton2.png");
		animatedSprite = new AnimatedSprite(texture);
		sf::IntRect rectOne(32 * 3, 64 * 2, 32, 64);
		sf::IntRect rectTwo(32 * 4, 64 * 2, 32, 64);
		sf::IntRect rectThree(32 * 5, 64 * 2, 32, 64);
		sf::IntRect rectFour(32 * 6, 64 * 2, 32, 64);
		sf::IntRect rectFive(32 * 7, 64 * 2, 32, 64);
		sf::IntRect rectSix(32 * 8, 64 * 2, 32, 64);
		animatedSprite->addFrame(rectOne);
		animatedSprite->addFrame(rectTwo);
		animatedSprite->addFrame(rectThree);
		animatedSprite->addFrame(rectFour);
		animatedSprite->addFrame(rectFive);
		animatedSprite->addFrame(rectSix);*/

		texture.loadFromFile("Assets\\SpikeManSet.png");
		animatedSprite = new AnimatedSprite(texture);
		sf::IntRect rectOne(0, 64, 64, 64);
		sf::IntRect rectTwo(64, 64, 64, 64);
		sf::IntRect rectThree(128, 64, 64, 64);
		sf::IntRect rectFour(192, 64, 64, 64);
		sf::IntRect rectFive(0, 128, 64, 64);
		sf::IntRect rectSix(64, 128, 64, 64);
		sf::IntRect rectSeven(128, 128, 64, 64);
		sf::IntRect rectEight(192, 128, 64, 64);
		animatedSprite->addFrame(rectOne);
		animatedSprite->addFrame(rectTwo);
		animatedSprite->addFrame(rectThree);
		animatedSprite->addFrame(rectFour);
		animatedSprite->addFrame(rectFive);
		animatedSprite->addFrame(rectSix);
		animatedSprite->addFrame(rectSeven);
		animatedSprite->addFrame(rectEight);
		break;
	}
	default:
		break;

	}
}

MovingRight::~MovingRight()
{
}

void MovingRight::update()
{
	animatedSprite->update();
}

sf::Sprite& MovingRight::getSprite()
{
	int frame = animatedSprite->getCurrentFrame();
	animatedSprite->setTextureRect(animatedSprite->getFrame(frame));
	//animatedSprite->setOrigin(animatedSprite->getTextureRect().width / 2, animatedSprite->getTextureRect().height / 2);
	return *animatedSprite;
}

void MovingRight::setSpritePos(MyVector3 pos)
{
	getSprite().setPosition(pos);
}

void MovingRight::idle(StateChangeHandler* t_state)
{
	t_state->setCurrent(new Idle(m_animationType));
	delete this;
}

void MovingRight::movingDown(StateChangeHandler* t_state)
{
	t_state->setCurrent(new MovingDown(m_animationType));
	delete this;
}
void MovingRight::movingUp(StateChangeHandler* t_state)
{
	t_state->setCurrent(new MovingUp(m_animationType));
	delete this;
}

void MovingRight::movingLeft(StateChangeHandler* t_state)
{
	t_state->setCurrent(new MovingLeft(m_animationType));
	delete this;
}
