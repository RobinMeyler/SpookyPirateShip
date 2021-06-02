#include "Splash.h"
#include "Game.h"


Splash::Splash(ResourceManager& t_gameAssets)
{
	
}


Splash::~Splash()
{
}

void Splash::initialize()
{
	m_bckGrndTexture.loadFromFile("Assets/Images/boatwater.jpg");
	m_body.setTexture(m_bckGrndTexture);
	m_body.setPosition(0, 0);
	distortionMap.setRepeated(true);
	distortionMap.setSmooth(true);
	if (!distortionMap.loadFromFile("distortion_map.png"))
	{
		sf::err() << "Failed to load distortion map, exiting..." << std::endl;

	}
	renderTexture.create(14, 14);
	renderSprite.setTexture(renderTexture.getTexture());
	renderSprite.setPosition(100, 150);
	const char* vs_src = "#version 130\n"
		"void main()"
		"{"
		"	gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;"
		"gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;"
		"gl_FrontColor = gl_Color;"
		"}";


	std::string fragLine, textFrag;

	std::ifstream inFrag("water.txt");				// Spaceish

	while (std::getline(inFrag, fragLine))
	{
		textFrag += fragLine + "\n";
	}
	const char* dataFrag = textFrag.c_str();

	if (!shader1.loadFromMemory(vs_src, sf::Shader::Vertex))
	{
		// error...
	}

	// load only the fragment shader
	if (!shader1.loadFromMemory(dataFrag, sf::Shader::Fragment))
	{
		// error...
	}
	// set up GUI..
	//Label
	try {
		m_font.loadFromFile("BBrick.ttf");
	}
	catch (...) {

	}
	m_bckGrndTexture.loadFromFile("Assets/Images/boatwater.jpg");
	m_bckGrndSprite.setTexture(m_bckGrndTexture);

	sf::String labelString = "GHOST PIRATE SHIP";
	Label* splash = new Label(m_font);
	splash->setString(labelString);
	splash->setTextSize(120);
	splash->setPosition(sf::Vector2f{ 450, 150 });
	splash->setTextColor(sf::Color::Red);
	splash->setOutline(sf::Color::White, 2);
	splash->setUnderLined();


	sf::Color b = sf::Color::White;
	Button* button1 = new Button(b, 600, 100);
	button1->setString("Continue!", 40);
	button1->setTextColor(sf::Color(sf::Color::Black));
	button1->setButtonTag("continue");
	button1->setFont(m_font);
	button1->resetOrigin();
	button1->setPosition(sf::Vector2f(800, 900));
	button1->setRotation(0);
	button1->setOutline(sf::Color::Magenta, 2);

	button1->setInputType(InputType::mouse);
	button1->setHighLightSpeed(10);
	button1->setFlashColor(sf::Color::Green);


	m_GUI.addWidget(splash);
	m_GUI.addWidget(button1);
	m_GUI.setStartFocus(button1);
	button1->setAsStarter();
	m_GUI.setInput(InputType::mouse);
	m_GUI.setAnimationStyle(buttonAnimationStyle::FLASH);
}

void Splash::update(sf::Time t_deltaTime, MyVector3 mouseClick, bool pressed)
{
	m_mousePos = mouseClick;
	m_GUI.update(t_deltaTime, mouseClick);
	if (pressed == true)
	{
		std::string st = m_GUI.findSelected(mouseClick).first;
		if (st == "continue" && Game::m_screenChangeTimer < 0)
		{
			Game::m_screenChangeTimer = 0.5f;
			Game::m_gameMode = GameMode::MainMenu;
		}
	}
}

void Splash::render(sf::RenderWindow& t_window)
{
	shader1.setUniform("time", clock.getElapsedTime().asSeconds());
	//// For Haze 
	//shader1.setUniform("distortionFactor", distortionFactor);
	//shader1.setUniform("riseFactor", riseFactor);

	// For Lines
	sf::Vector2f res = { 1920, 1280 };
	shader1.setUniform("resolution", res);
	sf::Vector2f oop = t_window.mapPixelToCoords(m_mousePos);
	//shader1.setUniform("mouse", oop);

	//renderSprite.setPosition(m_testCar.getPosition() - sf::Vector2f{ 14,14 });
	renderTexture.clear();
	renderTexture.draw(m_body);
	renderTexture.display();


	//t_window.draw(m_bckGrndSprite);
	t_window.draw(m_body, &shader1);
	m_GUI.render(t_window);
}
