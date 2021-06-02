#include "LevelEditor.h"
#include "Game.h"

LevelEditor::LevelEditor(ResourceManager& t_gameAssets) :
	Xaxis{ sf::Lines },
	Yaxis{ sf::Lines },
	m_selector{ t_gameAssets },
	gameAssets{ &t_gameAssets }
{
	//initialize();
}


void LevelEditor::update(sf::Time t_deltaTime, MyVector3 mouseClick, int mouseScroll, bool pressed, bool rightPressed, sf::RenderWindow& t_window)
{
	float screenLimit = SCREEN_WIDTH - m_viewValueScale;
	// Updating counters ===========================================
	m_clickTimer += t_deltaTime.asSeconds();
	zoomcount += t_deltaTime.asSeconds();
	rotCount += t_deltaTime.asSeconds();
	m_saveTimer += t_deltaTime.asSeconds();
	m_timeManager += t_deltaTime.asSeconds();
	m_enemyPlaceTimer += t_deltaTime.asSeconds();
	keyPlaceTimer += t_deltaTime.asSeconds();

	checkZoom();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::U))
	{
		Game::m_gameMode = GameMode::Winning;
		Game::m_saving = true;
		Game::m_screenView = sf::View(sf::FloatRect(0, 0, 1920, 1280));
		Game::m_screenView.setCenter(960, 640);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
	{
		Game::m_gameMode = GameMode::Winning;
		Game::m_loading = true;
		Game::m_screenView = sf::View(sf::FloatRect(0, 0, 1920, 1280));
		Game::m_screenView.setCenter(960, 640);
	}
	// 1564
	if (mouseClick.x < screenLimit)		// Over editing area
	{
		doEditingArea(pressed, t_window, mouseClick, rightPressed);
	}
	else if (mouseClick.x > (screenLimit) && (mouseClick.y < 896 || zoomOut == true))
	{
		m_selector.update(t_deltaTime, mouseClick, mouseScroll, pressed);
		doSelectingArea(t_window, mouseClick, pressed);
	}
	else
	{
		overGrid = false;
		if (pressed == true && m_timeManager > 0.2f)
		{
			m_timeManager = 0;
			std::string st = m_EditorGUI.findSelected(t_window.mapPixelToCoords(mouseClick)).first;
			optionController(st);
		}
	}

	m_currentSprite.setPosition(t_window.mapPixelToCoords(mouseClick));
	if (zoomOut == false)
	{
		m_EditorGUI.update(t_deltaTime, mouseClick);
		m_selector.setPosition(sf::Vector2f(Game::m_screenView.getCenter().x + 576, Game::m_screenView.getCenter().y - 640));
	}
	changeScreen();
	saveAndLoad();
	
}

void LevelEditor::render(sf::RenderWindow& t_window)
{
	t_window.clear(sf::Color::White);
	Xaxis.clear();
	Yaxis.clear();


	for (int i = 0; i < m_bottomLayer.size(); i++)
	{
		t_window.draw(*(m_bottomLayer.at(i)->getSprite()));
	}
	for (int i = 0; i < m_level.size(); i++)
	{
		t_window.draw(*(m_level.at(i)->getSprite()));
	}
	for (int i = 0; i < 60; i++)
	{
		gridYaxisStart.position = MyVector3(i * 64.0f, 0, 0);
		gridYaxisEnd.position = MyVector3(i * 64.0f, 4000, 0);
		gridXaxisStart.position = MyVector3(0, i * 64.0f, 0);
		gridXaxisEnd.position = MyVector3(4000, i * 64.0f, 0);
		Xaxis.append(gridXaxisStart);
		Xaxis.append(gridXaxisEnd);
		Yaxis.append(gridYaxisStart);
		Yaxis.append(gridYaxisEnd);

		t_window.draw(Xaxis);
		t_window.draw(Yaxis);
	}
	m_selector.render(t_window);
	if (zoomOut == false)
	{
		m_EditorGUI.render(t_window);
	}
	if (overGrid == true && erase != true && m_reentry == false && placeRoute == false)
	{
		t_window.draw(m_currentSprite);
	}
}

void LevelEditor::initialize()
{
	gridYaxisStart.position = MyVector3(50, 0, 0);
	gridYaxisEnd.position = MyVector3(50, 800, 0);
	gridXaxisStart.position = MyVector3(0, 50, 0);
	gridXaxisEnd.position = MyVector3(800, 50, 0);

	gridYaxisStart.color = sf::Color(0, 0, 0, 255); // Black
	gridYaxisEnd.color = sf::Color(0, 0, 0, 255);
	gridXaxisStart.color = sf::Color(0, 0, 0, 255);
	gridXaxisEnd.color = sf::Color(0, 0, 0, 255);

	m_lastclickPos = sf::Vector2f(0, 0);
	m_clickTimer = 0;
	doorPlace = false;
	m_enemyPlaceTimer = 0;
	m_currentTextureTag = "Test0";
	currentTileIndex = 0;
	m_currentSprite.setTexture(gameAssets->m_gameTextures[m_currentTextureTag]);
	m_currentSprite.setOrigin(32, 32);
	m_font.loadFromFile("digital-7.ttf");
	sf::Color b = sf::Color::White;
	Button* button1 = new Button(b, 128, 128);
	button1->setString("Save", 40);
	button1->setTextColor(sf::Color(sf::Color::Blue));
	button1->setOutline(sf::Color::Blue, 2);
	button1->setButtonTag("Save");
	button1->setFont(m_font);
	button1->setPosition(sf::Vector2f(1536, 1152));
	widPosArray.push_back(sf::Vector2f(1536, 1152));
	button1->setRotation(0);
	button1->setInputType(InputType::mouse);
	//button1->setHighLightSpeed(10);
	//button1->setFlashColor(sf::Color::Green);
	button1->setAsStarter();
	m_EditorGUI.addWidget(button1);
	m_EditorGUI.setStartFocus(button1);

	Button* button2 = new Button(b, 128, 128);
	button2->setString("Load", 40);
	button2->setTextColor(sf::Color(sf::Color::Blue));
	button2->setOutline(sf::Color::Blue, 2);
	button2->setButtonTag("Load");
	button2->setFont(m_font);
	button2->setPosition(sf::Vector2f(1664, 1152));
	widPosArray.push_back(sf::Vector2f(1664, 1152));
	button2->setRotation(0);
	button2->setInputType(InputType::mouse);
	m_EditorGUI.addWidget(button2);

	Button* button6 = new Button(b, 128, 128);
	button6->setString("Exit", 40);
	button6->setTextColor(sf::Color(sf::Color::Blue));
	button6->setOutline(sf::Color::Blue, 2);
	button6->setButtonTag("Exit");
	button6->setFont(m_font);
	button6->setPosition(sf::Vector2f(1792, 1152));
	widPosArray.push_back(sf::Vector2f(1792, 1152));
	button6->setRotation(0);
	button6->setInputType(InputType::mouse);
	m_EditorGUI.addWidget(button6);

	Button* button7 = new Button(b, 384, 128);
	button7->setString("Erase", 40);
	button7->setTextColor(sf::Color(sf::Color::Blue));
	button7->setOutline(sf::Color::Blue, 2);
	button7->setButtonTag("Erase");
	button7->setFont(m_font);
	button7->setPosition(sf::Vector2f(1536, 1024));
	widPosArray.push_back(sf::Vector2f(1536, 1024));
	button7->setRotation(0);
	button7->setInputType(InputType::mouse);
	button7->setButtonAsSwitch();
	button7->setFillcolor(sf::Color::Blue);
	button7->setUnfilledColor(sf::Color::White);
	button7->setInputType(InputType::mouse);
	m_EditorGUI.addWidget(button7);

	Button* button3 = new Button(b, 128, 128);
	button3->setString("Back", 30);
	button3->setTextColor(sf::Color(sf::Color::Blue));
	button3->setOutline(sf::Color::Blue, 2);
	button3->setButtonTag("Back");
	button3->setActionString("Act");
	button3->setFont(m_font);
	button3->setPosition(sf::Vector2f(1536, 896));
	widPosArray.push_back(sf::Vector2f(1536, 896));
	button3->setRotation(0);
	button3->setInputType(InputType::mouse);
	button3->setButtonAsSwitch();
	button3->setFillcolor(sf::Color::Blue);
	button3->setUnfilledColor(sf::Color::White);
	m_EditorGUI.addWidget(button3);

	Button* button4 = new Button(b, 128, 128);
	button4->setString("Middle", 30);
	button4->setTextColor(sf::Color(sf::Color::Blue));
	button4->setOutline(sf::Color::Blue, 2);
	button4->setButtonTag("Middle");
	button4->setActionString("Act");
	button4->setFont(m_font);
	button4->setPosition(sf::Vector2f(1664, 896));
	widPosArray.push_back(sf::Vector2f(1664, 896));
	button4->setRotation(0);
	button4->setButtonAsSwitch();
	button4->setFillcolor(sf::Color::Blue);
	button4->setUnfilledColor(sf::Color::White);
	button4->setInputType(InputType::mouse);
	m_EditorGUI.addWidget(button4);

	Button* button5 = new Button(b, 128, 128);
	button5->setString("Front", 30);
	button5->setTextColor(sf::Color(sf::Color::Blue));
	button5->setOutline(sf::Color::Blue, 2);
	button5->setButtonTag("Front");
	button5->setActionString("Act");
	button5->setFont(m_font);
	button5->setPosition(sf::Vector2f(1792, 896));
	widPosArray.push_back(sf::Vector2f(1792, 896));
	button5->setRotation(0);
	button5->setButtonAsSwitch();
	button5->setFillcolor(sf::Color::Blue);
	button5->setUnfilledColor(sf::Color::White);
	button5->setInputType(InputType::mouse);
	m_EditorGUI.addWidget(button5);

	button3->addPartnerB(button4);
	button3->addPartnerB(button5);
	button4->addPartnerB(button3);
	button4->addPartnerB(button5);
	button5->addPartnerB(button4);
	button5->addPartnerB(button3);
	button4->setSwitchFilled();


	m_EditorGUI.setInput(InputType::mouse);
	m_EditorGUI.setAnimationStyle(buttonAnimationStyle::FLASH);
}


LevelEditor::~LevelEditor()
{
	for (int i = 0; i < m_level.size(); i++)
	{
		delete m_level.at(i);
	}
	m_level.clear();
	for (int i = 0; i < m_bottomLayer.size(); i++)
	{
		delete m_bottomLayer.at(i);
	}
	m_bottomLayer.clear();
}

bool compareValue(const Tile* lhs, const Tile* rhs)
{
	if (lhs->position.y == rhs->position.y)
	{
		return lhs->position.x < rhs->position.x;
	}
	else
	{
		return lhs->position.y < rhs->position.y;
	}
}

void LevelEditor::saveLevel()
{
	if (m_level.size() > 0)
	{
		//std::sort(m_level.begin(), m_level.end(), compareValue);
		if (m_savedLevelNames.size() < 10)
		{
			std::fstream filestr;
			std::string stg = m_saveName + ".txt";
			filestr.open(stg, std::fstream::in | std::fstream::out | std::fstream::app);
			stg.clear();
			if (filestr.fail())
			{
				std::cout << "Error" << std::endl;
			}
			for (int i = 0; i < m_bottomLayer.size(); i++)
			{
				filestr << m_bottomLayer.at(i)->getIndex() << " " << m_bottomLayer.at(i)->getPosition().x << " "
					<< m_bottomLayer.at(i)->getPosition().y << " " << 0;
				filestr << std::endl;
			}
			for (int i = 0; i < m_level.size(); i++)
			{
				if (m_level.at(i)->getIndex() != 6)
				{
					filestr << m_level.at(i)->getIndex() << " " << m_level.at(i)->getPosition().x << " "
						<< m_level.at(i)->getPosition().y << " " << 1;
					filestr << std::endl;
				}
			}
			filestr.close();

			std::string stg2 = m_saveName + "E.txt";
			filestr.open(stg2, std::fstream::in | std::fstream::out | std::fstream::app);
			for (int i = 0; i < m_level.size(); i++)
			{
				if (m_level.at(i)->getIndex() == 6)
				{
					filestr << m_level.at(i)->getIndex() << " " << m_level.at(i)->getPosition().x << " " << m_level.at(i)->getPosition().y << " ";
					for (int j = 0; j < m_level.at(i)->m_enemyPositionList.size(); j++)
					{
						filestr << m_level.at(i)->m_enemyPositionList.at(j).x << " " << m_level.at(i)->m_enemyPositionList.at(j).y << " ";
					}
					filestr << std::endl;
				}
			}
			filestr.close();
			filestr.open("SavedLevels.txt", std::fstream::in | std::fstream::out | std::fstream::app);
			if (filestr.fail())
			{
				std::cout << "Error" << std::endl;
			}

			filestr << m_saveName;
			filestr << std::endl;
			filestr.close();
		}
		else
		{
			// Delete Process
		}
	}
}

void LevelEditor::loadLevel()
{
	for (int i = 0; i < m_level.size(); i++)
	{
		delete m_level.at(i);
	}
	m_level.clear();
	for (int i = 0; i < m_bottomLayer.size(); i++)
	{
		delete m_bottomLayer.at(i);
	}
	m_bottomLayer.clear();

	// Reads in from fill in Form (Name, score)
	int index, xPos, yPos, rotation;
	int layer{ 0 };
	std::string line;
	std::string st;
	std::string stg = m_loadName + ".txt";
	std::ifstream file(stg);
	// Read in names and scores from file
	if (file.is_open())
	{
		while (file >> index >> xPos >> yPos >> layer)
		{
			if (layer == 0)
			{
				st = "Test" + std::to_string(index);
				std::cout << st << std::endl;
				Tile* sp = new Tile(*gameAssets, st, index, 0);
				sp->setPosition(sf::Vector2f(xPos, yPos));
				m_bottomLayer.push_back(sp);

			}
			else if (layer == 1)
			{
				st = "Test" + std::to_string(index);
				std::cout << st << std::endl;
				Tile* sp = new Tile(*gameAssets, st, index, 0);
				sp->setPosition(sf::Vector2f(xPos, yPos));
				m_level.push_back(sp);
			}
		}
	}
	file.close();
	std::cout << m_level.size() << std::endl;
}

void LevelEditor::checkZoom()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::T) && zoomcount > 2)
	{
		zoomcount = 0;
		if (zoomOut == true)
		{
			zoomOut = false;
			m_viewValueScale = 384;
			Game::m_screenView = sf::View(sf::FloatRect(0, 0, 1920, 1260));
			Game::m_screenView.setCenter(lastCentre);
			m_selector.setLength(1260);
			m_diffFromStartCamera = Game::m_screenView.getCenter() - m_cameraStartPos;
			std::vector<sf::Vector2f> temp;
			for (auto& goop : widPosArray)
			{
				temp.push_back(goop + m_diffFromStartCamera);
			}
			m_selector.updateWids(m_diffFromStartCamera);
		}
		else
		{
			zoomOut = true;
			m_viewValueScale = 182;
			lastCentre = Game::m_screenView.getCenter();
			Game::m_screenView = sf::View(sf::FloatRect(0, 0, 4000, 2820));
			m_selector.setPosition(MyVector3(3778, 0, 0));
			m_selector.updateWids(sf::Vector2f(2246, 0));
			m_selector.setLength(2560);
			Game::m_screenView.setCenter(zoomCentre);
		}
	}
}

void LevelEditor::backgroundUpdate(MyVector3 mouseClick, int nx, int ny)
{

	int vecSize = m_bottomLayer.size();
	std::vector<Tile*>::iterator it = m_bottomLayer.begin();
	std::vector<Tile*>::iterator end = m_bottomLayer.end();
	for (; it != end; it++)
	{
		if ((nx == (*it)->getPosition().x / 64) && (ny == (*it)->getPosition().y / 64))
		{
			delete (*it);			// Delete it off the heap
			m_bottomLayer.erase(it);		// Remove it from the array
			break;					// Iterator will be broken and also avoids wasted time, might swap this data structure to a list, to save looping time
		}
	}
	if (erase == false)
	{
		Tile* sp = new Tile(*gameAssets, m_currentTextureTag, currentTileIndex, rotDirection);
		sp->setPosition(sf::Vector2f(nx * 64, ny * 64));
		m_bottomLayer.push_back(sp);
		m_lastclickPos = mouseClick;
	}
	std::cout << m_bottomLayer.size() << std::endl;
}

void LevelEditor::playUpdate(MyVector3 mouseClick, int nx, int ny)
{
	if (placeRoute == false && doorPlace == false)
	{
		int vecSize = m_level.size();
		std::vector<Tile*>::iterator it = m_level.begin();
		std::vector<Tile*>::iterator end = m_level.end();
		for (; it != end; it++)
		{
			if ((nx == (*it)->getPosition().x / 64) && (ny == (*it)->getPosition().y / 64))
			{
				delete (*it);			// Delete it off the heap
				m_level.erase(it);		// Remove it from the array
				break;					// Iterator will be broken and also avoids wasted time, might swap this data structure to a list, to save looping time
			}
		}
		if (erase == false)
		{
			Tile* sp = new Tile(*gameAssets, m_currentTextureTag, currentTileIndex, rotDirection);
			sp->setPosition(sf::Vector2f(nx * 64, ny * 64));
			m_level.push_back(sp);
			m_lastclickPos = mouseClick;
			if (currentTileIndex == 6)		// Enemy
			{
				m_enemyPlaceTimer = 0;
				placeRoute = true;
				currentInUseEnemy = sp;
				currentRouteCount = 0;
			}
			else if (currentTileIndex == 4) // Door
			{
				m_currentSprite.setTexture(gameAssets->m_gameTextures["Test20"]);
				m_currentTextureTag = "Test20";
				currentTileIndex = 20;
				keyPlaceTimer = 0;
				doorPlace = true;
			}
		}
		std::cout << m_level.size() << std::endl;
	}
	else if(placeRoute == true)
	{
		/*bool exist = false;
		for (int i = 0; i < currentInUseEnemy->m_enemyPositionList.size(); i++)
		{
			if (currentInUseEnemy->m_enemyPositionList.at(i) == sf::Vector2f(nx * 64, ny * 64))
			{
				exist = true;
				break;
			}
		}*/
		if (m_enemyPlaceTimer > 0.5f)
		{
			m_clickTimer = 0;
			m_enemyPlaceTimer = 0;
			currentInUseEnemy->m_enemyPositionList.push_back(sf::Vector2f(nx * 64, ny * 64));
			currentRouteCount++;
			if (currentRouteCount >= 3)
			{
				placeRoute = false;
			}
		}
	}
	else if (doorPlace == true && keyPlaceTimer > 0.5f)
	{
		int vecSize = m_level.size();
		std::vector<Tile*>::iterator it = m_level.begin();
		std::vector<Tile*>::iterator end = m_level.end();
		for (; it != end; it++)
		{
			if ((nx == (*it)->getPosition().x / 64) && (ny == (*it)->getPosition().y / 64))
			{
				delete (*it);			// Delete it off the heap
				m_level.erase(it);		// Remove it from the array
				break;					// Iterator will be broken and also avoids wasted time, might swap this data structure to a list, to save looping time
			}
		}
		Tile* sp = new Tile(*gameAssets, m_currentTextureTag, currentTileIndex, rotDirection);
		sp->setPosition(sf::Vector2f(nx * 64, ny * 64));
		m_level.push_back(sp);
		m_lastclickPos = mouseClick;	
		doorPlace = false;
		m_currentSprite.setTexture(gameAssets->m_gameTextures["Test4"]);
		m_currentTextureTag = "Test4";
		currentTileIndex = 4;
	}
}

void LevelEditor::rightClickScroll(MyVector3 mouseClick)
{
	//// Move camera centre
		//// Checks for boundaries

	if (m_reentry == false)
	{
		m_startPanPos = mouseClick;
		m_reentry = true;
	}

	MyVector3 distanceFromPan = mouseClick - m_startPanPos;
	float power = distanceFromPan.length();
	if (power > 300)
	{
		power = 300;
	}
	distanceFromPan.normalise();
	sf::Vector2f dist = -distanceFromPan;
	Game::m_screenView.setCenter(Game::m_screenView.getCenter() + dist * (power / 10));



	bool checkU = false;
	bool checkS = false;
	if (Game::m_screenView.getCenter().x < 960)
	{
		Game::m_screenView.setCenter(960, Game::m_screenView.getCenter().y);
		checkS = true;
	}
	else if (Game::m_screenView.getCenter().x > 3200)
	{
		Game::m_screenView.setCenter(3200, Game::m_screenView.getCenter().y);
		checkS = true;
	}

	if (Game::m_screenView.getCenter().y < 640)
	{
		Game::m_screenView.setCenter(Game::m_screenView.getCenter().x, 640);
		checkU = true;
	}
	else if (Game::m_screenView.getCenter().y > 1920)
	{
		Game::m_screenView.setCenter(Game::m_screenView.getCenter().x, 1920);
		checkU = true;
	}

	MyVector3 oop = dist * (power / 10);
	if (checkU == false && checkS == false)
	{
		m_selector.moveWidgets(oop);
		//	m_EditorGUI.movewidgets(oop.x, oop.y);
	}
	else if (checkU == false && checkS == true)
	{
		m_selector.moveWidgets(sf::Vector2f(0, oop.y));
		//	m_EditorGUI.movewidgets(0, oop.y);
	}
	else if (checkS == false && checkU == true)
	{
		m_selector.moveWidgets(sf::Vector2f(oop.x, 0));
		//	m_EditorGUI.movewidgets(oop.x, 0);
	}
	m_diffFromStartCamera = Game::m_screenView.getCenter() - m_cameraStartPos;
	std::vector<sf::Vector2f> temp;
	for (auto& goop : widPosArray)
	{
		temp.push_back(goop + m_diffFromStartCamera);
	}
	m_selector.updateWids(m_diffFromStartCamera);
	m_EditorGUI.setWidgetPositons(temp);
}

void LevelEditor::optionController(std::string st)
{
	if (st == "Save" && Game::m_screenChangeTimer < 0)
	{
		Game::m_gameMode = GameMode::Winning;
		Game::m_saving = true;
		Game::m_screenView = sf::View(sf::FloatRect(0, 0, 1920, 1280));
		Game::m_screenView.setCenter(960, 640);
		Game::m_screenChangeTimer = 0.5f;
	}
	if (st == "Load" && Game::m_screenChangeTimer < 0)
	{
		Game::m_gameMode = GameMode::Winning;
		Game::m_loading = true;
		Game::m_screenView = sf::View(sf::FloatRect(0, 0, 1920, 1280));
		Game::m_screenView.setCenter(960, 640);
		Game::m_screenChangeTimer = 0.5f;
	}
	if (st == "Erase")
	{
		if (erase == true)
		{
			erase = false;
		}
		else
		{
			erase = true;
		}
	}
	if (st == "Exit" )
	{
		Game::m_screenChangeTimer = 0.5f;
		Game::m_gameMode = GameMode::MainMenu;
		for (int i = 0; i < m_level.size(); i++)
		{
			delete m_level.at(i);
		}
		m_level.clear();
		for (int i = 0; i < m_bottomLayer.size(); i++)
		{
			delete m_bottomLayer.at(i);
		}
		m_bottomLayer.clear();
		Game::m_screenView = sf::View(sf::FloatRect(0, 0, 1920, 1280));
		Game::m_screenView.setCenter(960, 640);
		m_clickTimer = 0;
		m_diffFromStartCamera = Game::m_screenView.getCenter() - m_cameraStartPos;
		std::vector<sf::Vector2f> temp;
		for (auto& goop : widPosArray)
		{
			temp.push_back(goop + m_diffFromStartCamera);
		}
		m_selector.updateWids(m_diffFromStartCamera);
		m_EditorGUI.setWidgetPositons(temp);
		initialize();
	}
	if (st == "Back")
	{
		m_currentLayer = Layer::background;
	}
	if (st == "Middle")
	{
		m_currentLayer = Layer::play;
	}
	
}

void LevelEditor::saveAndLoad()
{

	// Save -------------------------------------------------
	m_saveName = Game::m_currentSaveName;
	if (saveBool == true && (m_saveName != m_oldSaveName))
	{
		m_oldSaveName = m_saveName;
		saveLevel();
		saveBool = false;
		m_saveTimer = 0;
	}
	if (m_saveTimer > 5)
	{
		saveBool = true;
	}

	// -------------------------------------------------------

	// Load --------------------------------------------------
	m_loadName = Game::m_currentLoadName;
	if (m_oldLoadName != m_loadName)
	{
		m_oldLoadName = m_loadName;
		loadLevel();
	}
	// ------------------------------------------------------
}

void LevelEditor::changeScreen()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::B) && Game::m_screenChangeTimer < 0)
	{
		Game::m_screenChangeTimer = 0.5f;
		Game::m_gameMode = GameMode::MainMenu;
		for (int i = 0; i < m_level.size(); i++)
		{
			delete m_level.at(i);
		}
		m_level.clear();
		for (int i = 0; i < m_bottomLayer.size(); i++)
		{
			delete m_bottomLayer.at(i);
		}
		m_bottomLayer.clear();
		Game::m_screenView = sf::View(sf::FloatRect(0, 0, 1920, 1280));
		Game::m_screenView.setCenter(955, 640);
		m_clickTimer = 0;
		m_diffFromStartCamera = Game::m_screenView.getCenter() - m_cameraStartPos;
		std::vector<sf::Vector2f> temp;
		for (auto& goop : widPosArray)
		{
			temp.push_back(goop + m_diffFromStartCamera);
		}
		m_selector.updateWids(m_diffFromStartCamera);
		m_EditorGUI.setWidgetPositons(temp);
	}
}

void LevelEditor::doEditingArea(bool pressed, sf::RenderWindow& t_window, MyVector3 mouseClick, bool rightPressed)
{
	overGrid = true;
	if (pressed == true && m_currentTextureTag != "NAN" && m_clickTimer > 0.25 && mouseClick != m_lastclickPos)
	{
		int nx = t_window.mapPixelToCoords(mouseClick).x / 64;
		int ny = t_window.mapPixelToCoords(mouseClick).y / 64;

		if (m_currentLayer == Layer::background)
		{
			backgroundUpdate(mouseClick, nx, ny);
		}
		else if (m_currentLayer == Layer::play)
		{
			playUpdate(mouseClick, nx, ny);
		}
	}
	if (rightPressed == true && zoomOut == false)
	{
		rightClickScroll(mouseClick);
	}
	else
	{
		m_reentry = false;
		m_startPanPos = mouseClick;
	}
}

void LevelEditor::doSelectingArea(sf::RenderWindow& t_window, MyVector3 mouseClick, bool pressed)
{
	overGrid = false;
	if (placeRoute == false && doorPlace == false)
	{
		if (pressed == true && m_timeManager > 0.2f)
		{
			if (m_selector.selectTile(t_window.mapPixelToCoords(mouseClick)).first != "NAN")
			{
				m_timeManager = 0;
				std::pair<std::string, int> tileData;
				tileData = m_selector.selectTile(t_window.mapPixelToCoords(mouseClick));
				m_currentTextureTag = tileData.first;
				currentTileIndex = tileData.second;
			}
			if (m_currentTextureTag != "" && m_currentTextureTag != "NAN")
			{
				m_currentSprite.setTexture(gameAssets->m_gameTextures[m_currentTextureTag]);
			}
		}
	}
}

void LevelEditor::clearGUI()
{
}




// Move world code instead
//if (m_reentry == false)
//{
//	m_startPanPos = mouseClick;
//	m_reentry = true;
//}
//
//MyVector3 distanceFromPan = mouseClick - m_startPanPos;
//float power = distanceFromPan.length();
//if (power > 300)
//{
//	power = 300;
//}
//distanceFromPan.normalise();
//sf::Vector2f dist = -distanceFromPan;
//
//std::vector<Tile*>::iterator it = m_level.begin();
//std::vector<Tile*>::iterator end = m_level.end();
//for (; it != end; it++)
//{
//	(*it)->setPosition((*it)->getPosition() + dist);
//}
//
//std::vector<Tile*>::iterator it2 = m_bottomLayer.begin();
//std::vector<Tile*>::iterator end2 = m_bottomLayer.end();
//for (; it2 != end2; it2++)
//{
//	(*it2)->setPosition((*it2)->getPosition() + dist);
//}
