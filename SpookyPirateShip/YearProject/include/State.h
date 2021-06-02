#pragma once
#include "SFML/Graphics.hpp"
#include "MyVector3.h"

//#include "StateChangeHandler.h"
class StateChangeHandler;

// Parent class to all states
class State
{
public:
	virtual void update() {};
	virtual sf::Sprite& getSprite() { return temp; }; // get current sprite to draw

	virtual void setSpritePos(MyVector3 pos) {};

	virtual void idle(StateChangeHandler* t_state) {};
	virtual void movingUp(StateChangeHandler* t_state) {};
	virtual void movingDown(StateChangeHandler* t_state) {};
	virtual void movingRight(StateChangeHandler* t_state) {};
	virtual void movingLeft(StateChangeHandler* t_state) {};

	sf::Sprite temp;
};

#include "StateChangeHandler.h"