#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite()
{
	m_current_frame = 0;
}

AnimatedSprite::AnimatedSprite(const sf::Texture& t) : 
	Sprite(t), 
	texture(t), 
	m_current_frame(0), 
	m_time(sf::seconds(0.25f)) 
{
}

AnimatedSprite::AnimatedSprite(const sf::Texture& t, const sf::IntRect& rect) : 
	Sprite(t), 
	m_current_frame(0), 
	m_time(sf::seconds(0.5f)) 
{
	m_frames.push_back(rect);
}

AnimatedSprite::~AnimatedSprite() {}

const sf::Clock& AnimatedSprite::getClock() {
	return m_clock;
}

const sf::Time& AnimatedSprite::getTime() {
	return m_time;
}

const std::vector<sf::IntRect>& AnimatedSprite::getFrames() {
	return m_frames;
}

const sf::IntRect& AnimatedSprite::getFrame(int n) {
	return m_frames[n];
}

void AnimatedSprite::addFrame(sf::IntRect& frame) {
	m_frames.push_back(frame);
}

const int AnimatedSprite::getCurrentFrame() {
	return m_current_frame;
}

void AnimatedSprite::update()
{
	if (m_clock.getElapsedTime() > m_time) {
		if (m_frames.size() > m_current_frame + 1)
		{
			m_current_frame++;
		}
		else {
			m_current_frame = 0;
		}
		m_clock.restart();
	}
}

sf::Texture AnimatedSprite::getTexture()
{
	return texture;
}
