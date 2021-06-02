#pragma once

// Made by: Robin Meyler, Josh Browne
// Date: Feburary - march 2019
// Time taken: ~ 40 hours


#include "Widget.h"

class CheckBox : public Widget
{
public:
	// Structors ------------------------------------------------------
	CheckBox(float t_size, bool * t_staticBool);
	~CheckBox();

	// Virtual overrides ----------------------------------------------
	void setPosition(sf::Vector2f t_pos) override;
	void update(sf::Time t_deltaTime) override;
	void render(sf::RenderWindow & t_window) override;
	void highlighted(sf::Time t_deltaTime) override;
	void notHightlighted() override;

	// Action
	std::string *action() override;
	void setActionString(std::string t_actionString) override;
	std::string getActionString();

	float getPositionY() override;

	Widget * getUp() override;
	Widget * getDown() override;
	Widget * getRight() override;
	Widget * getLeft() override;

	// Setters ---------------------------------------------------------
	void setPosition(float t_width, float t_height, PositionSetState t_settingStyle);
	void setFocusOutlineColor(sf::Color t_color);
	void setFilledTrue();

	void setUp(Widget * t_upWidget);
	void setDown(Widget * t_downWidget);
	void setRight(Widget * t_rightWidget);
	void setLeft(Widget * t_leftWidget);

	// Swaping ------------------------------
	void swapState();
	void addPartner(CheckBox* t_checkBox);


private:
	// Widget stuff --------------
	std::vector<CheckBox*> m_otherRadiosInSet;
	Widget * m_up{ nullptr };
	Widget *m_Down{ nullptr };
	Widget *m_right{ nullptr };
	Widget *m_Left{ nullptr };

	// SFML ----------------------
	sf::RectangleShape m_checkBox;
	sf::RectangleShape m_tickBox;
	sf::Color m_focusColor;

	std::string m_actionString = "";

	bool m_isFilled{ false };
	bool isInFocus{ false };
	// static controling pointer
	bool *m_staticActionBool;
};

