#pragma once

// Made by: Robin Meyler, Josh Browne
// Date: Feburary - march 2019
// Time taken: ~ 40 hours


#include "Widget.h"

class RadioButton : public Widget
{
public:
	// Structots -------------------------------------------
	RadioButton(float t_radius, bool * t_staticBool);
	~RadioButton();

	// Virtual Overrides ------------------------------------
	void setPosition(sf::Vector2f t_pos) override;

	void update(sf::Time t_deltaTime) override;
	void render(sf::RenderWindow & t_window) override;
	void highlighted(sf::Time t_deltaTime) override;
	
	std::string *action() override;
	void setActionString(std::string t_actionString) override;
	void notHightlighted() override;
	void setFocusOutlineColor(sf::Color t_color);

	Widget * getUp() override;
	Widget * getDown() override;
	Widget * getRight() override;
	Widget * getLeft() override;

	float getPositionY() override;
	
	// Setters ------------------------------------------------
	void setPosition(float t_width, float t_height, PositionSetState t_settingStyle);
	void setUp(Widget * t_upWidget);
	void setDown(Widget * t_downWidget);
	void setRight(Widget * t_rightWidget);
	void setLeft(Widget * t_leftWidget);
	void setAsStarter();				// Set as in focus at the start

	// Used to control the static bool and filled
	void swapState();
	void addPartner(RadioButton* t_radioButton);
	
private: 
	sf::CircleShape m_radioCircle;
	sf::CircleShape m_innerCirlce;
	float m_radius;
	sf::Color m_focusColor;
	bool m_isFilled{ false };
	std::string m_actionString = "";
	Widget *m_up{ nullptr };
	Widget *m_Down{ nullptr };
	Widget *m_right{ nullptr };
	Widget *m_Left{ nullptr };
	std::vector<RadioButton*> m_otherRadiosInSet;
	bool isInFocus{ false };
	bool *m_staticActionBool;
};

