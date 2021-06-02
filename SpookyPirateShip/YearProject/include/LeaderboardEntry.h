#pragma once

// Made by: Robin Meyler, Josh Browne
// Date: Feburary - march 2019
// Time taken: ~ 40 hours



#include "Widget.h"
#include "Label.h"

class LeaderboardEntry : public Widget
{
public:
	// Structors ---------------------------------------------------
	LeaderboardEntry();
	LeaderboardEntry(std::string t_name, int t_leaderboardEntry, float t_textSize);
	~LeaderboardEntry();

	// Virtual overrides
	void update(sf::Time t_deltaTime) override;
	void render(sf::RenderWindow & t_window) override;

	float getPositionY() override;
	Widget * getUp() override;
	Widget * getDown() override;

	// Setters -----------------------------------------------------
	void setPosition(sf::Vector2f t_pos, float t_spaceWideApart);
	void setFont(sf::Font & t_font);
	void setUp(Widget * t_upWidget);
	void setDown(Widget * t_downWidget);
	void setNameColor(sf::Color t_color);
	void setValueColor(sf::Color t_color);

	// Getters -------------------------------------------------------
	int getValue() const;
	std::string getString() const;


private:
	Label m_entryName;
	Label m_entryScore;

	Widget *m_up{ nullptr };
	Widget *m_Down{ nullptr };

	int value{ 0 };
};

