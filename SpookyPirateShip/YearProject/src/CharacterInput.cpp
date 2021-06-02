// Made by: Robin Meyler, Josh Browne
// Date: Feburary - march 2019
// Time taken: ~ 40 hours


#include "CharacterInput.h"

// Constructor
CharacterInput::CharacterInput(float t_size, sf::Font & t_font)
{
	m_size = t_size;				// Keep track of the size;

	// Set each string to it's letter -----------------------------------------
	sf::Color blue = sf::Color::Blue;
	std::string tempString = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; // Each letter
	for (int i = 0; i < 26; i++)
	{
		Button *b = new Button(blue, t_size, t_size);
		std::string st(1, tempString[i]);				// Char to std::contructor
		b->setString(st, t_size*0.8);
		b->setActionString(st);
		b->setButtonTag(st);
		b->setIndex(0);
		b->setFont(t_font);
		m_boardText[i] = *b;
	}
	m_currentWidget = &m_boardText[0];  // First 1 in focus
	m_boardText[0].setAsStarter();

	// Sets the up, down and so on of each entry
	this->setDirectionWidgets();
}

CharacterInput::~CharacterInput()
{
	delete[] m_boardText;
}

// Sets the postion of all of the buttons 
void CharacterInput::setPosition(sf::Vector2f t_pos)
{
	float xOffset{ 0.0f };
	float yOffset{ 0.0f };
	int rowCount{ 0 };

	// X and Y offsets increase along X till 10 then reset and drop down 1 on the Y ------------
	for (int i = 0; i < 26; i++)
	{
		sf::Vector2f tempVec = {t_pos.x + xOffset, t_pos.y + yOffset };		
		m_boardText[i].setPosition(tempVec);
		rowCount++;
		xOffset += m_size;
		if (rowCount == 10)		// 10 because table is rows of 10 (and 6 to spare)
		{
			xOffset = 0;
			yOffset += m_size;
			rowCount = 0;
		}
	}
}

void CharacterInput::update(sf::Time t_deltaTime)
{
	for (int i = 0; i < 26; i++)
	{
		m_boardText[i].update(t_deltaTime);
	}
}

void CharacterInput::render(sf::RenderWindow & t_window)
{
	for (int i = 0; i < 26; i++)
	{
		m_boardText[i].render(t_window);
	}
}

void CharacterInput::highlighted(sf::Time t_deltaTime)
{
	m_currentWidget->highlighted(t_deltaTime);
}

void CharacterInput::notHightlighted()
{
	for (int i = 0; i < 26; i++)
	{
		m_boardText[i].notHightlighted();
	}
}

 // Get the part of the table that is in focus
Widget * CharacterInput::getCurrentTableFocus()
{
	return m_currentWidget;
}

Widget * CharacterInput::getUp()
{
	Widget * checkWidget = m_currentWidget->getUp();
	if (checkWidget != nullptr)
	{
		m_currentWidget = checkWidget;
	}
	return m_currentWidget;
}

Widget * CharacterInput::getDown()
{
	Widget * checkWidget = m_currentWidget->getDown();
	if (checkWidget != nullptr)
	{
		m_currentWidget = checkWidget;
	}
	return m_currentWidget;
}

Widget * CharacterInput::getRight()
{
	Widget * checkWidget = m_currentWidget->getRight();
	if (checkWidget != nullptr)
	{
		m_currentWidget = checkWidget;
	}
	return m_currentWidget;
}

Widget * CharacterInput::getLeft()
{
	Widget * checkWidget = m_currentWidget->getLeft();
	if (checkWidget != nullptr)
	{
		m_currentWidget = checkWidget;
	}
	return m_currentWidget;
}

GUItype CharacterInput::getWidgetType()
{
	return m_widgetType;
}

void CharacterInput::setUp(Widget * t_upWidget)
{
	m_upOption = t_upWidget;
	this->setDirectionWidgets();
}

void CharacterInput::setDown(Widget * t_downWidget)
{
	m_downOption = t_downWidget;
	this->setDirectionWidgets();
}

// Sets the Up, Down, Right and LEft of each button
void CharacterInput::setDirectionWidgets()
{
	int buttonArraySize = 26;
	int rowWidth = 10;
	for (int i = 0; i < buttonArraySize; i++)
	{
		// Left, check if there is a button to the left
		if ((i - 1) >= 0 && ((i - 1) != rowWidth-1 && (i - 1) != (rowWidth*2) -1))
		{
			m_boardText[i].setLeft(&m_boardText[i - 1]);
		}
		// Right , check if there is a button to the right
		if (i + 1 < buttonArraySize && ((i + 1) != rowWidth && (i + 1) != (rowWidth * 2)))
		{
			m_boardText[i].setRight(&m_boardText[i + 1]);
		}
		// Up, check if there is a button above
		if ((i - rowWidth) >= 0)
		{
			m_boardText[i].setUp(&m_boardText[i - rowWidth]);
		}
		else
		{
			m_boardText[i].setUp(m_upOption);
		}
		// Down, check if there is a button below
		if ((i + rowWidth) < buttonArraySize)
		{
			m_boardText[i].setDown(&m_boardText[i + rowWidth]);
		}
		else
		{
			m_boardText[i].setDown(m_downOption);
		}
	}
}

std::string CharacterInput::getButtonTag()
{
	return m_currentTagSelected;
}

bool CharacterInput::checkCollision(sf::Vector3f t_position)
{
	for (int i = 0; i < 26; i++)
	{
		if (m_boardText[i].checkCollision(t_position) == true)
		{
			m_currentTagSelected = m_boardText[i].getButtonTag();
			return true;
		}
	}
	return false;
}
