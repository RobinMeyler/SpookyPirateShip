// Made by: Robin Meyler, Josh Browne
// Date: Feburary - march 2019
// Time taken: ~ 40 hours


#include "RadioButton.h"
#include <iostream>

// Defaults
RadioButton::RadioButton(float t_radius, bool * t_staticBool)
{
	m_staticActionBool = t_staticBool;		// Static bool passed in as pointer and controlled in Radio
	m_isFilled = *m_staticActionBool;
	m_radius = t_radius;
	m_radioCircle.setRadius(m_radius);
	m_radioCircle.setFillColor(sf::Color::White);
	m_radioCircle.setOrigin(t_radius, t_radius);
	m_radioCircle.setOutlineThickness(3);
	m_focusColor = sf::Color::Red;
	m_radioCircle.setOutlineColor(sf::Color::White);

	m_innerCirlce.setRadius(t_radius*0.6);
	m_innerCirlce.setFillColor(sf::Color::Black);
	m_innerCirlce.setOrigin(t_radius*0.6, t_radius*0.6);
}

RadioButton::~RadioButton()
{
}

// Dynamic set position function that takes 0 -> 1.0, 0% -> 100% or exact values
// Also takes a Enum to tell the fucntion which to use
void RadioButton::setPosition(float t_width, float t_height, PositionSetState t_settingStyle)
{
	switch (t_settingStyle)
	{
	case PositionSetState::DECIMAL:
		// Example fo clamping 0 -> 1
		t_width = std::min(std::max(t_width, 0.0f), 1.0f);
		t_height = std::min(std::max(t_height, 0.0f), 1.0f);

		m_radioCircle.setPosition(t_width * SCREEN_WIDTH, t_height * SCREEN_HEIGHT);
		m_innerCirlce.setPosition(t_width * SCREEN_WIDTH, t_height * SCREEN_HEIGHT);
		break;
	case PositionSetState::PERCENTAGE:
		// Example fo clamping 0 -> 100
		t_width = std::min(std::max(t_width, 0.0f), 100.0f);
		t_height = std::min(std::max(t_height, 0.0f), 100.0f);

		t_width /= 100; // Make a decimal
		t_height /= 100;
		m_radioCircle.setPosition(t_width * SCREEN_WIDTH, t_height * SCREEN_HEIGHT);
		m_innerCirlce.setPosition(t_width * SCREEN_WIDTH, t_height * SCREEN_HEIGHT);
		break;
	case PositionSetState::EXACT:
		m_radioCircle.setPosition(t_width, t_height);
		m_innerCirlce.setPosition(t_width, t_height);
		break;
	default:
		break;
	}
}

void RadioButton::setPosition(sf::Vector2f t_pos)
{
	m_innerCirlce.setPosition(t_pos);
	m_radioCircle.setPosition(t_pos);
}

// Swaps the button as filled and vice versa, changes the static bool and state of other bools in set
void RadioButton::swapState()
{
	if (isInFocus == true)
	{
		if (m_isFilled != true)
		{
			m_isFilled = true;
			*m_staticActionBool = true;
		}
		
		for (auto & buttons : m_otherRadiosInSet)
		{
			buttons->swapState();
		}
	}
	else
	{
		m_isFilled = false;
		*m_staticActionBool = false;
	}
}

void RadioButton::update(sf::Time t_deltaTime)
{
}

void RadioButton::render(sf::RenderWindow & t_window)
{
	t_window.draw(m_radioCircle);
	if (m_isFilled == true)
	{
		t_window.draw(m_innerCirlce);
	}
}

// Radio button is in focus
void RadioButton::highlighted(sf::Time t_deltaTime)
{
	isInFocus = true;
    m_radioCircle.setOutlineColor(m_focusColor);
}

// Radio button no longer in focus
void RadioButton::notHightlighted()
{
	m_radioCircle.setOutlineColor(sf::Color::White);
}

// Swaps the state of it and all the others it is partnered to
std::string * RadioButton::action()
{
	swapState();
	return &m_actionString;
}

void RadioButton::setActionString(std::string t_actionString)
{
	m_actionString = t_actionString;
}

void RadioButton::setFocusOutlineColor(sf::Color t_color)
{
	m_focusColor = t_color;
}

// Add another radio button to the set, so it will swap with this one when needed
void RadioButton::addPartner(RadioButton * t_radioButton)
{
	m_otherRadiosInSet.push_back(t_radioButton);
}

void RadioButton::setUp(Widget * t_upWidget)
{
	m_up = t_upWidget;
}

void RadioButton::setDown(Widget * t_downWidget)
{
	m_Down = t_downWidget;
}

void RadioButton::setRight(Widget * t_rightWidget)
{
	m_right = t_rightWidget;
}

void RadioButton::setLeft(Widget * t_leftWidget)
{
	m_Left = t_leftWidget;
}

Widget * RadioButton::getUp()
{
	isInFocus = false;
	return m_up;
}

Widget * RadioButton::getDown()
{
	isInFocus = false;
	return m_Down;
}

Widget * RadioButton::getRight()
{
	isInFocus = false;
	return m_right;
}

Widget * RadioButton::getLeft()
{
	isInFocus = false;
	return m_Left;
}

float RadioButton::getPositionY()
{
	return m_radioCircle.getPosition().y;
}

void RadioButton::setAsStarter()
{
	m_isFilled = true;
	*m_staticActionBool = true;
}
