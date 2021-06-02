#include "ResourceManager.h"



ResourceManager::ResourceManager()
{
}


ResourceManager::~ResourceManager()
{
}

void ResourceManager::addTexture(std::string t_ID, std::string t_texture)
{
	m_gameTextures.acquire(t_ID, thor::Resources::fromFile<sf::Texture>(t_texture));
}

void ResourceManager::addSoundBuffer(std::string t_ID, std::string t_soundBuffer)
{
	m_gameSounds.acquire(t_ID, thor::Resources::fromFile<sf::SoundBuffer>(t_soundBuffer));
}

void ResourceManager::addFont(std::string t_ID, std::string t_font)
{
	m_gameFonts.acquire(t_ID, thor::Resources::fromFile<sf::Font>(t_font));
}
