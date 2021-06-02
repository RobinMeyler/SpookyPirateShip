#include "MovingDown.h"

MovingDown::MovingDown(int t_animationType)
{
	// switch statement to see what texture to load
	m_animationType = t_animationType;

	switch (t_animationType)
	{
	case 0:
	{
		// Player Case
		/*texture.loadFromFile("Assets\\playerSpriteSheet.png");
		animatedSprite = new AnimatedSprite(texture);
		sf::IntRect rectOne(0, 0, 64, 77.5);
		sf::IntRect rectTwo(64, 0, 64, 77.5);
		sf::IntRect rectThree(64 * 2, 0, 64, 77.5);
		animatedSprite->addFrame(rectOne);
		animatedSprite->addFrame(rectTwo);
		animatedSprite->addFrame(rectThree);*/

		texture.loadFromFile("Assets\\Lorenzo.png");
		animatedSprite = new AnimatedSprite(texture);
		sf::IntRect rectOne(128, 0, 64, 64);
		sf::IntRect rectTwo(192, 0, 64, 64);
		sf::IntRect rectThree(0, 64, 64, 64);
		sf::IntRect rectFour(192, 0, 64, 64);
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
		sf::IntRect rectOne(32 * 3, 0, 32, 64);
		sf::IntRect rectTwo(32 * 4, 0, 32, 64);
		sf::IntRect rectThree(32 * 5, 0, 32, 64);
		sf::IntRect rectFour(32 * 6, 0, 32, 64);
		sf::IntRect rectFive(32 * 7, 0, 32, 64);
		sf::IntRect rectSix(32 * 8, 0, 32, 64);
		animatedSprite->addFrame(rectOne);
		animatedSprite->addFrame(rectTwo);
		animatedSprite->addFrame(rectThree);
		animatedSprite->addFrame(rectFour);
		animatedSprite->addFrame(rectFive);
		animatedSprite->addFrame(rectSix);*/

		texture.loadFromFile("Assets\\SpikeManSet.png");
		animatedSprite = new AnimatedSprite(texture);
		sf::IntRect rectOne(0, 0, 64, 64);
		sf::IntRect rectTwo(64, 0, 64, 64);
		sf::IntRect rectThree(128, 0, 64, 64);
		sf::IntRect rectFour(192, 0, 64, 64);
		animatedSprite->addFrame(rectOne);
		animatedSprite->addFrame(rectTwo);
		animatedSprite->addFrame(rectThree);
		animatedSprite->addFrame(rectFour);
		break;
	}
	default:
		break;
	}
}

MovingDown::~MovingDown()
{
}

void MovingDown::update()
{
	animatedSprite->update();
}

sf::Sprite& MovingDown::getSprite()
{
	int frame = animatedSprite->getCurrentFrame();
	animatedSprite->setTextureRect(animatedSprite->getFrame(frame));
	//animatedSprite->setOrigin(animatedSprite->getTextureRect().width / 2, animatedSprite->getTextureRect().height / 2);
	return *animatedSprite;
}

void MovingDown::setSpritePos(MyVector3 pos)
{
	getSprite().setPosition(pos);
}

void MovingDown::idle(StateChangeHandler* t_state)
{
	t_state->setCurrent(new Idle(m_animationType));
	delete this;
}

void MovingDown::movingUp(StateChangeHandler* t_state)
{
	t_state->setCurrent(new MovingUp(m_animationType));
	delete this;
}

void MovingDown::movingRight(StateChangeHandler* t_state)
{
	t_state->setCurrent(new MovingRight(m_animationType));
	delete this;
}

void MovingDown::movingLeft(StateChangeHandler* t_state)
{
	t_state->setCurrent(new MovingLeft(m_animationType));
	delete this;
}
