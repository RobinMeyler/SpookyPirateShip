// Made by: Robin Meyler, Josh Browne
// Date: Feburary - march 2019
// Time taken: ~ 40 hours


#include "GUI.h"

// Few default values that can be reset
GUI::GUI() :
	m_sliderMoveSpeed(10),
	m_transitionSpeed(0),
	m_transition{WidgetTransitionState::DISPLAY}
{
	int temp = 50;
	m_transitionSpeed = &temp;
}

// Delete heap memory when being destroyed
GUI::~GUI()
{
	for (int i = m_widgets.size() - 1; i > 0; i--)
	{
		delete m_widgets.at(i);
	}
	if (m_sliderActive == true)
	{
		delete m_slider;
	}
	if (m_leaderboards.size() > 0)
	{
		for (int i = m_leaderboards.size() - 1; i > 0; i--)
		{
			delete m_leaderboards.at(i);
		}
	}
}
void GUI::update(sf::Time t_deltaTime)
{
	switch (m_transitionStyle)
	{
	case WidgetTransitionStyle::HorizontalMove:

		break;
	case WidgetTransitionStyle::VerticalMove:
		verticalTransition(t_deltaTime);
		break;
	case WidgetTransitionStyle::Rotate:
		rotateTransition(t_deltaTime);
		break;
	default:
		break;
	}
	timeManager += t_deltaTime.asSeconds();
}
void GUI::update(sf::Time t_deltaTime, sf::Vector3f t_mousePos)
{
	if (m_gameInput == InputType::controller)
	{
		switch (m_transitionStyle)
		{
		case WidgetTransitionStyle::HorizontalMove:

			break;
		case WidgetTransitionStyle::VerticalMove:
			verticalTransition(t_deltaTime);
			break;
		case WidgetTransitionStyle::Rotate:
			rotateTransition(t_deltaTime);
			break;
		default:
			break;
		}
	}
	else if (m_gameInput == InputType::mouse)
	{
		bool col = false;
		for (int i = 0; i < m_widgets.size(); i++)
		{
			if (m_widgets.at(i)->getWidgetType() == GUItype::Button)
			{
				col = m_widgets.at(i)->checkCollision(t_mousePos);
			}
			if (col == true)
			{
				m_currentWidget = m_widgets.at(i);
				m_widgets.at(i)->highlighted(t_deltaTime);
			}
			else 
			{
			
			}
			m_widgets.at(i)->update(t_deltaTime);
		}
	}
	timeManager += t_deltaTime.asSeconds();
}

void GUI::render(sf::RenderWindow & t_window)
{
	for (int i = 0; i < m_widgets.size(); i++)
	{
		m_widgets.at(i)->render(t_window);
	}
	for (int i = 0; i < m_leaderboards.size(); i++)
	{
		m_leaderboards.at(i)->render(t_window);
	}
	if (m_sliderActive == true)
	{
		m_slider->render(t_window);
	}
}

// Clears heap memory and vecotrs for reinitialization
void GUI::clearGUI()
{
	for (int i = m_widgets.size() - 1; i > 0; i--)
	{
		delete m_widgets.at(i);
	}
	if (m_sliderActive == true)
	{
		delete m_slider;
	}
	if (m_leaderboards.size() > 0)
	{
		for (int i = m_leaderboards.size() - 1; i > 0; i--)
		{
			delete m_leaderboards.at(i);
		}
	}
	if (m_transition == WidgetTransitionState::FINISH)
	{
		m_transition = WidgetTransitionState::SETUP;
	}
	else
	{
		m_transition = WidgetTransitionState::DISPLAY;
	}
	m_widgets.clear();
	m_leaderboards.clear();
}

// Adds a widget to the vector of display widgets
void GUI::addWidget(Widget *t_widget)
{
	m_widgets.push_back(t_widget);
	if (t_widget->getWidgetType() == GUItype::Button)
	{
		m_WigetPositions.push_back(t_widget->getPosition());
	}
}

Widget* GUI::getCurrentWidget()
{
	return m_currentWidget;
}

// If a leaderboard is in use, fill the vector with entries, sorting them as they fill to make sure it only fills to 10 and omnly have to check the last one when sorted
void GUI::addLeaderboardEntry(LeaderboardEntry * t_entry)
{
	if (m_leaderboards.size() < 10)
	{
		m_leaderboards.push_back(t_entry);
		sortLeaderBoard(Sort::VALUE);
	}
	else
	{
		if (m_leaderboards.at(9)->getValue() > t_entry->getValue())
		{
			m_leaderboards.pop_back();
			m_leaderboards.push_back(t_entry);
			sortLeaderBoard(Sort::VALUE);
		}
	}
}

// Sets a start position and spacing to fill a board of entries
void GUI::setLeaderboardStartPosition(sf::Vector2f t_startPos, float t_spaceBetween, float t_spaceWideApart)
{
	for (int i = 0; i < m_leaderboards.size(); i++)
	{
		m_leaderboards.at(i)->setPosition(t_startPos + sf::Vector2f{ 0, i*t_spaceBetween }, t_spaceWideApart);
	}
}

// Sorting conditions-----------------------------------------------------------------------------
// Used with Quick sort to order the leaderboard
bool compareValue( const LeaderboardEntry * lhs, const LeaderboardEntry * rhs)
{
	return lhs->getValue() < rhs->getValue();
}

bool compareString(const LeaderboardEntry * a, const LeaderboardEntry * b) {
	const std::string a_name = a->getString();
	const std::string b_name = b->getString();
	bool compare = (a_name < b_name);
	return compare;
}
// ----------------------------------------------------------------------------------------------------

// Sort leaderboard using above function to decide which way to order it
void GUI::sortLeaderBoard(Sort t_sort)
{
	if (m_leaderboards.size() > 0)
	{
		if (t_sort == Sort::STRING)			// Alphabetical
		{
			std::sort(m_leaderboards.begin(), m_leaderboards.end(), compareString);
			this->resetBorderOrder();
			m_currentWidget = m_leaderboards.at(0);
		}
		else if (t_sort == Sort::VALUE)		// By number
		{
			std::sort(m_leaderboards.begin(),
				m_leaderboards.end(),
				compareValue);
			this->resetBorderOrder();
			m_currentWidget = m_leaderboards.at(0);
		}
	}
}

float GUI::getCurrentWidgetY()
{
	return m_currentWidget->getPositionY();
}

// returns switch buttons filled
int GUI::getNumOfFilled()
{
	int numOf = 0;
	for(int i = 0; i < m_widgets.size(); i++)
		if (m_widgets.at(i)->getWidgetType() == GUItype::Button && m_widgets.at(i)->getIfFilled() == true)
		{
			numOf++;
		}
	return numOf;
}

// Set animation style of each button
void GUI::setAnimationStyle(buttonAnimationStyle t_anime)
{
	for (int i = 0; i < m_widgets.size(); i++)
	{
		if (m_widgets.at(i)->getWidgetType() == GUItype::Button)
		{
			m_widgets.at(i)->setAnimationStyle(t_anime);
		}
	}
}

// Start focus for the GUI
void GUI::setStartFocus(Widget * t_widget)
{
	m_currentWidget = t_widget;
}

// Move the focus to a leaderbaord from normal widgets
void GUI::setFocusToLeaderBoard()
{
	m_previousWidget = m_currentWidget;
	m_currentWidget = m_leaderboards.at(0);
}

// Back to widgets from leaderboard
void GUI::setFocusToPrevious()
{
	m_currentWidget = m_previousWidget;
	m_previousWidget = m_leaderboards.at(0);
}

// Sets the Up and down widgets for the leaderboard after it has being sort
// Dyamically rests the order and resets the player to the top of the board
void GUI::resetBorderOrder()
{
	for (int i = 0; i < m_leaderboards.size(); i++)
	{
		if (i - 1 >= 0)
		{
			m_leaderboards.at(i)->setUp(m_leaderboards.at(i - 1));
		}
		else
		{
			m_leaderboards.at(i)->setUp(nullptr);
		}
		if (i + 1 < m_leaderboards.size())
		{
			m_leaderboards.at(i)->setDown(m_leaderboards.at(i + 1));
		}
		else
		{
			m_leaderboards.at(i)->setDown(nullptr);
		}
	}
}

// Plays music and returns the action string of the widget in current focus
std::string * GUI::processInput()
{
	if (m_buttonSelectBool != nullptr && *m_buttonSelectBool)
	{
		m_buttonSelectSound.play();
	}
	return m_currentWidget->action();
}

void GUI::setTransitionStyle(WidgetTransitionStyle t_style)
{
	m_transitionStyle = t_style;
}

// Set button transition state
void GUI::setTransitionState(WidgetTransitionState t_state)
{
	m_transition = t_state;
}

WidgetTransitionState GUI::getTransitionState()
{
	return m_transition;
}

// Set button tranisition speed
void GUI::setTransitionSpeed(int * t_speed)
{
	m_transitionSpeed = t_speed;
}

void GUI::verticalTransition(sf::Time t_deltaTime)
{
	m_SwapIn = true;
	m_SwapOut = true;
	j = 0;
	k = 0;
	n = 0;
	switch (m_transition)
	{
	case WidgetTransitionState::SETUP:
		runSetupTransition();
		break;
	case WidgetTransitionState::INTRO:
		runIntroTransition();
		break;
	case WidgetTransitionState::DISPLAY:
		for (int i = 0; i < m_widgets.size(); i++)
		{
			m_widgets.at(i)->update(t_deltaTime);
		}
		if (m_currentWidget->getWidgetType() != GUItype::Button)
		{
			m_currentWidget->highlighted(t_deltaTime);
		}
		break;
	case WidgetTransitionState::EXIT:
		runExitTransition();
		break;
	case WidgetTransitionState::FINISH:
		break;
	default:
		break;
	}
}

void GUI::rotateTransition(sf::Time deltaTime)
{
	switch (m_transition)
	{
	case WidgetTransitionState::SETUP:
		// Done with placement
		break;
	case WidgetTransitionState::INTRO:
		for (int i = 0; i < m_widgets.size(); i++)
		{
			if (m_widgets.at(i)->getWidgetType() == GUItype::Button)
			{
				MyVector3 distance = MyVector3{ m_widgets.at(i)->getPosition().x, m_widgets.at(i)->getPosition().y, 1 } - MyVector3{ 600,400, 1 };
				float angleBet = atan2(-distance.y, distance.x);			// Inverse tan of the distance, gives angle
				angleBet = angleBet * (180 / 3.14);							// Degrees
			
				angleBet = angleBet + m_rotateSpeed;							// Make change 
				double radius = 300;
				float newX = radius * cos(angleBet*(3.14 / 180));			// New X and Y returned to radians
				float newY = radius * sin(angleBet*(3.14 / 180));
				m_widgets.at(i)->setPosition(MyVector3{ 600,400, 1 } + sf::Vector2f{ newX, -newY });		// Set wdiget

				m_widgets.at(i)->setRotation(-angleBet + 90);
			}
		}
		m_finalRotatePosition = m_finalRotatePosition + (std::sqrt((m_rotateSpeed*m_rotateSpeed)));
		if (m_rotateAmount == m_finalRotatePosition)
		{
			m_transition = WidgetTransitionState::DISPLAY;
			m_finalRotatePosition = 0;
		}
		break;
	case WidgetTransitionState::DISPLAY:
		for (int i = 0; i < m_widgets.size(); i++)
		{
			m_widgets.at(i)->update(deltaTime);
		}
		if (m_currentWidget->getWidgetType() != GUItype::Button)
		{
			m_currentWidget->highlighted(deltaTime);
		}
		break;
	case WidgetTransitionState::EXIT:
		
		break;
	case WidgetTransitionState::FINISH:
		break;
	default:
		break;
	}
}

void GUI::setRotateInfo(float t_amount, float t_speed)
{
	m_rotateAmount = t_amount;
	m_rotateSpeed = t_speed;
}

void GUI::rotate(int t_direction)
{
	if (t_direction == 1)
	{
		if (m_rotateSpeed < 0)
		{
			m_rotateSpeed = -m_rotateSpeed;
		}
	}
	else if (t_direction == 0)
	{
		if (m_rotateSpeed > 0)
		{
			m_rotateSpeed = -m_rotateSpeed;
		}
	}
	m_transition = WidgetTransitionState::INTRO;
}

// This runs the set up in the intialize of a screen to avoid the jaring reposition sometimes visible at the start of the program
void GUI::runSetupTransition()
{
	for (int i = 0; i < m_widgets.size(); i++)
	{
		if (m_widgets.at(i)->getWidgetType() == GUItype::Button)
		{
			m_widgets.at(i)->setPosition(sf::Vector2f{ m_widgets.at(i)->getPosition().x, m_widgets.at(i)->getPosition().y + SCREEN_HEIGHT });
		}
	}
	m_transition = WidgetTransitionState::INTRO;
}

// Intro transition
void GUI::runIntroTransition()
{
	for (int i = 0; i < m_widgets.size(); i++)
	{
		if (m_widgets.at(i)->getWidgetType() == GUItype::Button)
		{
			if (m_widgets.at(i)->getPosition().y > m_WigetPositions.at(j).y)
			{
				m_SwapIn = false;
			}
			j++;
		}
	}
	if (m_SwapIn == true)
	{
		for (int i = 0; i < m_widgets.size(); i++)
		{
			if (m_widgets.at(i)->getWidgetType() == GUItype::Button)
			{
				m_widgets.at(i)->setPosition(m_WigetPositions.at(k));
				k++;
			}
		}
		m_transition = WidgetTransitionState::DISPLAY;
	}
	else
	{
		for (int i = 0; i < m_widgets.size(); i++)
		{
			if (m_widgets.at(i)->getWidgetType() == GUItype::Button)
			{
				m_widgets.at(i)->setPosition(sf::Vector2f{ m_widgets.at(i)->getPosition().x, m_widgets.at(i)->getPosition().y - *m_transitionSpeed });
			}
		}
	}
}

// Outro transition
void GUI::runExitTransition()
{
	for (int i = 0; i < m_widgets.size(); i++)
	{
		if (m_widgets.at(i)->getWidgetType() == GUItype::Button)
		{
			if (m_widgets.at(i)->getPosition().y < (m_WigetPositions.at(n).y + SCREEN_HEIGHT))
			{
				m_SwapOut = false;
			}
			n++;
		}
	}
	if (m_SwapOut == true)
	{
		m_transition = WidgetTransitionState::FINISH;
	}
	else
	{
		for (int i = 0; i < m_widgets.size(); i++)
		{
			if (m_widgets.at(i)->getWidgetType() == GUItype::Button)
			{
				m_widgets.at(i)->setPosition(sf::Vector2f{ m_widgets.at(i)->getPosition().x, m_widgets.at(i)->getPosition().y + *m_transitionSpeed });
			}
		}
	}
}

// Gets button tranisition state
WidgetTransitionState GUI::getState()
{
	return m_transition;
}

// This sets the min, max of the screen. IIF the max is great than screen height, then a slider is created and is in effect for the GUI
// Since there is only 1 per screen, keep it off the user and dynamic to the GUI
// Offset is how farm formt he center of the screen in terms of Y the view can move before the screen adjusts
void GUI::setViewMinMax(float t_min, float t_max, float t_offSet)
{
	if (t_max > SCREEN_HEIGHT)
	{
		m_slider = new VerticalSlider(t_max, 20);
		m_sliderActive = true;
	}
	m_screenMin = t_min;
	m_screenMax = t_max;
	m_offsetFromLimit = t_offSet;

}

// Adjust the position when the slider is active and the screen view needs to change so the user can see the desired information
// on parts fo the screen that may be below Screen Height
void GUI::adjustPosition(sf::View & t_view)
{
	if (m_sliderActive == true)
	{
		if (m_currentWidget->getPositionY() < t_view.getCenter().y - m_offsetFromLimit)
		{
			t_view.move(0, -m_sliderMoveSpeed);
			m_slider->moveView(-m_sliderMoveSpeed, t_view.getCenter());
		}
		if (m_currentWidget->getPositionY() > t_view.getCenter().y + m_offsetFromLimit)
		{
			t_view.move(0, m_sliderMoveSpeed);
			m_slider->moveView(m_sliderMoveSpeed, t_view.getCenter());
		}
	}

}

void GUI::setSliderMoveSpeed(float t_speed)
{
	m_sliderMoveSpeed = t_speed;
}

// Plays sound effect if one is added
// Checks if the Direction widget existins, sets it to current focus if it does
// Unhighlights other widgets
void GUI::moveUp()
{
	Widget * checkWidget = m_currentWidget->getUp();
	if (checkWidget != nullptr)
	{
		m_currentWidget = checkWidget;
		for (int i = 0; i < m_widgets.size(); i++)
		{
			m_widgets.at(i)->notHightlighted();
		}
	}
	m_currentWidget->highlighted(sf::Time());
	if (m_buttonChangeBool != nullptr && *m_buttonChangeBool)
	{
		m_buttonChangeSound.play();
	}
}

// Plays sound effect if one is added
// Checks if the Direction widget existins, sets it to current focus if it does
// Unhighlights other widgets
void GUI::moveDown()
{
	Widget * checkWidget = m_currentWidget->getDown();
	if (checkWidget != nullptr)
	{
		m_currentWidget = checkWidget;
	}
	for (int i = 0; i < m_widgets.size(); i++)
	{
		m_widgets.at(i)->notHightlighted();
	}
	m_currentWidget->highlighted(sf::Time());
	if (m_buttonChangeBool != nullptr && *m_buttonChangeBool)
	{
		m_buttonChangeSound.play();
	}
}

// Plays sound effect if one is added
// Checks if the Direction widget existins, sets it to current focus if it does
// Unhighlights other widgets
void GUI::moveRight()
{
	Widget * checkWidget = m_currentWidget->getRight();
	if (checkWidget != nullptr)
	{
		m_currentWidget = checkWidget;
		for (int i = 0; i < m_widgets.size(); i++)
		{
			m_widgets.at(i)->notHightlighted();
		}
	}
	m_currentWidget->highlighted(sf::Time());
	if (m_buttonChangeBool != nullptr && *m_buttonChangeBool)
	{
		m_buttonChangeSound.play();
	}
}

// Plays sound effect if one is added
// Checks if the Direction widget existins, sets it to current focus if it does
// Unhighlights other widgets
void GUI::moveLeft()
{
	Widget * checkWidget = m_currentWidget->getLeft();
	if (checkWidget != nullptr)
	{
		m_currentWidget = checkWidget;
		for (int i = 0; i < m_widgets.size(); i++)
		{
			m_widgets.at(i)->notHightlighted();
		}
	}
	m_currentWidget->highlighted(sf::Time());
	if (m_buttonChangeBool != nullptr && *m_buttonChangeBool)
	{
		m_buttonChangeSound.play();
	}
}

std::pair<std::string, int> GUI::findSelected(MyVector3 mousePosition)
{
	bool col = false;
	for (int i = 0; i < m_widgets.size(); i++)
	{
		if (m_widgets.at(i)->getWidgetType() == GUItype::Button)
		{
			col = m_widgets.at(i)->checkCollision(mousePosition);
			if (col == true)
			{
				timeManager = 0;
				std::cout << m_widgets.at(i)->getButtonTag() << std::endl;
				std::pair<std::string, int> tempPair;
				tempPair.first = m_widgets.at(i)->getButtonTag();
				tempPair.second = m_widgets.at(i)->getIndex();
				std::string *waste = m_widgets.at(i)->action();
				return tempPair;
			}
		}
		else if (m_widgets.at(i)->getWidgetType() == GUItype::CharacterSelect)
		{
			col = m_widgets.at(i)->checkCollision(mousePosition);
			std::pair<std::string, int> tempPair;
			tempPair.first = m_widgets.at(i)->getButtonTag();
			tempPair.second = 0;
			return tempPair;
		}
	}
	std::pair<std::string, int> tempPairFail;
	tempPairFail.first = "NAN";
	tempPairFail.second = -1;
	return tempPairFail;
}


// Sets sound effect options
void GUI::setSoundBuffer(sf::SoundBuffer * t_buttonChangeBuffer, bool * t_buttonChangeBool, sf::SoundBuffer * t_buttonSelectBuffer, bool * t_buttonSelectBool, sf::SoundBuffer * t_buttonBackBuffer, bool * t_buttonBackBool)
{
	m_buttonChangeSound.setBuffer(*t_buttonChangeBuffer);
	m_buttonChangeBool = t_buttonChangeBool;
	m_buttonSelectSound.setBuffer(*t_buttonSelectBuffer);
	m_buttonSelectBool = t_buttonSelectBool;
	m_buttonBackSound.setBuffer(*t_buttonBackBuffer);
	m_buttonBackBool = t_buttonBackBool;
}

std::vector<Widget*>& GUI::getWidgets()
{
	return m_widgets;
}

void GUI::movewidgets(float x, float y)
{
	for (int i = 0; i < m_widgets.size(); i++)
	{
		m_widgets.at(i)->move(x,y);
	}
}

void GUI::setWidgetPositons(std::vector<sf::Vector2f>& t_positions)
{
	if (t_positions.size() == m_widgets.size())
	{
		for (int i = 0; i < m_widgets.size(); i++)
		{
			m_widgets.at(i)->setPosition(t_positions.at(i));
		}
	}
}

void GUI::setInput(InputType input)
{
	m_gameInput = input;
}

