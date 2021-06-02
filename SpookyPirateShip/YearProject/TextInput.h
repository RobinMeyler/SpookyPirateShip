#pragma once


#include <iostream>
#include <string>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "GUIGlobals.h"
#include "GUI.h"
#include "ResourceManager.h"
#include "Selector.h"

class TextInput
{
public:
	TextInput();
	~TextInput();
	
private:
	std::string m_name;
	sf::RectangleShape m_box;



};