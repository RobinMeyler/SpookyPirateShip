#pragma once

#include "State.h"
#include "AnimatedSprite.h"
//#include "StateChangeHandler.h"
#include "Idle.h"
#include "MovingUp.h"
#include "MovingRight.h"
#include "MovingLeft.h"

class StateChangeHandler;

class MovingDown : public State
{
public:
	MovingDown(int t_animationType);
	~MovingDown();
	int m_animationType; // used at initialisation to see which texture to load

	void update() override;
	sf::Sprite& getSprite() override; // get current sprite to draw

	sf::Texture texture;
	AnimatedSprite* animatedSprite;

	//Override Functions
	void setSpritePos(MyVector3 pos);
	void idle(StateChangeHandler* t_state);
	void movingUp(StateChangeHandler* t_state);
	void movingRight(StateChangeHandler* t_state);
	void movingLeft(StateChangeHandler* t_state);
};

#include "StateChangeHandler.h"