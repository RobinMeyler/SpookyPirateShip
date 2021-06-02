#pragma once

// Made by: Robin Meyler, Josh Browne
// Date: Feburary - march 2019
// Time taken: ~ 40 hours



#include "Widget.h"
#include "Label.h"

class Button : public Widget
{
public:
	// Contructors --------------------------------------------------------------------------------
	Button() {};
	Button(sf::Texture const & t_texture, float t_width, float t_height);
	Button(sf::Color & t_color, float t_width, float t_height);
	~Button();

	// Virtual overrides --------------------------------------------------------------------------

	// Main actions ------------------
	void update(sf::Time t_deltaTime) override;
	void render(sf::RenderWindow & t_window) override;
	void highlighted(sf::Time t_deltaTime) override;
	void notHightlighted() override;

	// Actions ------------------------
	std::string *action() override;
	void setActionString(std::string t_actionString) override;		// Buttons action task

	// Getters -------------------------
	Widget * getUp() override;
	Widget * getDown() override;
	Widget * getRight() override;
	Widget * getLeft() override;
	sf::Vector2f getPosition() override;
	float getPositionY() override;				// For slider
	GUItype getWidgetType() override;			// E.g Buttom, Radio, Check
	bool getIfFilled() override;				// If switch
	std::string getActionString();
	float getRotation() override;
	std::string getText() override;

	// Setters -------------------------------------------------------------------------------------
	void setButtonAsSwitch();
	void setButtonAsFaded() override;
	void setButtonAsNormal() override;
	void setButtonAsTransparent() override;
	void setAsStarter() override;

	// Button's Text
	void setString(std::string  t_message, float t_size) override;
	void setTextOutline(sf::Color t_colour, float t_size);
	void setFont(sf::Font & t_font);
	void setTextColor(sf::Color t_textColor);

	// Setting Button attributes ------------------------------------
	void setFillcolor(sf::Color t_color);
	void setUnfilledColor(sf::Color t_color);
	void setOutline(sf::Color t_color, float t_thickness);
	void setPosition(float t_width, float t_height, PositionSetState t_settingStyle);
	void setPosition(sf::Vector2f t_pos) override;
	void setRotation(float t_rotation) override;
	void setOrigin(float t_x, float t_y);
	void resetOrigin();
	// Setting button direction -------------------------------------
	void setUp(Widget * t_upWidget);
	void setDown(Widget * t_downWidget);
	void setRight(Widget * t_rightWidget);
	void setLeft(Widget * t_leftWidget);

	// Setting animation conditions ---------------------------------
	void setAnimationStyle(buttonAnimationStyle t_anime) override;
	void setFlashSpeed(float t_flashSpeed);
	void setTextureAnimation(sf::IntRect & t_intRec, float t_speed, int numOfTextures);
	void setSwitchColorsColor(sf::Color t_filled, sf::Color t_unFilled);
	void setFlashColor(sf::Color t_flashColor);
	void setHightlightColor(sf::Color t_highlight, sf::Color t_textColor);
	void setHighLightSpeed(float t_speed);

	// Swtich State ------------------------------------------------------------------------------
	void addPartnerB(Button* t_radioButton);
	void swapState();
	void setSwitchFilled();
	void runTextureAnimation(sf::Time t_deltaTime);

	// Animations----------------------------
	void doHightLighting();
	void doHighLighted();
	void doUnHightLighing();
	void doUnhighLighted();

	void doFlash();
	void doShrink();

	// new
	bool checkCollision(sf::Vector3f t_position) override;
	std::string getButtonTag() override;
	void setButtonTag(std::string st);
	void setIndex(int index) override;
	int getIndex() override;
	void setInputType(InputType inp);
	void move(float x, float y) override;
	bool getCollided();
private:
	// Other GUI -------------------------
	Label m_buttonText;

	// Switch state ----------------------------
	std::vector<Button*> m_otherButtonsInSet;

	// Pointer to adjacent buttons
	Widget *m_up{ nullptr };
	Widget *m_Down{ nullptr };
	Widget *m_right{ nullptr };
	Widget *m_left{ nullptr };

	// SFML --------------------------------------
	sf::RectangleShape m_buttonBox;
	sf::Texture m_texture;				
	sf::IntRect m_currentTextureRect;
	sf::Sprite m_sprite;
	sf::Color m_filledColor;
	sf::Color m_unFilledColor;
	sf::Color m_flashColor;
	sf::Color m_highlightColor;
	sf::Color m_outlineColor;
	sf::Color m_textColor;
	sf::Color m_highlightTextColor;
	sf::Font m_font;

	std::string m_actionString = "";

	bool isInFocus{ false };
	bool m_isFilled{ false };
	int m_numOfJumps;
	int m_currentTextureNum{ 1 };
	int m_textIntJump;
	int m_originalTextSize;
	int m_highLightSpeed{ 5 };
	float m_textureSpeed;
	float m_buttonWidth{ 100 };
	float m_buttonHeight{ 30 };
	float m_animationCounter{ 0 };
	float m_textureCounter{ 0 };
	float m_flashSpeed{ 0.3f };
	float m_direction{ 1 };

	bool collide{ false };
	sf::Vector2f m_currentShrinkSize;
	sf::Vector2f m_originalShrinkSize;
	std::string m_buttonTag;
	int index;
	// Enum states----------------------------------------

	InputType m_input = InputType::controller;
	GUItype m_widgetType = GUItype::Button;
	buttonStyle m_buttonStyle = buttonStyle::NORMAL;
	buttonVisual m_type = buttonVisual::RECTANGLE;
	buttonAnimationStyle m_animationStyle = buttonAnimationStyle::FLASH;
	highLightState m_currentHightlight = highLightState::NotHighlighted;
};

