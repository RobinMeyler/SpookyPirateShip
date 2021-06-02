// Made by: Robin Meyler, Josh Browne
// Date: Feburary - march 2019
// Time taken: ~ 40 hours


#include "CheckBox.h"

#include <iostream>

// Sets box details
CheckBox::CheckBox(float t_size, bool * t_staticBool)
{
	m_staticActionBool = t_staticBool;
	m_isFilled = *m_staticActionBool;
	m_checkBox.setSize(sf::Vector2f{ t_size, t_size });
	m_tickBox.setSize(sf::Vector2f{ t_size* 0.6f, t_size *0.6f });
	m_checkBox.setOrigin(t_size /2, t_size /2);
	m_checkBox.setOutlineThickness(3);
	m_focusColor = sf::Color::Red;					 // default
	m_checkBox.setOutlineColor(sf::Color::White);
	m_checkBox.setFillColor(sf::Color::White);
	m_tickBox.setFillColor(sf::Color::Black);
	m_tickBox.setOrigin(t_size* 0.6 / 2, t_size* 0.6 / 2);
}

CheckBox::~CheckBox()
{
}

// Dynamic set position function that takes 0 -> 1.0, 0% -> 100% or exact values
// Also takes a Enum to tell the fucntion which to use
void CheckBox::setPosition(float t_width, float t_height, PositionSetState t_settingStyle)
{
	switch (t_settingStyle)
	{
	case PositionSetState::DECIMAL:
		// Example fo clamping 0 -> 1
		t_width = std::min(std::max(t_width, 0.0f), 1.0f);
		t_height = std::min(std::max(t_height, 0.0f), 1.0f);

		m_checkBox.setPosition(t_width * SCREEN_WIDTH, t_height * SCREEN_HEIGHT);
		m_tickBox.setPosition(t_width * SCREEN_WIDTH, t_height * SCREEN_HEIGHT);
		break;
	case PositionSetState::PERCENTAGE:
		// Example fo clamping 0 -> 100
		t_width = std::min(std::max(t_width, 0.0f), 100.0f);
		t_height = std::min(std::max(t_height, 0.0f), 100.0f);

		t_width /= 100; // Make a decimal
		t_height /= 100;
		m_checkBox.setPosition(t_width * SCREEN_WIDTH, t_height * SCREEN_HEIGHT);
		m_tickBox.setPosition(t_width * SCREEN_WIDTH, t_height * SCREEN_HEIGHT);
		break;
	case PositionSetState::EXACT:
		m_checkBox.setPosition(t_width, t_height);
		m_tickBox.setPosition(t_width, t_height);
		break;
	default:
		break;
	}
}

void CheckBox::setPosition(sf::Vector2f t_pos)
{
	m_checkBox.setPosition(t_pos);
	m_tickBox.setPosition(t_pos);
}

// Sets the outline color for the checkbox when it is highlighted
void CheckBox::setFocusOutlineColor(sf::Color t_color)
{
	m_focusColor = t_color;
}

// Swaps the state and it's filled status
void CheckBox::swapState()
{
	if (m_isFilled == false)
	{
		m_isFilled = true;
		*m_staticActionBool = true;
	}
	else
	{
		m_isFilled = false;
		*m_staticActionBool = false;
	}
}

void CheckBox::update(sf::Time t_deltaTime)
{
}

void CheckBox::render(sf::RenderWindow & t_window)
{
	t_window.draw(m_checkBox);
	if (m_isFilled == true)
	{
		t_window.draw(m_tickBox);
	}
}

void CheckBox::highlighted(sf::Time t_deltaTime)
{
	isInFocus = true;
	m_checkBox.setOutlineColor(m_focusColor);
}

void CheckBox::notHightlighted()
{
	m_checkBox.setOutlineColor(sf::Color::White);
}

// Action functions
std::string * CheckBox::action()
{
	swapState();
	return &m_actionString;
}

void CheckBox::setActionString(std::string t_actionString)
{
	m_actionString = t_actionString;
}

std::string CheckBox::getActionString()
{
	return m_actionString;;
}

// Adding partners if you want certian checkboxes to know about one another
void CheckBox::addPartner(CheckBox * t_radioButton)
{
	m_otherRadiosInSet.push_back(t_radioButton);
}

void CheckBox::setUp(Widget * t_upWidget)
{
	m_up = t_upWidget;
}

void CheckBox::setDown(Widget * t_downWidget)
{
	m_Down = t_downWidget;
}

void CheckBox::setRight(Widget * t_rightWidget)
{
	m_right = t_rightWidget;
}

void CheckBox::setLeft(Widget * t_leftWidget)
{
	m_Left = t_leftWidget;
}

void CheckBox::setFilledTrue()
{
	m_isFilled = true;
}

Widget * CheckBox::getUp()
{
	isInFocus = false;
	return m_up;
}

Widget * CheckBox::getDown()
{
	isInFocus = false;
	return m_Down;
}

Widget * CheckBox::getRight()
{
	isInFocus = false;
	return m_right;
}

Widget * CheckBox::getLeft()
{
	isInFocus = false;
	return m_Left;
}

float CheckBox::getPositionY()
{
	return m_checkBox.getPosition().y;
}
