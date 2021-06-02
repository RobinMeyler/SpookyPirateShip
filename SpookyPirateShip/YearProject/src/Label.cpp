// Made by: Robin Meyler, Josh Browne
// Date: Feburary - march 2019
// Time taken: ~ 40 hours


#include "Label.h"

// Constructors set defaults based on what info it it passed
Label::Label()
{
	m_labelText.setString("");
	m_labelText.setFont(m_font);
	m_labelText.setCharacterSize(20);
	m_labelText.setFillColor(sf::Color::Red);
	m_labelText.setPosition(sf::Vector2f{ 0,0 });
}

Label::Label(sf::Font & t_font) :
	m_font(t_font)
{
	m_labelText.setString("");
	m_labelText.setFont(m_font);
	m_labelText.setCharacterSize(20); 
	m_labelText.setFillColor(sf::Color::Red);
	m_labelText.setPosition(sf::Vector2f{ 0,0 });
}

// Try not use this one because of font loading
Label::Label(sf::String t_message)
{
	m_font.loadFromFile("BBrick.ttf");
	m_labelText.setString(t_message);
	m_labelText.setFont(m_font);
	m_labelText.setCharacterSize(20); // Default
	m_labelText.setFillColor(sf::Color::Red);
	m_labelText.setPosition(sf::Vector2f{ 0,0 });
}

Label::Label(sf::String t_message, sf::Font & t_font) :
	m_font(t_font)
{
	m_labelText.setString(t_message);
	m_labelText.setFont(m_font);
	m_labelText.setCharacterSize(20); // Default
	m_labelText.setFillColor(sf::Color::Red);
	m_labelText.setPosition(sf::Vector2f{ 0,0 });
}

Label::~Label()
{
}

void Label::update(sf::Time t_deltaTime)
{
}

void Label::render(sf::RenderWindow & t_window)
{
	t_window.draw(m_labelText);
}

float Label::getPositionY()
{
	return m_labelText.getPosition().y;
}

std::string Label::getString() const
{
	std::string tempStr = m_labelText.getString();
	return m_labelText.getString();
}

void Label::setTextColor(sf::Color t_color)
{
	m_labelText.setFillColor(t_color);
}

void Label::setTextSize(float t_size)
{
	m_labelText.setCharacterSize(t_size);
}

float Label::getTextSize()
{
	return m_labelText.getCharacterSize();
}

void Label::setPosition(sf::Vector2f t_pos)
{
	m_labelText.setPosition(t_pos);
}

void Label::setString(sf::String  t_message)
{
	m_labelText.setString(t_message);
}

void Label::setFont(sf::Font & t_font)
{
	m_labelText.setFont(t_font);
	setOrigin();					// Centers the text
}

void Label::setOrigin()
{
	m_labelText.setOrigin(m_labelText.getGlobalBounds().width / 2, m_labelText.getGlobalBounds().height);
}

void Label::setOrigin(sf::Vector2f t_origin)
{
	m_labelText.setOrigin(t_origin);
}

void Label::setUnderLined()
{
	if (m_labelText.getStyle() == sf::Text::Italic)
	{
		m_labelText.setStyle(sf::Text::Underlined | sf::Text::Italic);		// If one is already set, set the other as well
	}
	else
	{
		m_labelText.setStyle(sf::Text::Underlined);
	}
}

void Label::setUnderItalic()
{
	if (m_labelText.getStyle() == sf::Text::Underlined)
	{
		m_labelText.setStyle(sf::Text::Underlined | sf::Text::Italic);     // If one is already set, set the other as well
	}
	else
	{
		m_labelText.setStyle(sf::Text::Italic);
	}
}

// Passed thickness and color to condense
void Label::setOutline(sf::Color t_color, float t_thickness)
{
	m_labelText.setOutlineThickness(t_thickness);
	m_labelText.setOutlineColor(t_color);
}

// Size in vector form of the entity
sf::Vector2f Label::getSize()
{
	return sf::Vector2f{ m_labelText.getGlobalBounds().width, m_labelText.getGlobalBounds().height };
}

Widget * Label::getUp()
{
	isInFocus = false;
	return m_up;
}

Widget * Label::getDown()
{
	isInFocus = false;
	return m_Down;
}

Widget * Label::getRight()
{
	isInFocus = false;
	return m_right;
}

Widget * Label::getLeft()
{
	isInFocus = false;
	return m_left;
}

void Label::setUp(Widget * t_upWidget)
{
	m_up = t_upWidget;
}

void Label::setDown(Widget * t_downWidget)
{
	m_Down = t_downWidget;
}

void Label::setRight(Widget * t_rightWidget)
{
	m_right = t_rightWidget;
}

void Label::setLeft(Widget * t_leftWidget)
{
	m_left = t_leftWidget;
}

void Label::setRotation(float t_rotation)
{
	m_labelText.setRotation(t_rotation);
}
