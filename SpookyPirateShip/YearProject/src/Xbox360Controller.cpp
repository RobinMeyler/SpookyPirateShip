// Name: Robin Meyler


#include "Xbox360Controller.h"
#include <iostream>
Xbox360Controller::Xbox360Controller()
{
}

Xbox360Controller::~Xbox360Controller()
{
}

void Xbox360Controller::update()
{
	checkButtonPressed();
	checkAxisPositions();
}

bool Xbox360Controller::isConnected()
{
	return false;
}

bool Xbox360Controller::connect()
{
	return false;
}

void Xbox360Controller::checkButtonPressed()
{
	doCheck(&m_currentState.A, 0);								// A
	doCheck(&m_currentState.B, 1);								// B
	doCheck(&m_currentState.X, 2);								// X
	doCheck(&m_currentState.Y, 3);								// Y
	doCheck(&m_currentState.LB, 4);								// LB
	doCheck(&m_currentState.RB, 5);								// RB
	doCheck(&m_currentState.Back, 6);							// Back
	doCheck(&m_currentState.Start, 7);							// Start
	doCheck(&m_currentState.LeftThumbStickClick, 8);			// LeftThumbClick
	doCheck(&m_currentState.RightThumbStickClick, 9);			// RightThumbClick
}

void Xbox360Controller::checkAxisPositions()
{
	m_currentState.LeftThumbStick.x = m_Joystick.getAxisPosition(0, sf::Joystick::Axis::X);			// Left Stick X axis
	m_currentState.LeftThumbStick.y = m_Joystick.getAxisPosition(0, sf::Joystick::Axis::Y);			// Left Stick Y axis
	m_currentState.RightThumbStick.x = m_Joystick.getAxisPosition(0, sf::Joystick::Axis::U);		// Right Stick X axis
	m_currentState.RightThumbStick.y = m_Joystick.getAxisPosition(0, sf::Joystick::Axis::V);		// Right Sitck Y axis
	m_currentState.RTrigger = m_Joystick.getAxisPosition(0, sf::Joystick::Axis::Z);
	m_currentState.LTrigger = m_Joystick.getAxisPosition(0, sf::Joystick::Axis::Z);
	// Dpad directions
	if (m_Joystick.getAxisPosition(0, sf::Joystick::Axis::PovX) > dpadThreshold)			// DPAD Right
	{
		m_currentState.DpadRight = true;
	}
	else
	{
		m_currentState.DpadRight = false;
	}

	if (m_Joystick.getAxisPosition(0, sf::Joystick::Axis::PovX) < -dpadThreshold)			// DPAD Left
	{
		m_currentState.DpadLeft = true;
	}
	else
	{
		m_currentState.DpadLeft = false;
	}
	if (m_Joystick.getAxisPosition(0, sf::Joystick::Axis::PovY) < -dpadThreshold)			// DPAD Down
	{
		m_currentState.DpadDown = true;
	}
	else
	{
		m_currentState.DpadDown = false;
	}
	if (m_Joystick.getAxisPosition(0, sf::Joystick::Axis::PovY) > dpadThreshold)			// DPAD Up
	{
		m_currentState.DpadUp = true;
	}
	else
	{
		m_currentState.DpadUp = false;
	}
}

// Does the check for button pressed
// Takes in the pointer for the current state and the index number for that button
// Sets the button status to true or false based on what it returns
void Xbox360Controller::doCheck(bool * t_status, short t_button)
{
	if (m_Joystick.isButtonPressed(0, t_button))					// t_button is the index of controller
	{																// ie. 0 = A, 1 = B
		*t_status = true;											// Pointer used because it alters the bool
	}
	else																
	{
		*t_status = false;											// Set to false if not pressed
	}
}

