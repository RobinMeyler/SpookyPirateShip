// Made by: Robin Meyler, Josh Browne
// Date: Feburary - march 2019
// Time taken: ~ 40 hours


#include "HorizontalSlider.h"


HorizontalSlider::HorizontalSlider(float t_width, float t_height, int * t_static)
{
	m_staticPointer = t_static;
	m_currentValue = *t_static;			// Set the slider to starting value
	m_moveIncrement = t_width / 100;		// 1 -> 100
	// Main Vertical bar
	float horizontalHeight = t_height * 0.2;
	m_horizonTalBar.setSize(sf::Vector2f{ t_width, horizontalHeight });
	m_horizonTalBar.setOrigin(t_width / 2, horizontalHeight / 2);
	m_horizonTalBar.setFillColor(sf::Color::Red);
	// Horizontal bars
	float verticalWidth = t_width * 0.1;
	m_verticalBar.setSize(sf::Vector2f{ verticalWidth , t_height });
	m_verticalBar.setOrigin(verticalWidth / 2, t_height / 2);
	m_verticalBar.setFillColor(sf::Color::Yellow);
	// 5 small vertical bars
	float barWidth = t_width * 0.01;				// Skinny bars for visaul effect
	float barHeight;
	for (int i = 0; i < 5; i++)			// 5 spaced across the barr
	{
		m_checkPointBars[i].setFillColor(sf::Color::Blue);
		if (i % 2 == 0)															// Evens
		{
			barHeight = t_height * 0.6;		// High but not as high
		}
		else																	// Odds
		{
			barHeight = t_height * 0.4;		// High but even more 'not as high'
		}
		m_checkPointBars[i].setSize(sf::Vector2f{ barWidth, barHeight });
		m_checkPointBars[i].setOrigin(barWidth / 2, barHeight / 2);
	}
	m_value.setString(std::to_string(m_currentValue));
	m_value.setPosition(m_verticalBar.getPosition() + sf::Vector2f{ 0, (m_verticalBar.getGlobalBounds().height / 2) + 20 });
	m_value.setOrigin();
}

HorizontalSlider::~HorizontalSlider()
{
}

// Sets the position of the Bar view Vector
void HorizontalSlider::setPosition(sf::Vector2f t_pos)
{
	m_horizonTalBar.setPosition(t_pos);
	m_verticalBar.setPosition(t_pos.x -(m_horizonTalBar.getGlobalBounds().width/2) + (m_moveIncrement*m_currentValue), t_pos.y );

	// Figuring the aprrotiate positions for the small bars  ------------
	float barWidthOffset = m_horizonTalBar.getGlobalBounds().width / 2.0f;
	float distanceBetween = m_horizonTalBar.getGlobalBounds().width / 4.0f;
	float start = (t_pos.x - barWidthOffset);
	for (int i = 0; i < 5; i++)
	{
		if (i < 4)
			m_checkPointBars[i].setPosition(start + (i*distanceBetween) + m_checkPointBars[i].getGlobalBounds().width / 2, t_pos.y);
		else
			m_checkPointBars[i].setPosition((start + (i*distanceBetween)) - m_checkPointBars[i].getGlobalBounds().width / 2, t_pos.y);  // To give an all enclusive look
	}
	m_value.setPosition(m_verticalBar.getPosition() + sf::Vector2f{ 0, (m_verticalBar.getGlobalBounds().height / 2) + 20 });		// Value below
}

void HorizontalSlider::update(sf::Time t_deltaTime)
{
	m_value.setString(std::to_string(m_currentValue));
}

void HorizontalSlider::render(sf::RenderWindow & t_window)
{
	for (int i = 0; i < 5; i++)
	{
		t_window.draw(m_checkPointBars[i]);
	}
	t_window.draw(m_horizonTalBar);

	t_window.draw(m_verticalBar);
	m_value.render(t_window);
}

void HorizontalSlider::highlighted(sf::Time t_deltaTime)
{
	m_verticalBar.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255, 255));
	m_value.setString(std::to_string(m_currentValue));
}

std::string * HorizontalSlider::action()
{
	return &m_actionString;
}

void HorizontalSlider::setActionString(std::string t_actionString)
{
	m_actionString = t_actionString;
}

void HorizontalSlider::setString(std::string t_message, float t_size)
{

}

float HorizontalSlider::getPositionY()
{
	return m_horizonTalBar.getPosition().y;
}

void HorizontalSlider::setUp(Widget * t_upWidget)
{
	m_up = t_upWidget;
}

void HorizontalSlider::setDown(Widget * t_downWidget)
{
	m_Down = t_downWidget;
}

void HorizontalSlider::setRight(Widget * t_rightWidget)
{
	m_right = t_rightWidget;
}

void HorizontalSlider::setLeft(Widget * t_leftWidget)
{
	m_Left = t_leftWidget;
}

void HorizontalSlider::setFont(sf::Font & t_font)
{
	m_font = t_font;
	m_value.setFont(m_font);
}

Widget * HorizontalSlider::getUp()
{
	return m_up;
}

Widget * HorizontalSlider::getDown()
{
	return m_Down;
}

// Moves the slider right and left when in focus and alters the static value
Widget * HorizontalSlider::getRight()
{
	if (m_currentValue < 100)
	{
		m_currentValue += 5;
		*m_staticPointer += 5;
		m_verticalBar.move(m_moveIncrement*5, 0);
	}
	return m_right;
}
// Moves the slider right and left when in focus and alters the static value
Widget * HorizontalSlider::getLeft()
{
	if (m_currentValue > 0)
	{
		m_currentValue -= 5;
		*m_staticPointer -= 5;
		m_verticalBar.move(-m_moveIncrement*5, 0);
	}
	return m_Left;
}