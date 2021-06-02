#pragma once
// Made by: Robin Meyler, Josh Browne
// Date: Feburary - march 2019
// Time taken: ~ 40 hours


#include "Widget.h"
#include "Button.h"

class CharacterInput : public Widget
{
public:
	// Structors --------------------------------------------------
	CharacterInput(float t_size, sf::Font & t_font);
	~CharacterInput();

	// Virtual overrides -------------------------------------------
	void update(sf::Time t_deltaTime) override;
	void render(sf::RenderWindow & t_window) override;
	void highlighted(sf::Time t_deltaTime) override;
	void notHightlighted() override;

	Widget * getUp() override;
	Widget * getDown() override;
	Widget * getRight() override;
	Widget * getLeft() override;
	GUItype getWidgetType() override;

	// Setters -----------------------------------------------------
	void setPosition(sf::Vector2f t_pos);
	void setUp(Widget * t_upWidget);
	void setDown(Widget * t_downWidget);
	void setDirectionWidgets();
	std::string getButtonTag() override;
	bool checkCollision(sf::Vector3f t_position) override;

	// Gets the part of the Character input that is currently in focus
	Widget * getCurrentTableFocus();

private:
	// Widget stuff ----------------------------------------------
	Button m_boardText[26];  // Board for input
	std::vector<char *> m_inputName;
	Widget *m_currentWidget;
	Widget * m_upOption;
	Widget * m_downOption;

	float m_size;
	std::string m_currentTagSelected;
	GUItype m_widgetType = GUItype::CharacterSelect;
};

