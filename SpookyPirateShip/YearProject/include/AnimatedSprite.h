#pragma once
#include <SFML/Graphics.hpp>


class AnimatedSprite : public sf::Sprite {
public:
	AnimatedSprite();
	AnimatedSprite(const sf::Texture&);
	AnimatedSprite(const sf::Texture&, const sf::IntRect&);
	~AnimatedSprite();

	const sf::Clock& getClock();
	const sf::Time& getTime();
	const std::vector<sf::IntRect>& getFrames();
	const sf::IntRect& getFrame(int);
	void addFrame(sf::IntRect&);
	const int getCurrentFrame();
	void update();	// index to show which state

	sf::Texture getTexture();

private:
	sf::Clock m_clock;
	sf::Time m_time;
	std::vector<sf::IntRect> m_frames;
	int m_current_frame;
	sf::Texture texture;
};