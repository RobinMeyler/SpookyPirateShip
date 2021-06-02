// Made by: Robin Meyler, Josh Browne
// Date: Feburary - march 2019
// Time taken: ~ 40 hours


#include "LeaderboardEntry.h"



LeaderboardEntry::LeaderboardEntry()
{
}

LeaderboardEntry::LeaderboardEntry(std::string t_name, int t_leaderboardEntry, float t_textSize)
{
	value = t_leaderboardEntry;
	sf::Color green = sf::Color::Green;
	m_entryScore.setTextSize(t_textSize);
	m_entryScore.setTextColor(green);
	m_entryScore.setString(std::to_string(value));
	m_entryName.setString(t_name);
	m_entryName.setTextSize(t_textSize);
	m_entryName.setTextColor(green);
}

LeaderboardEntry::~LeaderboardEntry()
{
}

void LeaderboardEntry::update(sf::Time t_deltaTime)
{
}

void LeaderboardEntry::render(sf::RenderWindow & t_window)
{
	m_entryName.render(t_window);
	m_entryScore.render(t_window);
}


// Gets the entry's Value (score)
int LeaderboardEntry::getValue() const
{
	return value;
}
// Gets the entry's String (Name)
std::string LeaderboardEntry::getString() const
{
	return m_entryName.getString();
}

// Space apart means the space to the right the score is in relation to the name, to form a leaderboard shape
void LeaderboardEntry::setPosition(sf::Vector2f t_pos, float t_spaceWideApart)
{
	m_entryName.setPosition(t_pos);
	m_entryScore.setPosition(t_pos + sf::Vector2f{ t_spaceWideApart, 0 });
}

float LeaderboardEntry::getPositionY()
{
	return m_entryScore.getPositionY();
}

Widget * LeaderboardEntry::getUp()
{
	return m_up;
}

Widget * LeaderboardEntry::getDown()
{
	return m_Down;
}

void LeaderboardEntry::setFont(sf::Font & t_font)
{
	m_entryName.setFont(t_font);
	m_entryName.setOrigin(sf::Vector2f{ 0,0 });
	m_entryScore.setFont(t_font);
	m_entryScore.setOrigin(sf::Vector2f{ 0,0 });
}

void LeaderboardEntry::setUp(Widget * t_upWidget)
{
	m_up = t_upWidget;
}

void LeaderboardEntry::setDown(Widget * t_downWidget)
{
	m_Down = t_downWidget;
}

// Setting the colors
void LeaderboardEntry::setNameColor(sf::Color t_color)
{
	m_entryName.setTextColor(t_color);
}

void LeaderboardEntry::setValueColor(sf::Color t_color)
{
	m_entryScore.setTextColor(t_color);
}
