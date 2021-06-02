// Made by: Robin Meyler, Josh Browne
// Date: Feburary - march 2019
// Time taken: ~ 40 hours


#include "Widget.h"

// Default definitions that do nothing unless defined within a subclass
// Not pure virtual because I want to makes pointer versions
Widget::Widget()
{
}

Widget::~Widget()
{
}

void Widget::update(sf::Time t_deltaTime)
{
}

void Widget::render(sf::RenderWindow & t_window)
{
}

void Widget::highlighted(sf::Time t_deltaTime)
{
}

void Widget::notHightlighted()
{
}

void Widget::setActionString(std::string t_actionString)
{
}

void Widget::setAnimationStyle(buttonAnimationStyle t_anime)
{
}

std::string * Widget::action()
{
	return nullptr;
}

void Widget::setButtonAsFaded()
{
}

void Widget::setButtonAsNormal()
{
}

void Widget::setAsStarter()
{
}

std::string Widget::getText()
{
	return std::string();
}

bool Widget::getFocusStatus()
{
	return false;		// False if not defined
}

GUItype Widget::getWidgetType()
{
	return GUItype();		// Basic if not defined
}

bool Widget::getIfFilled()
{
	return false;	// False if not defined
}

Widget * Widget::getUp()
{
	return nullptr;		// Nullptr if not defined
}

Widget * Widget::getDown()
{
	return nullptr;	// Nullptr if not defined
}

Widget * Widget::getRight()
{
	return nullptr;	// Nullptr if not defined
}

Widget * Widget::getLeft()
{
	return nullptr;	// Nullptr if not defined
}

void Widget::setPosition(sf::Vector2f t_pos)
{
}

void Widget::setRotation(float t_rotation)
{
}

float Widget::getRotation()
{
	return 0.0f;
}

sf::Vector2f Widget::getPosition()
{
	return sf::Vector2f(0,0); // 0,0 for error check
}

float Widget::getPositionY()
{
	return 0.0f;
}

std::string Widget::getActionString()
{
	return std::string();
}

void Widget::increaseRotation()
{
}

void Widget::decreaseRotation()
{
}

bool Widget::checkCollision(sf::Vector3f t_position)
{
	return false;
}

std::string Widget::getButtonTag()
{
	return std::string();
}

void Widget::setIndex(int index)
{
}

int Widget::getIndex()
{
	return 0;
}

void Widget::move(float x, float y)
{
}
