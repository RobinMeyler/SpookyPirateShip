#pragma once

/// <summary>
/// Volume Knob widget (originally for joint project Racing Game)
/// </summary>

#include "Widget.h"

class VolumeKnob : public Widget
{
public:
	// Structors -----------------------------------------------
	VolumeKnob(sf::Texture & t_texture);
	~VolumeKnob();

	// Virtual overrides ---------------------------------------
	void update(sf::Time t_deltaTime) override;
	void render(sf::RenderWindow & t_window) override;
	void highlighted(sf::Time t_deltaTime) override;
	void notHightlighted() override;


	sf::Sprite getSprite();
	std::string getActionString();

	void setPosition(sf::Vector2f t_position);
	void setActionString(std::string t_actionString) override;		// Buttons action task

	// Getters -------------------------
	Widget * getUp() override;
	Widget * getDown() override;
	Widget * getRight() override;
	Widget * getLeft() override;

	// Setting button direction -------------------------------------
	void setUp(Widget * t_upWidget);
	void setDown(Widget * t_downWidget);
	void setRight(Widget * t_rightWidget);
	void setLeft(Widget * t_leftWidget);

	// Rotate
	void increaseRotation() override;
	void decreaseRotation() override;

private:
	sf::Sprite m_knobSprite; // the sprite of the volume knob
	int m_rotation;

	sf::CircleShape m_highlightCirlce; // circle that pulsates to show focus on knob
	int m_opacity{ 0 };
	enum class highlightState { BRIGHTEN, DIM};
	highlightState m_highlightState{ highlightState::BRIGHTEN };

	std::string m_actionString = "";

	// Pointer to adjacent buttons
	Widget *m_up{ nullptr };
	Widget *m_Down{ nullptr };
	Widget *m_right{ nullptr };
	Widget *m_left{ nullptr };
};