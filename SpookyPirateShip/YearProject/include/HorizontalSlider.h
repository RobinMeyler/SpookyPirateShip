#pragma once

// Made by: Robin Meyler, Josh Browne
// Date: Feburary - march 2019
// Time taken: ~ 40 hours



#include "Widget.h"
#include "Label.h"

class HorizontalSlider : public Widget
{
public:

	// Structors -----------------------------------
	HorizontalSlider(float t_width, float t_height, int * t_static);
	~HorizontalSlider();

	// Virtual overrides -------------------------------
	void setPosition(sf::Vector2f t_pos) override;

	void update(sf::Time t_deltaTime) override;
	void render(sf::RenderWindow & t_window) override;
	void highlighted(sf::Time t_deltaTime) override;
	Widget * getUp() override;
	Widget * getDown() override;
	Widget * getRight() override;
	Widget * getLeft() override;

	std::string *action() override;
	void setActionString(std::string t_actionString) override;

	float getPositionY() override;

	// Setters -------------------------------------
	void setString(std::string  t_message, float t_size);
	void setUp(Widget * t_upWidget);
	void setDown(Widget * t_downWidget);
	void setRight(Widget * t_rightWidget);
	void setLeft(Widget * t_leftWidget);
	void setFont(sf::Font & t_font);

private:
	Label m_value;
	int m_currentValue;
	float m_moveIncrement;
	int * m_staticPointer;

	sf::RectangleShape m_horizonTalBar;
	sf::RectangleShape m_verticalBar;
	sf::RectangleShape m_checkPointBars[5];
	sf::Font m_font;
	std::string m_actionString = "";
	Widget *m_up{ nullptr };
	Widget *m_Down{ nullptr };
	Widget *m_right{ nullptr };
	Widget *m_Left{ nullptr };
	float barWidthOffset;
	float distanceBetween;
	float start;
};

