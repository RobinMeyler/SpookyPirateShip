#include "ScreenTransitions.h"

ScreenTransitions::ScreenTransitions()
{
}

ScreenTransitions::~ScreenTransitions()
{
}

void ScreenTransitions::Fade()
{
	if (transitioning)
	{
		if (fadeIn)
		{
			if (Screen_Opacity > 5)
			{

			Screen_Opacity -= TRANSITION_SPEED;

			}
			else
			{
				Screen_Opacity = 0;
				transitioning = false;
			}
		}
		else
		{
			if (Screen_Opacity < 250)
			{

				Screen_Opacity += TRANSITION_SPEED;

			}
			else
			{
				Screen_Opacity = 255;
				transitioning = false;
			}
		}
	}
	screenCurtain.setColor(sf::Color(0,0,0,Screen_Opacity));
}

void ScreenTransitions::setFadeType(bool t_bool)
{
	fadeIn = t_bool;

	transitioning = true;
}

void ScreenTransitions::setCurtain(sf::Texture t_texture)
{
	screenCurtain.setTexture(t_texture);
}

sf::Sprite ScreenTransitions::getScreenCurtain()
{
	return screenCurtain;
}

void ScreenTransitions::setPosition(sf::Vector2f t_pos)
{
	screenCurtain.setPosition(t_pos);
}

void ScreenTransitions::init()
{
	screenCurtain.setColor(sf::Color(255, 255, 255, Screen_Opacity));
	screenCurtain.setPosition(sf::Vector2f(0,0));
}

bool ScreenTransitions::isTransitioning()
{
	return transitioning;
}

void ScreenTransitions::setFadeSpeed(float t_speed)
{
	TRANSITION_SPEED = t_speed;
}
