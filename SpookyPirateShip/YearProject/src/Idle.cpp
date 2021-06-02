#include "Idle.h"

Idle::Idle(int t_animationType)
{
	m_animationType = t_animationType;

	switch (t_animationType)
	{
	case 0:
	{
		// Player Case
		/*texture.loadFromFile("Assets\\playerSpriteSheet.png");
		animatedSprite = new AnimatedSprite(texture);
		sf::IntRect rectOne(0, 0, 64, 77.5);
		animatedSprite->addFrame(rectOne);*/

		texture.loadFromFile("Assets\\Lorenzo.png");
		animatedSprite = new AnimatedSprite(texture);
		sf::IntRect rectOne(64, 0, 64, 64);
		animatedSprite->addFrame(rectOne);
		break;
	}
	case 1:
	{
		//Enemy Case
		/*texture.loadFromFile("Assets\\zombie_n_skeleton2.png");
		animatedSprite = new AnimatedSprite(texture);
		sf::IntRect rectOne(32 * 3, 0, 32, 64);
		animatedSprite->addFrame(rectOne);*/

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

Idle::~Idle()
{
}

void Idle::update()
{
	animatedSprite->update();
}

sf::Sprite& Idle::getSprite()
{
	//sf::Sprite temp;
	int frame = animatedSprite->getCurrentFrame();
	//temp.setTexture(animatedSprite->getTexture());
	//temp.setTextureRect(animatedSprite->getFrame(frame));
	animatedSprite->setTextureRect(animatedSprite->getFrame(frame));
	//animatedSprite->setOrigin(animatedSprite->getTextureRect().width / 2, animatedSprite->getTextureRect().height / 2);   NOT NEEDED NOW
	return *animatedSprite;
}

void Idle::setSpritePos(MyVector3 pos)
{
	getSprite().setPosition(pos);
}

void Idle::movingUp(StateChangeHandler* t_state)
{
	t_state->setCurrent(new MovingUp(m_animationType));
	delete this;
}

void Idle::movingDown(StateChangeHandler* t_state)
{
	t_state->setCurrent(new MovingDown(m_animationType));
	delete this;
}

void Idle::movingRight(StateChangeHandler* t_state)
{
	t_state->setCurrent(new MovingRight(m_animationType));
	delete this;
}

void Idle::movingLeft(StateChangeHandler* t_state)
{
	t_state->setCurrent(new MovingLeft(m_animationType));
	delete this;
}
