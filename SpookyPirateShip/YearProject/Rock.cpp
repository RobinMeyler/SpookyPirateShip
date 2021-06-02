#include "Rock.h"

Rock::Rock(ResourceManager& t_gameAssets, MyVector3 t_position) :
	m_rockSprite(t_gameAssets.m_gameTextures["Rock"]),
	position(t_position),
	m_stopped(true),
	m_held(false)
{
	m_prevPos = position;
	m_rockSprite.setPosition(position);
	m_rockSprite.setOrigin(8, 8);

	if (!soundBuffer.loadFromFile("Assets/Audio/rockImpact.wav"))
	{
		std::cout << "ERROR, loading sound (rock)" << std::endl;
	}
	sound.setBuffer(soundBuffer);
}

Rock::~Rock()
{
}

void Rock::update(sf::Time t_deltaTime, MyVector3 mouseClick, bool pressed)
{
	m_prevPos = position;
	if (m_reset == true && m_held == true)
	{
		m_held = false;
		direc = mouseClick - position;
		direc.normalise();
		MyVector3 dist = direc * 250;
		float One = (dist).length();
		float Two = (mouseClick - position).length();

		if (One < Two)
		{
			m_endPosition = position + dist;
		}
		else
		{
			m_endPosition = mouseClick;
		}
		m_reset = false;
	}
	if (position != m_endPosition && m_stopped == false)
	{
		position = position + direc * 10;
		float x = (position.x - m_endPosition.x);
		float y = (position.y - m_endPosition.y);
		x = sqrt(x * x);
		y = sqrt(y * y);

		if( x < 10 && y < 10)	// Close
		{ 
			position = m_endPosition;
			m_stopped = true;
			m_emitSound = true;
		}
	}
	m_rockSprite.setPosition(position);
}

void Rock::render(sf::RenderWindow& t_window, sf::Shader& lighting)
{
	t_window.draw(m_rockSprite, &lighting);
}

void Rock::beThrown(MyVector3 m_landPosition)
{
	m_endPosition = m_landPosition;
	m_stopped = false;
	m_reset = true;
}

void Rock::collideStop(bool t_stop)
{
	if (t_stop == true)
	{
		m_stopped = true;
		if (!m_held)
		{
			m_emitSound = true;
			position = m_prevPos;  // moved here to fix glitch -josh
		}
		
	}
}

MyVector3 Rock::getPosition()
{
	return position;
}

void Rock::setPosition(MyVector3 t_position)
{
	position = t_position;
}

void Rock::setHeld(bool t_held)
{
	m_held = t_held;
}

bool Rock::getHeld()
{
	return m_held;
}

bool Rock::checkEmitSound()
{
	if (m_emitSound)
	{
		if (sound.getStatus() != sf::Sound::Status::Playing)
		{
			sound.play();
		}
		m_emitSound = false;
		return true;
	}
	return false;
}
