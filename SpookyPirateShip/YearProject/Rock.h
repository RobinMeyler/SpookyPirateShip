#pragma once

#include <iostream>
#include <string>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "GUIGlobals.h"
#include "GUI.h"
#include "ResourceManager.h"
#include "Selector.h"


class Rock
{
public:
	Rock() {};
	Rock(ResourceManager& t_gameAssets, MyVector3 t_position);
	~Rock();
	
	void update(sf::Time t_deltaTime, MyVector3 mouseClick, bool pressed);
	void render(sf::RenderWindow& t_window, sf::Shader& lighting);
	void beThrown(MyVector3 m_landPosition);
	void collideStop(bool t_stop);
	MyVector3 getPosition();
	void setPosition(MyVector3 t_position);
	void setHeld(bool t_held);
	bool getHeld();
	bool checkEmitSound();

private:
	sf::Sprite m_rockSprite;
	MyVector3 position;
	MyVector3 m_prevPos;
	MyVector3 m_endPosition;
	MyVector3 direc;
	bool m_stopped;
	bool m_reset;
	bool m_held;
	bool m_emitSound;

	sf::SoundBuffer soundBuffer;
	sf::Sound sound;
};

