// Made by: Robin Meyler, Josh Browne
// Date: Feburary - march 2019
// Time taken: ~ 40 hours


#include "VerticalSlider.h"



VerticalSlider::VerticalSlider(float t_maxScreenLength, float t_width)
{
	m_maxScreen = t_maxScreenLength;

	float diffPort = SCREEN_HEIGHT*(SCREEN_HEIGHT/t_maxScreenLength);			// Difference proportion of screen over the max so it's under 1 (800* 800/1400)
	float sliderBarDifference = 0.25f * t_width;										// 1/4 of the size of the outline = 1/8 on either side (which looks nice)
	m_proportionValue = SCREEN_HEIGHT / t_maxScreenLength;				// 800/1400 is 0.something							

	m_sliderBar.setSize(sf::Vector2f{ t_width - sliderBarDifference, diffPort });		// Gives the approaite sized slider that will move downt he screen in relation to how the view moves
	m_sliderOutline.setSize(sf::Vector2f{ t_width, (float)SCREEN_HEIGHT });

	m_sliderBar.setFillColor(sf::Color::Red);
	m_sliderBar.setPosition(SCREEN_WIDTH - (t_width - (sliderBarDifference/2)), 0);				// difference/2 because its needs to be centred in the outline

	m_sliderOutline.setFillColor(sf::Color::White);
	m_sliderOutline.setPosition(SCREEN_WIDTH - t_width, 0);
}

VerticalSlider::~VerticalSlider()
{
}

void VerticalSlider::update(sf::Time t_deltaTime)
{
}

void VerticalSlider::render(sf::RenderWindow & t_window)
{
	t_window.draw(m_sliderOutline);
	t_window.draw(m_sliderBar);
}

// Moving the slider and adjusting the postion of the slider so it stays fixed on thye screen whe the view moves
void VerticalSlider::moveView(float t_move, sf::Vector2f t_viewPos)
{
	float percent = SCREEN_HEIGHT / 100;		// Screen height in terms of % 1, 100
	float screenMove = t_move /m_maxScreen;   // How much to move, 10/1400 = 1/140

	m_currentPercent += (100* screenMove);	// 1/40 * 100 = 100/40, 2.5%

	
	m_sliderBar.setPosition(m_sliderBar.getPosition().x, t_viewPos.y - (SCREEN_HEIGHT / 2) + (m_currentPercent * percent));	// Make sure the sliders move with the view
	m_sliderOutline.setPosition(m_sliderOutline.getPosition().x, t_viewPos.y - (SCREEN_HEIGHT / 2));	// Make sure the sliders move with the view
	m_sliderBar.move(0, t_move*m_proportionValue);		// Add on the move amount by the ratio e.g (10* 800/1400)
}

void VerticalSlider::highlighted(sf::Time t_deltaTime)
{
}
