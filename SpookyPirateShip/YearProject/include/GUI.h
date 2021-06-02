#pragma once

// Made by: Robin Meyler, Josh Browne
// Date: Feburary - march 2019
// Time taken: ~ 40 hours


#include <iostream>
#include <string>
#include <vector>
#include "Widget.h"
#include "Button.h"
#include "LeaderboardEntry.h"
#include "VerticalSlider.h"
#include "VolumeKnob.h"
#include <SFML/Audio.hpp>
#include "MyVector3.h"

class GUI
{
public:
	GUI();
	~GUI();
	void update(sf::Time t_deltaTime);
	void update(sf::Time t_deltaTime, sf::Vector3f t_mousePos);
	void render(sf::RenderWindow & t_window);
	void clearGUI();								// Deletes heap, clears vectors
	void addWidget(Widget *t_widget);						// Adds widget to the set

	Widget* getCurrentWidget();

	void setStartFocus(Widget *t_widget);						// Sets the focus of the first widget on the screen
	float getCurrentWidgetY();									// Gets current Y for position use in game
	int getNumOfFilled();										// Returns number filled when using Switch buttons
	void setAnimationStyle(buttonAnimationStyle t_anime);
	std::string *processInput();


	// Transisiton functions ------------------------------------------------
	void setTransitionStyle(WidgetTransitionStyle t_style);
	void setTransitionState(WidgetTransitionState t_state);
	WidgetTransitionState getTransitionState();
	void setTransitionSpeed(int *t_speed);



	void verticalTransition(sf::Time deltaTime);
	void rotateTransition(sf::Time deltaTime);

	void setRotateInfo(float t_amount, float t_speed);
	void rotate(int t_direction);
	void runSetupTransition();
	void runIntroTransition();
	void runExitTransition();
	WidgetTransitionState getState();



	// Slider functions -----------------------------------------------------
	void setViewMinMax(float t_min, float t_max, float t_offSet);		// Min(usually 0) Max(SCREENHEIGHT + etc) Offset (up and down distance from center of screen)
	void adjustPosition(sf::View & t_view);								// Gets inFocus Y and moves the View to that
	void setSliderMoveSpeed(float t_speed);					

	// Leaderboard Functions -------------------------------------------------
	void setLeaderboardStartPosition(sf::Vector2f t_startPos, float t_spaceBetween, float t_spaceWideApart);		// Sets where the list down starts and spacing
	void addLeaderboardEntry(LeaderboardEntry * t_entry);		
	void sortLeaderBoard(Sort t_sort);						// Sorts Leaderboard by Sort type
	void setFocusToLeaderBoard();							// Puts focus on Leaderboard Widgets
	void setFocusToPrevious();								// This puts the focus back on the normal Widgets off od Leaderbaord
	void resetBorderOrder();								// Resets board after a Sort

	// Move Widget focus
	void moveUp();
	void moveDown();
	void moveRight();
	void moveLeft();

	// New
	std::pair<std::string, int> findSelected(MyVector3 mousePosition);

	// Sound Functions-------------------------------------------------------
	void setSoundBuffer(sf::SoundBuffer * t_buttonChangeBuffer, bool * t_buttonChangeBool,sf::SoundBuffer * t_buttonSelectBuffer, bool * t_buttonSelectBool,sf::SoundBuffer * t_buttonBackBuffer, bool * t_buttonBackBool);

	std::vector<Widget*>& getWidgets();
	void movewidgets(float x, float y);
	void setWidgetPositons(std::vector<sf::Vector2f> &t_positions);
	void setInput(InputType input);
private:
	WidgetTransitionState m_transition;
	WidgetTransitionStyle m_transitionStyle;
	InputType m_gameInput = InputType::controller;
	// GUI Widgets
	std::vector<Widget*> m_widgets;
	std::vector<sf::Vector2f> m_WigetPositions; // Final positions tracked for button transisitions

	// Leaderboard Entries (if Exist)
	std::vector<LeaderboardEntry *> m_leaderboards;

	Widget * m_currentWidget;
	Widget * m_previousWidget;

	// Slider
	// Slider only intialized if the screen in greater than SCREEN_HEIGHT
	VerticalSlider * m_slider;

	// Vairable speed and status
	bool m_sliderActive{ false };
	int *m_transitionSpeed;
	float m_sliderMoveSpeed;
	float m_screenMin;
	float m_screenMax;
	float m_offsetFromLimit;

	float m_rotateAmount{ 90 };
	float m_finalRotatePosition{ 0 };
	float m_rotateSpeed{ 1 };

	float timeManager{ 0 };
	// Transition variables
	bool m_SwapIn{ true };
	bool m_SwapOut{ true };
	// Array counters
	int j{ 0 };
	int k{ 0 };
	int n{ 0 };

	// Sounds ------------------------------------------
	sf::Sound m_buttonChangeSound;
	sf::Sound m_buttonSelectSound;
	sf::Sound m_buttonBackSound;
	bool * m_buttonSelectBool{ nullptr };
	bool * m_buttonChangeBool{ nullptr };
	bool * m_buttonBackBool{ nullptr };
};

