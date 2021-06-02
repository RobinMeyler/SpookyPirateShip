#pragma once

#include "State.h"
#include "AnimatedSprite.h"
//#include "StateChangeHandler.h"
#include "Idle.h"
#include "MovingDown.h"
#include "MovingRight.h"
#include "MovingLeft.h"

class StateChangeHandler;

class MovingUp : public State
{
public:
	MovingUp(int t_animationType);
	~MovingUp();
	int m_animationType; // used at initialisation to see which texture to load

	void update() override;
	sf::Sprite& getSprite() override; // get current sprite to draw

	sf::Texture texture;
	AnimatedSprite* animatedSprite;

	//Override Functions
	void setSpritePos(MyVector3 pos);
	void idle(StateChangeHandler* t_state);
	virtual void movingDown(StateChangeHandler* t_state);
	virtual void movingRight(StateChangeHandler* t_state);
	virtual void movingLeft(StateChangeHandler* t_state);
};

#include "StateChangeHandler.h"