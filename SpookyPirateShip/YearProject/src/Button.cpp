
// Made by: Robin Meyler, Josh Browne
// Date: Feburary - march 2019
// Time taken: ~ 40 hours


#include "Button.h"
#include <iostream>

// 2 contructors, overloaded
Button::Button(sf::Texture const & t_texture, float t_width, float t_height) :
	m_texture(t_texture),
	m_buttonBox(sf::Vector2f{ t_width, t_height }),
	m_currentShrinkSize{ t_width, t_height },
	m_originalShrinkSize(m_currentShrinkSize),
	m_textColor(sf::Color::Black),
	m_buttonHeight{ t_height },
	m_buttonWidth{ t_width },
	m_filledColor(sf::Color(255, 255, 255)),
	m_unFilledColor(sf::Color(255, 255, 255)),
	m_flashColor(sf::Color(50, 50, 50))
{
	m_buttonBox.setSize(sf::Vector2f{ t_width, t_height });
	m_buttonBox.setTexture(&m_texture);
	m_buttonTag = "";
	m_buttonText.setPosition(m_buttonBox.getPosition() + sf::Vector2f(t_width / 2, t_height / 2));
	//m_buttonBox.setOrigin(t_width / 2, t_height / 2);
	m_currentTextureRect = { 0,0, (int)m_texture.getSize().x, (int)m_texture.getSize().y };
}

Button::Button(sf::Color & t_color, float t_width, float t_height) :
	m_buttonBox(sf::Vector2f{ t_width, t_height }),
	m_currentShrinkSize{ t_width, t_height },
	m_originalShrinkSize(m_currentShrinkSize),
	m_textColor(sf::Color::Black),
	m_buttonHeight{t_height},
	m_buttonWidth{t_width},
	m_filledColor(t_color),
	m_unFilledColor(sf::Color(255, 255, 255)),
	m_flashColor(sf::Color(50, 50, 50))

{
	m_buttonBox.setFillColor(t_color);
	//m_buttonBox.setOrigin(t_width / 2, t_height / 2);
	m_buttonText.setPosition(m_buttonBox.getPosition() + sf::Vector2f(t_width / 2, t_height / 2));
	m_buttonTag = "";
}

void Button::update(sf::Time t_deltaTime)
{
	// Main button Colour management --------------------------------------------
	if (m_buttonStyle == buttonStyle::NORMAL)
	{
		m_buttonBox.setFillColor(m_filledColor);
		m_buttonText.setTextColor(sf::Color(sf::Color(255, 0, 0, 255)));
	}
	else if (m_buttonStyle == buttonStyle::SWITCH)
	{
		if (m_isFilled)
		{
			m_buttonBox.setFillColor(m_filledColor);
			m_buttonText.setTextColor(sf::Color(0, 255, 0));
		}
		else
		{
			m_buttonBox.setFillColor(m_unFilledColor);
			m_buttonText.setTextColor(sf::Color(255, 0, 0));
		}
	}
	else if (m_buttonStyle == buttonStyle::FADED)
	{
		m_buttonBox.setFillColor(sf::Color(sf::Color(255, 255, 255, 100)));
		m_buttonText.setTextColor(sf::Color(sf::Color(255, 0, 0, 100)));
	}
	else if (m_buttonStyle == buttonStyle::TRANSPARENT)
	{
		m_buttonBox.setFillColor(sf::Color(sf::Color(255, 255, 255, 0)));
		m_buttonText.setTextColor(sf::Color(sf::Color(255, 0, 0, 0)));
	}

	if (m_input == InputType::controller)
	{
		// Button Animation ----------------------------------------------------------
		switch (m_currentHightlight)
		{
		case highLightState::Highlighting:
			doHightLighting();
			break;
		case highLightState::FullyHighlighted:
			m_animationCounter -= t_deltaTime.asSeconds();
			doHighLighted();
			break;
		case highLightState::UnHighlighting:
			doUnHightLighing();
			break;
		case highLightState::UnHighlighted:
			doUnhighLighted();
			break;
		case highLightState::NotHighlighted:
			// This so things don't keep running the unhighlighted code for no reason
			break;
		default:
			break;
		}
	}
	else if (m_input == InputType::mouse)
	{
		if (collide == true)
		{
			switch (m_currentHightlight)
			{
			case highLightState::Highlighting:
				doHightLighting();
				break;
			case highLightState::FullyHighlighted:
				m_animationCounter -= t_deltaTime.asSeconds();
				doHighLighted();
				break;
			case highLightState::UnHighlighting:
				doUnHightLighing();
				break;
			case highLightState::UnHighlighted:
				doUnhighLighted();
				break;
			case highLightState::NotHighlighted:
				// This so things don't keep running the unhighlighted code for no reason
				break;
			default:
				break;
			}
		}
	
	}
	m_buttonText.setPosition(m_buttonBox.getPosition() + sf::Vector2f(m_buttonWidth / 2, m_buttonHeight / 2));
}

// Highlight the button 
void Button::highlighted(sf::Time t_deltaTime)
{
	isInFocus = true;
	if(m_currentHightlight == highLightState::NotHighlighted)
		m_currentHightlight = highLightState::Highlighting;
}

// Set the button to not highlighted
void Button::notHightlighted()
{
	isInFocus = false;
	// This will start the button animation into ending stage if It is highlighted
	if (m_currentHightlight != highLightState::NotHighlighted)
	{
		m_currentHightlight = highLightState::UnHighlighting;
	}
}

void Button::render(sf::RenderWindow & t_window)
{
	t_window.draw(m_buttonBox);
	m_buttonText.render(t_window);
}

// Adds a set of partners to a button that will swap with the button (Used for game, but can be useful in other places)
void Button::addPartnerB(Button * t_radioButton)
{
	m_otherButtonsInSet.push_back(t_radioButton);
}

// Swaps a switch from filled to not filled and vice versa
void Button::swapState()
{
	if (m_isFilled == false && collide == true)
	{
		m_isFilled = true;
	}
	else
	{
		m_isFilled = false;
	}
	if (collide == true)
	{
		for (auto & buttons : m_otherButtonsInSet)
		{
			buttons->swapState();
		}
	}
}

// For switch buttons, starts it as filled
void Button::setSwitchFilled()
{
	m_isFilled = true;
}

// Pass the first int rect
void Button::setTextureAnimation(sf::IntRect & t_intRec, float t_speed, int numOfTextures)
{
	m_currentTextureRect = t_intRec;
	m_textureSpeed = t_speed;
	m_textIntJump = t_intRec.height;
	m_numOfJumps = numOfTextures;
	m_buttonBox.setTextureRect(m_currentTextureRect);
}

// Button Texture sheets must be stacked in single file for this to work in its currrent state
void Button::runTextureAnimation(sf::Time t_deltaTime)
{
	m_textureCounter += t_deltaTime.asSeconds();

	if (m_currentTextureNum < m_numOfJumps)			// If it hasn't gone to far
	{
		if (m_textureCounter > m_textureSpeed)
		{
			m_textureCounter = 0;							// reset timer
			int width = m_currentTextureRect.width;
			int height = m_currentTextureRect.height;
			m_currentTextureRect = { 0, m_textIntJump*m_currentTextureNum, width, height };			// Move to the next image
			m_buttonBox.setTextureRect(m_currentTextureRect);
			m_currentTextureNum++;
		}
	}
	else
	{
		int width = m_currentTextureRect.width;
		int height = m_currentTextureRect.height;
		m_currentTextureRect = { 0, 0, width, height };			// If it has gone too far, go back to the start
		m_buttonBox.setTextureRect(m_currentTextureRect);
		m_currentTextureNum = 1;
	}
}

// Intro action of the highlighting
void Button::doHightLighting()
{
	sf::Color tempColor = m_buttonBox.getOutlineColor();
	switch (m_animationStyle)
	{
	case buttonAnimationStyle::FLASH:
		m_currentHightlight = highLightState::FullyHighlighted;
		break;
	case buttonAnimationStyle::SHRINK:
		m_currentHightlight = highLightState::FullyHighlighted;
		break;
	case buttonAnimationStyle::HIGHLIGHT:
		// Change the color of the highlight from current to desired over time untill close enough to finish ----------------------------------------
		if ((   tempColor.r < m_highlightColor.r - (m_highLightSpeed*2) || tempColor.r > m_highlightColor.r + (m_highLightSpeed*2)))
		{
			if (tempColor.r < m_highlightColor.r)
			{
				tempColor.r += m_highLightSpeed;
			}
			else if (tempColor.r > m_highlightColor.r)
			{
				tempColor.r -= m_highLightSpeed;
			}
			if (tempColor.g < m_highlightColor.g)
			{
				tempColor.g += m_highLightSpeed;
			}
			else if (tempColor.g > m_highlightColor.g)
			{
				tempColor.g -= m_highLightSpeed;
			}
			if (tempColor.b < m_highlightColor.b)
			{
				tempColor.b += m_highLightSpeed;
			}
			else if(tempColor.b > m_highlightColor.b)
			{
				tempColor.b -= m_highLightSpeed;
			}
			m_buttonBox.setOutlineColor(tempColor);
		}
		else
		{
			m_currentHightlight = highLightState::FullyHighlighted;
		}
		break;
	default:
		break;
	}
}

// Display of the animation, stagnent
void Button::doHighLighted()
{
	switch (m_animationStyle)
	{
	case buttonAnimationStyle::FLASH:
		doFlash();
		break;
	case buttonAnimationStyle::SHRINK:
		doShrink();
		break;
	case buttonAnimationStyle::HIGHLIGHT:
		m_buttonBox.setOutlineColor(m_highlightColor);
		m_buttonText.setTextColor(m_highlightTextColor);
		break;
	default:
		break;
	}
}

// Outro for the animations
void Button::doUnHightLighing()
{
	sf::Color tempColor = m_buttonBox.getOutlineColor();
	switch (m_animationStyle)
	{
	case buttonAnimationStyle::FLASH:
		m_currentHightlight = highLightState::UnHighlighted;
		break;
	case buttonAnimationStyle::SHRINK:
		m_currentHightlight = highLightState::UnHighlighted;
		break;
	case buttonAnimationStyle::HIGHLIGHT:
		// Change the color of the highlight from current to desired over time untill close enough to finish in reverse ----------------------------------------
		if ((tempColor.r < m_outlineColor.r - (m_highLightSpeed * 2) || tempColor.r > m_outlineColor.r + (m_highLightSpeed * 2)))
		{
			if (tempColor.r < m_outlineColor.r)
			{
				tempColor.r += m_highLightSpeed;
			}
			else if (tempColor.r > m_outlineColor.r)
			{
				tempColor.r -= m_highLightSpeed;
			}
			if (tempColor.g < m_outlineColor.g)
			{
				tempColor.g += m_highLightSpeed;
			}
			else if (tempColor.g > m_outlineColor.g)
			{
				tempColor.g -= m_highLightSpeed;
			}
			if (tempColor.b < m_outlineColor.b)
			{
				tempColor.b += m_highLightSpeed;
			}
			else if (tempColor.b > m_outlineColor.b)
			{
				tempColor.b -= m_highLightSpeed;
			}
			m_buttonBox.setOutlineColor(tempColor);
		}
		else
		{
			m_currentHightlight = highLightState::UnHighlighted;
		}
		break;
	default:
		break;
	}
}

// Resets the highlighting parts so it can be restarted correctly
void Button::doUnhighLighted()
{
	switch (m_animationStyle)
	{
	case buttonAnimationStyle::FLASH:
		m_animationCounter = (m_flashSpeed * 2);
		m_currentHightlight = highLightState::NotHighlighted;
		break;
	case buttonAnimationStyle::SHRINK:
		m_currentShrinkSize = m_originalShrinkSize;
		m_buttonText.setTextSize(m_originalTextSize);
		m_buttonText.setOrigin();
		m_buttonBox.setSize(m_currentShrinkSize);
		m_buttonBox.setOrigin(m_currentShrinkSize.x / 2, m_currentShrinkSize.y / 2);
		m_currentHightlight = highLightState::NotHighlighted;
		break;
	case buttonAnimationStyle::HIGHLIGHT:
		m_buttonBox.setOutlineColor(m_outlineColor);
		m_buttonText.setTextColor(m_textColor);
		m_currentHightlight = highLightState::NotHighlighted;
		break;
	default:
		break;
	}
}

// Flash animation loop
void Button::doFlash()
{
	if (m_animationCounter > m_flashSpeed)
	{
		m_buttonBox.setFillColor(m_flashColor);
	}
	if (m_animationCounter < 0)
	{
		m_animationCounter = (m_flashSpeed * 2);
	}
}

// Shrink animation loop
void Button::doShrink()
{
	m_currentShrinkSize.x += m_direction;
	m_currentShrinkSize.y += m_direction;
	if (m_currentShrinkSize.x > m_originalShrinkSize.x + 5)
	{
		m_direction = -m_direction;
	}
	else if (m_currentShrinkSize.x < m_originalShrinkSize.x - 5)
	{
		m_direction = -m_direction;
	}

	m_buttonBox.setSize(m_currentShrinkSize);
	m_buttonBox.setOrigin(m_currentShrinkSize.x / 2, m_currentShrinkSize.y / 2);
}

bool Button::checkCollision(sf::Vector3f t_position)
{
	if (t_position.x > m_buttonBox.getPosition().x &&
		t_position.x < m_buttonBox.getPosition().x + m_buttonWidth &&
		t_position.y > m_buttonBox.getPosition().y &&
		t_position.y < m_buttonBox.getPosition().y + m_buttonHeight)
	{
		collide = true;
		return true;
	}
	else
	{
		collide = false;
	}
	return false;
}

std::string Button::getButtonTag()
{
	return m_buttonTag;
}

void Button::setButtonTag(std::string st)
{
	m_buttonTag = st;
}

void Button::setIndex(int t_index)
{
	index = t_index;
}

int Button::getIndex()
{
	return index;
}

void Button::setInputType(InputType inp)
{
	m_input = inp;
}

void Button::move(float x, float y)
{
	m_buttonBox.move(x, y);
	m_buttonText.move(x, y);
}

bool Button::getCollided()
{
	return collide;
}

// Takes an returns the redetermined action string if set but the intialize, gamepad not used right now but left in case altered later
std::string * Button::action()
{
	swapState();
	return &m_actionString;
}

// Sets action string
void Button::setActionString(std::string t_actionString)
{
	m_actionString = t_actionString;
}

// Set the On and Off colors of a switch button
void Button::setSwitchColorsColor(sf::Color t_filled, sf::Color t_unFilled)
{
	m_filledColor = t_filled;
	m_unFilledColor = t_unFilled;
}

// Set flash animation color
void Button::setFlashColor(sf::Color t_flashColor)
{
	m_flashColor = t_flashColor;
}

// Set the color of the outline highlight animation
void Button::setHightlightColor(sf::Color t_highlight, sf::Color t_textColor)
{
	m_highlightColor = t_highlight;
	m_highlightTextColor = t_textColor;
}

// Set the highlight animation speed
void Button::setHighLightSpeed(float t_speed)
{
	m_highLightSpeed = t_speed;
}

// Set a button to be in focus ( Time there because it was set up that way, remove)
void Button::setAsStarter()
{
	highlighted(sf::Time());
}

void Button::setFont(sf::Font & t_font)
{
	m_buttonText.setFont(t_font);
}

void Button::setFillcolor(sf::Color t_colour)
{
	m_buttonBox.setFillColor(t_colour);
	m_filledColor = t_colour;
}

void Button::setUnfilledColor(sf::Color t_color)
{
	m_unFilledColor = t_color;
}

// Takes outline color and thickness to condense 
void Button::setOutline(sf::Color t_color, float t_thickness)
{
	m_buttonBox.setOutlineThickness(t_thickness);
	m_buttonBox.setOutlineColor(t_color);
	m_outlineColor = t_color;
}

// Dynamic set position function that takes 0 -> 1.0, 0% -> 100% or exact values
// Also takes a Enum to tell the fucntion which to use
void Button::setPosition(float t_width, float t_height, PositionSetState t_settingStyle)
{
	switch (t_settingStyle)
	{
	case PositionSetState::DECIMAL:
		// clamping 0 -> 1
		t_width = std::min(std::max(t_width, 0.0f), 1.0f);
		t_height = std::min(std::max(t_height, 0.0f), 1.0f);
		m_buttonBox.setPosition(t_width * SCREEN_WIDTH, t_height * SCREEN_HEIGHT);
		m_buttonText.setPosition(m_buttonBox.getPosition());
		break;
	case PositionSetState::PERCENTAGE:
		// clamping 0 -> 100
		t_width = std::min(std::max(t_width, 0.0f), 100.0f);
		t_height = std::min(std::max(t_height, 0.0f), 100.0f);
		t_width /= 100;			// Make a decimal
		t_height /= 100;
		m_buttonBox.setPosition(t_width * SCREEN_WIDTH, t_height * SCREEN_HEIGHT);
		m_buttonText.setPosition(m_buttonBox.getPosition());
		break;
	case PositionSetState::EXACT:
		m_buttonBox.setPosition(t_width, t_height);
		m_buttonText.setPosition(m_buttonBox.getPosition());
		break;
	default:
		break;
	}
}

void Button::setPosition(sf::Vector2f t_pos)
{
	m_buttonBox.setPosition(t_pos);
	m_buttonText.setPosition(m_buttonBox.getPosition());
}

void Button::setRotation(float t_rotation)
{
	m_buttonBox.setRotation(t_rotation);
	m_buttonText.setRotation(t_rotation);
}

void Button::setOrigin(float t_x, float t_y)
{
	m_buttonBox.setOrigin(t_x, t_y);
}

void Button::resetOrigin()
{
	m_buttonBox.setOrigin(0,0);
}

void Button::setButtonAsSwitch()
{
	m_buttonStyle = buttonStyle::SWITCH;
}

void Button::setButtonAsFaded()
{
	m_buttonStyle = buttonStyle::FADED;
}

void Button::setButtonAsNormal()
{
	m_buttonStyle = buttonStyle::NORMAL;
}

void Button::setButtonAsTransparent()
{
	m_buttonStyle = buttonStyle::TRANSPARENT;
}

void Button::setString(std::string t_message, float t_size)
{
	m_buttonText.setString(t_message);
	m_buttonText.setTextSize(t_size);
	m_originalTextSize = t_size;
	m_buttonText.setOrigin();
	m_buttonText.setPosition(m_buttonBox.getPosition());
}

void Button::setTextOutline(sf::Color t_colour, float t_size)
{
	m_buttonText.setOutline(t_colour, t_size);
}

void Button::setTextColor(sf::Color t_textColor)
{
	m_textColor = t_textColor;
	m_buttonText.setTextColor(t_textColor);
}

void Button::setUp(Widget * t_upWidget)
{
	m_up = t_upWidget;
}

void Button::setDown(Widget * t_downWidget)
{
	m_Down = t_downWidget;
}

void Button::setRight(Widget * t_rightWidget)
{
	m_right = t_rightWidget;
}

void Button::setLeft(Widget * t_leftWidget)
{
	m_left = t_leftWidget;
}

void Button::setAnimationStyle(buttonAnimationStyle t_animeStyle)
{
	m_animationStyle = t_animeStyle;
}

// Set the flash animation speed
void Button::setFlashSpeed(float t_flashSpeed)
{
	m_flashSpeed = t_flashSpeed;
}

Widget * Button::getUp()
{
	isInFocus = false;
	return m_up;
}

Widget * Button::getDown()
{
	isInFocus = false;
	return m_Down;
}

Widget * Button::getRight()
{
	isInFocus = false;
	return m_right;
}

Widget * Button::getLeft()
{
	isInFocus = false;
	return m_left;
}

sf::Vector2f Button::getPosition()
{
	return m_buttonBox.getPosition();
}

// Used for the vertical slider 
float Button::getPositionY()
{
	return m_buttonBox.getPosition().y;
}

GUItype Button::getWidgetType()
{
	return m_widgetType;
}

bool Button::getIfFilled()
{
	return m_isFilled;
}

std::string Button::getActionString()
{
	return m_actionString;
}

float Button::getRotation()
{
	return m_buttonBox.getRotation();
}

std::string Button::getText()
{
	return m_buttonText.getString();
}

// Destructor
Button::~Button()
{
}
