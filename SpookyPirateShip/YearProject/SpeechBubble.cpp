#include "SpeechBubble.h"

SpeechBubble::SpeechBubble(sf::Vector2f t_position, std::string t_message) : m_messageString(t_message)
{
	// move position to more ideal location
	t_position.x += 60;
	t_position.y -= 60;
	 //load font
	m_font.loadFromFile("digital-7.ttf");

	m_stringLength = m_messageString.length();

	int index = 0;
	while (m_stringLength > 0)
	{
		int count = 0;
		if (m_messageString.size() > lineLength)
		{
			std::string::reverse_iterator endIter = std::make_reverse_iterator(m_messageString.begin() + lineLength);
			while ((*endIter) != ' ')
			{
				endIter++;
				count++;
			}
			std::string::iterator iter = endIter.base();

			m_tempString.append(m_messageString.begin(), iter);
			m_messageString.erase(m_messageString.begin(), iter);
		}
		else
		{
			m_tempString.append(m_messageString.begin(), m_messageString.end());
			m_messageString.erase(m_messageString.begin(), m_messageString.end());
		}
		m_tempText.setString(m_tempString);
		m_tempText.setFont(m_font);
		m_tempText.setFillColor(sf::Color::Black);
		m_tempText.setCharacterSize(20);
		//m_tempText.setPosition(t_position.x + 5, t_position.y + ((m_tempText.getLocalBounds().height) * index));

		m_lines.push_back(m_tempText);

		m_stringLength -= (lineLength - count);
		m_tempString = ""; //reset
		index++;
	}

	if (m_lines.size() > 0)
	{
		//set triangle
		m_triangle.setPointCount(3);
		m_triangle.setFillColor(sf::Color::White);
		m_triangle.setPoint(0, sf::Vector2f(t_position.x + 20, t_position.y + 40)); //+ m_box.getLocalBounds().height));
		m_triangle.setPoint(1, sf::Vector2f(t_position.x + 60, t_position.y + 40)); //+ m_box.getLocalBounds().height));
		m_triangle.setPoint(2, sf::Vector2f(t_position.x, t_position.y + 80)); //+ m_box.getLocalBounds().height + 40));

		// find longest line (needed for setting box dimensions)
		float longest = 0;
		int count = 0;
		for (auto l : m_lines)
		{
			if (longest < l.getLocalBounds().width)
			{
				longest = l.getLocalBounds().width;
				index = count;
			}
			count++;
		}
		// set rectangle box
		m_box.setSize(sf::Vector2f(m_lines.at(index).getLocalBounds().width + 20, (m_lines.at(index).getLocalBounds().height * m_lines.size()) + 20));
		m_box.setFillColor(sf::Color::White);
		m_box.setPosition(m_triangle.getPoint(0).x - 20, m_triangle.getPoint(0).y - m_box.getLocalBounds().height);

		for (int i = 0; i < m_lines.size(); i++)
		{
			m_lines.at(i).setPosition(m_box.getPosition().x + 5, m_box.getPosition().y + (5 + m_lines.at(0).getLocalBounds().height * i));
		}
	}

	//set message
	/*m_messageText.setString(m_messageString);
	m_messageText.setFont(m_font);
	m_messageText.setFillColor(sf::Color::Black);
	m_messageText.setCharacterSize(35);
	m_messageText.setPosition(t_position.x + 5, t_position.y + 5);*/
	
}

SpeechBubble::~SpeechBubble()
{
}

void SpeechBubble::render(sf::RenderWindow& t_rendWind)
{
	if (m_lines.size() > 0)
	{
		t_rendWind.draw(m_box);
		t_rendWind.draw(m_triangle);
		for (int i = 0; i < m_lines.size(); i++)
		{
			t_rendWind.draw(m_lines.at(i));
		}
	}
}

void SpeechBubble::update(sf::Vector2f t_position)
{
	m_stringLength = m_messageString.length();

	if (m_lines.size() > 0)
	{
		// move position to more ideal location
		t_position.x += 60;
		t_position.y -= 60;

		//set triangle
		m_triangle.setPointCount(3);
		m_triangle.setFillColor(sf::Color::White);
		m_triangle.setPoint(0, sf::Vector2f(t_position.x + 20, t_position.y + 40)); //+ m_box.getLocalBounds().height));
		m_triangle.setPoint(1, sf::Vector2f(t_position.x + 60, t_position.y + 40)); //+ m_box.getLocalBounds().height));
		m_triangle.setPoint(2, sf::Vector2f(t_position.x, t_position.y + 80)); //+ m_box.getLocalBounds().height + 40));


		// find longest line (needed for setting box dimensions)
		float longest = 0;
		int count = 0;
		for (auto l : m_lines)
		{
			if (longest < l.getLocalBounds().width)
			{
				longest = l.getLocalBounds().width;
				index = count;
			}
			count++;
		}
		// set rectangle box
		m_box.setSize(sf::Vector2f(m_lines.at(index).getLocalBounds().width + 20, (m_lines.at(index).getLocalBounds().height * m_lines.size()) + 30));
		m_box.setFillColor(sf::Color::White);
		m_box.setPosition(m_triangle.getPoint(0).x - 20, m_triangle.getPoint(0).y - m_box.getLocalBounds().height);

		for (int i = 0; i < m_lines.size(); i++)
		{
			m_lines.at(i).setPosition(m_box.getPosition().x + 5, m_box.getPosition().y + (5 + m_lines.at(0).getLocalBounds().height * i));
		}
	}
}

void SpeechBubble::changeMessage(std::string t_message, sf::Vector2f t_position)
{
	// move position to more ideal location
	t_position.x += 60;
	t_position.y -= 60;

	m_messageString = t_message;
	m_stringLength = m_messageString.length();
	m_lines.clear();

	int index = 0;
	while (m_stringLength > 0)
	{
		int count = 0;
		if (m_messageString.size() > lineLength)
		{
			std::string::reverse_iterator endIter = std::make_reverse_iterator(m_messageString.begin() + lineLength);
			while ((*endIter) != ' ')
			{
				endIter++;
				count++;
			}
			std::string::iterator iter = endIter.base();

			m_tempString.append(m_messageString.begin(), iter);
			m_messageString.erase(m_messageString.begin(), iter);
		}
		else
		{
			m_tempString.append(m_messageString.begin(), m_messageString.end());
			m_messageString.erase(m_messageString.begin(), m_messageString.end());
		}
		m_tempText.setString(m_tempString);
		m_tempText.setFont(m_font);
		m_tempText.setFillColor(sf::Color::Black);
		m_tempText.setCharacterSize(20);
		//m_tempText.setPosition(t_position.x + 5, t_position.y + ((m_tempText.getLocalBounds().height) * index));

		m_lines.push_back(m_tempText);

		m_stringLength -= (lineLength - count);
		m_tempString = ""; //reset
		index++;
	}

	if (m_lines.size() > 0)
	{
		//set triangle
		m_triangle.setPointCount(3);
		m_triangle.setFillColor(sf::Color::White);
		m_triangle.setPoint(0, sf::Vector2f(t_position.x + 20, t_position.y + 40)); //+ m_box.getLocalBounds().height));
		m_triangle.setPoint(1, sf::Vector2f(t_position.x + 60, t_position.y + 40)); //+ m_box.getLocalBounds().height));
		m_triangle.setPoint(2, sf::Vector2f(t_position.x, t_position.y + 80)); //+ m_box.getLocalBounds().height + 40));

		// find longest line (needed for setting box dimensions)
		float longest = 0;
		int count = 0;
		for (auto l : m_lines)
		{
			if (longest < l.getLocalBounds().width)
			{
				longest = l.getLocalBounds().width;
				index = count;
			}
			count++;
		}
		// set rectangle box
		m_box.setSize(sf::Vector2f(m_lines.at(index).getLocalBounds().width + 20, (m_lines.at(index).getLocalBounds().height * m_lines.size()) + 20));
		m_box.setFillColor(sf::Color::White);
		m_box.setPosition(m_triangle.getPoint(0).x - 20, m_triangle.getPoint(0).y - m_box.getLocalBounds().height);

		for (int i = 0; i < m_lines.size(); i++)
		{
			m_lines.at(i).setPosition(m_box.getPosition().x + 5, m_box.getPosition().y + (5 + m_lines.at(0).getLocalBounds().height * i));
		}
	}
}
