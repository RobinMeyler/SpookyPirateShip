#pragma once
#include "State.h"
#include "AnimatedSprite.h"
#include "Idle.h"
#include "MovingDown.h"
#include "MovingLeft.h"

class StateChangeHandler; // forward decleration

class MovingRight : public State
{
public:
	MovingRight(int t_animationType);
	~MovingRight();
	int m_animationType; // used at initialisation to see which texture to load

	void update() override;
	sf::Sprite& getSprite() override; // get current sprite to draw

	sf::Texture texture;
	AnimatedSprite* animatedSprite;

	//Override Functions
	void setSpritePos(MyVector3 pos);
	void idle(StateChangeHandler* t_state);
	virtual void movingDown(StateChangeHandler* t_state);
	virtual void movingUp(StateChangeHandler* t_state);
	virtual void movingLeft(StateChangeHandler* t_state);
};

#include "StateChangeHandler.h"