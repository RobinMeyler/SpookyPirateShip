// Name: Robin Meyler

#pragma once
#ifndef XBOX360CONTROLLER 
#define XBOX360CONTROLLER

#include <SFML/Graphics.hpp> 

struct GamePadState {
	bool A;
	bool B;
	bool X;
	bool Y;
	bool LB;
	bool RB;
	bool LeftThumbStickClick;
	bool RightThumbStickClick;
	bool DpadUp;
	bool DpadDown;
	bool DpadLeft;
	bool DpadRight;
	bool Start;
	bool Back;
	bool Xbox;
	float RTrigger;
	float LTrigger;
	sf::Vector2f RightThumbStick;
	sf::Vector2f LeftThumbStick;
};

class Xbox360Controller
{
private:
	const int dpadThreshold = 50;
	sf::Joystick m_Joystick;
	sf::String m_previous;
public:
	static int s_noOfControllers;
	int sf_Joystick_index;
	GamePadState m_previousState;
	GamePadState m_currentState;
	Xbox360Controller();
	~Xbox360Controller();
	void update();
	bool isConnected();
	bool connect();
	void checkButtonPressed();
	void checkAxisPositions();
	void doCheck(bool *t_status, short t_button);
};

#endif