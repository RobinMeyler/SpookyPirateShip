#pragma once

// Made by: Robin Meyler, Josh Browne
// Date: Feburary - march 2019
// Time taken: ~ 40 hours



#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>
#include "GUIGlobals.h"
#include "Xbox360Controller.h"

// Mostly Virtual class that acts as a grouping Super class or all thew my Widgets in the GUI manager
class Widget
{
public:
	Widget();
	~Widget();

	virtual void update(sf::Time t_deltaTime);
	virtual void render(sf::RenderWindow & t_window);

	virtual void highlighted(sf::Time t_deltaTime);
	virtual void notHightlighted();

	// Setters ---------------------------------
	virtual void setPosition(sf::Vector2f t_pos);
	virtual void setRotation(float t_rotation);
	virtual float getRotation();
	virtual void setActionString(std::string t_actionString);
	virtual void setAnimationStyle(buttonAnimationStyle t_anime);
	virtual std::string *action();

	//Josh's additions for joint project..
	virtual void setButtonAsFaded();
	virtual void setButtonAsNormal();
	virtual void setButtonAsTransparent() {};
	virtual void setAsStarter();
	virtual std::string getText();
	virtual void setString(std::string  t_message, float t_size) {};

	// Getters --------------------------------
	virtual bool getFocusStatus();
	virtual GUItype getWidgetType();
	virtual bool getIfFilled();				// Button, check box, Radio
	virtual Widget * getUp();
	virtual Widget * getDown();
	virtual Widget * getRight();
	virtual Widget * getLeft();
	virtual sf::Vector2f getPosition();
	virtual float getPositionY();
	virtual std::string getActionString();

	// Added by Josh for VolumeKnob
	virtual void increaseRotation();
	virtual void decreaseRotation();

	// New
	virtual bool checkCollision(sf::Vector3f t_position);
	virtual std::string getButtonTag();
	virtual void setIndex(int index);
	virtual int getIndex();
	virtual void move(float x, float y);
private:
	

};

