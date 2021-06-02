#pragma once

#include "State.h"
#include "MovingUp.h"
#include "MovingDown.h"
#include "MovingRight.h"
#include "MovingLeft.h"
#include "AnimatedSprite.h"
#include "StateChangeHandler.h"


class Idle : public State
{
public:
	Idle(int t_animationType);
	~Idle();
	int m_animationType; // used at initialisation to see which texture to load

	void update() override;
	sf::Sprite& getSprite() override; // get current sprite to draw

	sf::Texture texture;
	AnimatedSprite* animatedSprite;

	//Override Functions
	void setSpritePos(MyVector3 pos);
	void movingUp(StateChangeHandler* t_state);
	void movingDown(StateChangeHandler* t_state);
	void movingRight(StateChangeHandler* t_state);
	void movingLeft(StateChangeHandler* t_state);
};