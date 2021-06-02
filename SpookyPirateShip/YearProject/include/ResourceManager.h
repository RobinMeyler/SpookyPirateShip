#pragma once

#include "Thor/Resources.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	void addTexture(std::string t_ID, std::string t_texture);
	void addSoundBuffer(std::string t_ID, std::string t_soundBuffer);
	void addFont(std::string t_ID, std::string t_font);

	thor::ResourceHolder<sf::Texture, std::string> m_gameTextures;
	thor::ResourceHolder<sf::Font, std::string> m_gameFonts;
	thor::ResourceHolder<sf::SoundBuffer, std::string> m_gameSounds;
};

