#pragma once

// Made by: Robin Meyler, Josh Browne
// Date: Feburary - march 2019
// Time taken: ~ 40 hours



#include "Widget.h"

class Label : public Widget
{
public:
	// Structors ------------------------------------------------
	Label();
	Label(sf::Font & t_font);
	Label(sf::String t_message);
	Label(sf::String t_message, sf::Font & t_font);
	~Label();

	// Virtual overrides ----------------------------------------
	void update(sf::Time t_deltaTime) override;
	void render(sf::RenderWindow & t_window) override;
	void setPosition(sf::Vector2f t_pos) override;
	float getPositionY() override;
	Widget * getUp() override;
	Widget * getDown() override;
	Widget * getRight() override;
	Widget * getLeft() override;

	// Setters -----------------------------------------------------
	void setTextColor(sf::Color t_color);
	void setTextSize(float t_size);
	void setString(sf::String t_message);
	void setFont(sf::Font & t_font);
	void setOrigin();					// This centers the Label
	void setOrigin(sf::Vector2f t_origin);		// This sets it to a choice
	void setUnderLined();
	void setUnderItalic();
	void setOutline(sf::Color t_color, float t_thickness);
	void setUp(Widget * t_upWidget);
	void setDown(Widget * t_downWidget);
	void setRight(Widget * t_rightWidget);
	void setLeft(Widget * t_leftWidget);
	void setRotation(float t_rotation);
	// Getters -------------------------------------------------------
	std::string getString() const;  // Used for sorting
	float getTextSize();
	sf::Vector2f getSize();

private:
	sf::Text m_labelText;
	sf::Font m_font;

	Widget *m_up{ nullptr };
	Widget *m_Down{ nullptr };
	Widget *m_right{ nullptr };
	Widget *m_left{ nullptr };

	bool isInFocus{ false };
};

