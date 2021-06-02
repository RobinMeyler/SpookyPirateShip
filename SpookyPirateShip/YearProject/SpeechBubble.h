#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"

class SpeechBubble
{
public:
	SpeechBubble(sf::Vector2f t_position, std::string t_message);
	~SpeechBubble();

	void render(sf::RenderWindow& t_rendWind);
	void update(sf::Vector2f t_position);
	void changeMessage(std::string t_message, sf::Vector2f t_position);

private:
	std::string m_messageString;
	sf::Text m_messageText;
	std::vector<sf::Text> m_lines;
	sf::Text m_tempText;
	std::string m_tempString;
	int lineLength{20};
	int index = -1;

	sf::Font m_font;
	sf::RectangleShape m_box;
	sf::ConvexShape m_triangle;  // triangle connect for bottom of speechbox
	int m_stringLength;

};