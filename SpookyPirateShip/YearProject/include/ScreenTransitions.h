#pragma once
#include "GUIGlobals.h"
#include "SFML/Graphics.hpp"
// Globals attached to ScreenTransitions
static float Screen_Opacity = 255;
static float TRANSITION_SPEED = 3;
static bool fadeIn = true;
static bool transitioning = true;
static sf::Sprite screenCurtain;

class ScreenTransitions
{
public:
	ScreenTransitions();
	~ScreenTransitions();

	static void Fade();
	static void setFadeType(bool t_bool);

	static void setCurtain(sf::Texture t_texture);
	static sf::Sprite getScreenCurtain();
	static void setPosition(sf::Vector2f t_pos);
	static void init();
	static bool isTransitioning();
	static void setFadeSpeed(float t_speed);
private:
};
