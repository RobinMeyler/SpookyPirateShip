#pragma once

// Made by: Robin Meyler, Josh Browne
// Date: Feburary - march 2019
// Time taken: ~ 40 hours


#include <iostream>

#include "ScreenTransitions.h"
#include "Collider.h"
#include "SFML/Graphics.hpp"
enum class lateralDirection
{
	Left,
	Right,
	None
};

enum class GameMode
{
	Licence,
	Splash,
	MainMenu,
	Gameplay,
	LevelEditor,
	LeaderBoard,
	Credits,
	Options,
	ControlInfo,
	Rules,
	SoundOptions,
	ArtOptions,
	Pause,
	Winning,
	CutScene,
	Upgrades,
	GameOver
};

enum class GUItype
{ 
	Widget,
	Button,
	Switch,
	Label,
	CheckBox,
	Radio,
	SideSlider,
	CharacterSelect
};

enum class PositionSetState
{
	DECIMAL,
	PERCENTAGE,
	EXACT
};

enum class buttonStyle
{
	NORMAL,
	SWITCH,
	FADED,
	TRANSPARENT
};

enum class buttonVisual
{
	RECTANGLE,
	TEXTURE
};

enum class buttonAnimationStyle
{
	FLASH,
	SHRINK, 
	HIGHLIGHT,
	NONE
};

enum class Sort
{
	STRING,
	VALUE
};

enum class WidgetTransitionState
{
	SETUP,
	INTRO,
	DISPLAY,
	EXIT,
	FINISH
};

enum class WidgetTransitionStyle
{
	VerticalMove,
	HorizontalMove,
	Rotate
};

enum class highLightState
{
	NotHighlighted,
	UnHighlighted,
	Highlighting,
	FullyHighlighted,
	UnHighlighting
};

enum class GameplayTurnState
{
	INPUT,		// read in players input
	UPDATE,		// update car movement with players input
};

enum class Layer
{
	background,
	play,
	front
};

enum class InputType
{
	controller,
	mouse
};

enum class doorStatus
{
	closed,
	opening,
	opened
};

static const float SCREEN_WIDTH = 1920;
static const float SCREEN_HEIGHT = 1280;
//static Xbox360Controller GAME_CONTROLLER;


