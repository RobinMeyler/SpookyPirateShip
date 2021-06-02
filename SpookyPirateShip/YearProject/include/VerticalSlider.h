#pragma once

// Made by: Robin Meyler, Josh Browne
// Date: Feburary - march 2019
// Time taken: ~ 40 hours


#include "Widget.h"

class VerticalSlider : public Widget
{
public:
	// Structors -----------------------------------------------
	VerticalSlider(float t_maxScreenLength, float t_width);
	~VerticalSlider();

	// Virtual overrides ---------------------------------------
	void update(sf::Time t_deltaTime) override;
	void render(sf::RenderWindow & t_window) override;
	void highlighted(sf::Time t_deltaTime) override;

	void moveView(float t_move, sf::Vector2f t_viewPos);

private:
	sf::RectangleShape m_sliderOutline;
	sf::RectangleShape m_sliderBar;
	float m_proportionValue;
	float m_maxScreen;
	float m_currentPercent{ 0 };
};

