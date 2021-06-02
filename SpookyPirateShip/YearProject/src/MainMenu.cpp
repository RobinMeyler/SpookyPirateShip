#include "MainMenu.h"
#include "Game.h"


MainMenu::MainMenu(ResourceManager& t_gameAssets)
{				
	
}


MainMenu::~MainMenu()
{
}


void MainMenu::initialize()
{
	if (!clickSoundBuffer.loadFromFile("Assets/Audio/buttonSound.wav"))
	{
		std::cout << "ERROR, loading click sound (main menu)" << std::endl;
	}
	clickSound.setBuffer(clickSoundBuffer);

	m_bckGrndTexture.loadFromFile("Assets/Images/beach.jpg");
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

	std::ifstream inFrag("dataFragShader.txt");				// Spaceish

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

	/*m_bckGrndTexture.loadFromFile("Assets/Images/beach.jpg");
	m_bckGrndSprite.setTexture(m_bckGrndTexture);*/

	sf::String labelString = "GHOST PIRATE SHIP";
	Label* main = new Label(m_font);
	main->setString(labelString);
	main->setTextSize(120);
	main->setPosition(sf::Vector2f{ 350, 200 });
	main->setTextColor(sf::Color::Red);
	main->setOutline(sf::Color::White, 2);



	sf::Color b = sf::Color::White;
	Button* button1 = new Button(b, 1000, 100);
	button1->setString("Play", 40);
	button1->setTextColor(sf::Color(sf::Color::Blue));
	button1->setOutline(sf::Color::Blue, 2);
	button1->setButtonTag("Play");
	button1->setFont(m_font);
	button1->setPosition(sf::Vector2f(450, 600));
	button1->setRotation(0);
	button1->resetOrigin();
	button1->setInputType(InputType::mouse);
	button1->setHighLightSpeed(10);
	button1->setFlashColor(sf::Color::Green);


	Button* button2 = new Button(b, 1000, 100);
	button2->setString("Options", 40);
	button2->setTextColor(sf::Color(sf::Color::Blue));
	button2->setButtonTag("Options");
	button2->setFont(m_font);
	button2->setPosition(sf::Vector2f(450, 725));
	button2->setRotation(0);
	button2->setOutline(sf::Color::Blue, 2);
	button2->resetOrigin();
	button2->setInputType(InputType::mouse);
	button2->setHighLightSpeed(10);
	button2->setFlashColor(sf::Color::Green);

	Button* button3 = new Button(b, 1000, 100);
	button3->setString("Level Editor", 40);
	button3->setTextColor(sf::Color(sf::Color::Blue));
	button3->setButtonTag("Edit");
	button3->setFont(m_font);
	button3->setPosition(sf::Vector2f(450, 850));
	button3->setRotation(0);
	button3->setOutline(sf::Color::Blue, 2);
	button3->resetOrigin();
	button3->setInputType(InputType::mouse);
	button3->setHighLightSpeed(10);
	button3->setFlashColor(sf::Color::Green);

	Button* button4 = new Button(b, 1000, 100);
	button4->setString("Exit", 40);
	button4->setTextColor(sf::Color(sf::Color::Blue));
	button4->setButtonTag("Exit");
	button4->setFont(m_font);
	button4->setPosition(sf::Vector2f(450, 975));
	button4->setRotation(0);
	button4->setOutline(sf::Color::Blue, 2);
	button4->resetOrigin();
	button4->setInputType(InputType::mouse);
	button4->setHighLightSpeed(10);
	button4->setFlashColor(sf::Color::Green);

	m_GUI.addWidget(main);
	m_GUI.addWidget(button1);
	m_GUI.addWidget(button2);
	m_GUI.addWidget(button3);
	m_GUI.addWidget(button4);
	m_GUI.setStartFocus(button1);
	button1->setAsStarter();
	m_GUI.setInput(InputType::mouse);
	m_GUI.setAnimationStyle(buttonAnimationStyle::FLASH);

}

void MainMenu::update(sf::Time t_deltaTime, MyVector3 mouseClick, bool pressed)
{
	m_mousePos = mouseClick;
	m_GUI.update(t_deltaTime, mouseClick);
	if (pressed == true)
	{

		clickSound.play();

		std::string st = m_GUI.findSelected(mouseClick).first;
		if (st == "Play" && Game::m_screenChangeTimer < 0)
		{
			Game::m_resetPlay = true;
			Game::m_screenView = sf::View(sf::FloatRect(0,0, 800, 600));
			Game::m_gameMode = GameMode::Gameplay;
			Game::m_screenChangeTimer = 0.5f;
		}
		if (st == "Options" && Game::m_screenChangeTimer < 0)
		{
			Game::m_gameMode = GameMode::Options;
			Game::m_screenChangeTimer = 0.5f;
		}
		if (st == "Edit" && Game::m_screenChangeTimer < 0)
		{
			Game::m_gameMode = GameMode::LevelEditor;
			Game::m_screenChangeTimer = 0.5f;
		}
		if (st == "Exit" && Game::m_screenChangeTimer < 0)
		{
			Game::m_gameMode = GameMode::Licence;
			Game::m_screenChangeTimer = 0.5f;
		}
	}
}

void MainMenu::render(sf::RenderWindow& t_window)
{
	shader1.setUniform("time", clock.getElapsedTime().asSeconds()/4);
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


	t_window.draw(m_body, &shader1);
	m_GUI.render(t_window);
}