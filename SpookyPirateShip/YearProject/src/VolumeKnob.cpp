#include "VolumeKnob.h"

VolumeKnob::VolumeKnob(sf::Texture & t_texture) :
	m_knobSprite(t_texture)
{
	m_knobSprite.setOrigin(m_knobSprite.getLocalBounds().width / 2, m_knobSprite.getLocalBounds().height / 2);

	m_highlightCirlce.setRadius(80);
	m_highlightCirlce.setFillColor(sf::Color(sf::Color(255, 255, 0, m_opacity)));
	m_highlightCirlce.setOrigin(m_highlightCirlce.getRadius(), m_highlightCirlce.getRadius());
}

VolumeKnob::~VolumeKnob()
{

}

void VolumeKnob::update(sf::Time t_deltaTime)
{
	m_knobSprite.setRotation(m_rotation);
}

void VolumeKnob::render(sf::RenderWindow & t_window)
{
	t_window.draw(m_highlightCirlce);
	t_window.draw(m_knobSprite);
}

void VolumeKnob::highlighted(sf::Time t_deltaTime)
{
	switch (m_highlightState)
	{
	case VolumeKnob::highlightState::BRIGHTEN:
		m_opacity = m_opacity + 5;
		break;
	case VolumeKnob::highlightState::DIM:
		m_opacity = m_opacity - 5;
		break;
	default:
		break;
	}

	if (m_opacity > 250)
	{
		m_highlightState = highlightState::DIM;
	}
	if (m_opacity < 1)
	{
		m_highlightState = highlightState::BRIGHTEN;
	}

	m_highlightCirlce.setFillColor(sf::Color(sf::Color(255, 255, 0, m_opacity)));
}

void VolumeKnob::notHightlighted()
{
	m_opacity = 0;
	m_highlightCirlce.setFillColor(sf::Color(sf::Color(255, 255, 0, m_opacity)));
}

sf::Sprite VolumeKnob::getSprite()
{
	return m_knobSprite;
}

std::string VolumeKnob::getActionString()
{
	return m_actionString;
}

void VolumeKnob::setPosition(sf::Vector2f t_position)
{
	m_knobSprite.setPosition(t_position);
	m_highlightCirlce.setPosition(t_position);
}

void VolumeKnob::setActionString(std::string t_actionString)
{
	m_actionString = t_actionString;
}

Widget * VolumeKnob::getUp()
{
	return m_up;
}

Widget * VolumeKnob::getDown()
{
	return m_Down;
}

Widget * VolumeKnob::getRight()
{
	return m_right;
}

Widget * VolumeKnob::getLeft()
{
	return m_left;
}

void VolumeKnob::setUp(Widget * t_upWidget)
{
	m_up = t_upWidget;
}

void VolumeKnob::setDown(Widget * t_downWidget)
{
	m_Down = t_downWidget;
}

void VolumeKnob::setRight(Widget * t_rightWidget)
{
	m_right = t_rightWidget;
}

void VolumeKnob::setLeft(Widget * t_leftWidget)
{
	m_left = t_leftWidget;
}

void VolumeKnob::increaseRotation()
{
	m_rotation++;
}

void VolumeKnob::decreaseRotation()
{
	m_rotation--;
}
