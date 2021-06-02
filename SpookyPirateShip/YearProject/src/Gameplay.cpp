#include "Gameplay.h"
#include "Game.h"



bool sortNodes(const Node* n1, const Node* n2)
{
	if (n1->m_data.m_position.y == n2->m_data.m_position.y)
	{
		return n1->m_data.m_position.x < n2->m_data.m_position.x;
	}
	else
	{
		return n1->m_data.m_position.y < n2->m_data.m_position.y;
	}
}


Gameplay::Gameplay(ResourceManager& t_gameAssets) :
	gameAssets{ &t_gameAssets },
	rock(t_gameAssets, MyVector3(84, 150, 0))
{
}

void Gameplay::reset()
{
	for (int i = 0; i < m_levelDoors.size(); i++)
	{
		delete m_levelDoors.at(i);
	}
	m_levelDoors.clear();
	for (int i = 0; i < m_levelKeys.size(); i++)
	{
		delete m_levelKeys.at(i);
	}
	m_levelKeys.clear();
}

Gameplay::~Gameplay()
{
	for (int i = 0; i < m_levelDoors.size(); i++)
	{
		delete m_levelDoors.at(i);
	}
	m_levelDoors.clear();
	for (int i = 0; i < m_levelKeys.size(); i++)
	{
		delete m_levelKeys.at(i);
	}
	m_levelKeys.clear();
}

void Gameplay::update(sf::Time t_deltaTime, MyVector3 mouseClick, bool pressed, sf::RenderWindow& t_window)
{
	if (Game::m_resetPlay == true)
	{
		Game::m_resetPlay = false;
		reset();
		initialize();
	}


	//m_enemyOne.checkPlayerInFOV(m_player.getPosition());
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
	{
		debug = !debug;
	}





	rockCheck(rock, pressed, t_deltaTime, t_window, mouseClick);

	for (int i = 0; i < m_levelDoors.size(); i++)
	{
		m_levelDoors.at(i)->update(t_deltaTime, &m_player);
	}

	bool doorCol = false;
	for (int i = 0; i < m_levelDoors.size(); i++)
	{
		doorCol = Collider::collisionPosSize(

			m_player.getPosition() + sf::Vector2f(10, 35),
			sf::Vector2f(45, 35),
			m_levelDoors.at(i)->getPosition() + sf::Vector2f(0, 0),
			sf::Vector2f(64, 64)
		);
		if (doorCol == true)
		{
			m_player.stepBack();
			break;
		}
	}

	bool keyCol = false;
	for (int i = 0; i < m_levelKeys.size(); i++)
	{
		keyCol = Collider::collisionPosSize(

			m_player.getPosition() + sf::Vector2f(10, 35),
			sf::Vector2f(45, 35),
			m_levelKeys.at(i)->getPosition() + sf::Vector2f(0, 0),
			sf::Vector2f(64, 64)
		);
		if (keyCol == true)
		{
			m_levelKeys.at(i)->setHeld(true);
			std::vector<Key*> playerQauys = m_player.heldKeys();
			bool alreadyhas = false;
			for (int j = 0; j < playerQauys.size(); j++)
			{
				if (playerQauys.at(j) == m_levelKeys.at(i))
				{
					alreadyhas = true;
				}
			}
			if (alreadyhas == false)
			{
				m_player.addKey(m_levelKeys.at(i));
			}
		}
	}

	//Game::m_screenView = t_window.getDefaultView();


	m_player.update();
	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies.at(i).update(t_deltaTime);
	}
	/*if (m_enemies.size() > 0)
	{
		for (Enemy e : m_enemies)
		{
			e.update(t_deltaTime);
		}
	}*/


	// Camera Logic ======================================================================
	float xPos;
	float yPos;
	if (m_player.m_state.getCurrent()->getSprite().getPosition().x < 400)
	{
		xPos = 400;
	}
	else if (m_player.m_state.getCurrent()->getSprite().getPosition().x > 4000)	// Get rid of these hardcoded values
	{
		xPos = 4000;
	}
	else
	{
		xPos = m_player.m_state.getCurrent()->getSprite().getPosition().x;
	}

	if (m_player.m_state.getCurrent()->getSprite().getPosition().y < 300)
	{
		yPos = 300;
	}
	else if (m_player.m_state.getCurrent()->getSprite().getPosition().y > 3000)
	{
		yPos = 3000;
	}
	else
	{
		yPos = m_player.m_state.getCurrent()->getSprite().getPosition().y;
	}
	Game::m_screenView.setCenter(sf::Vector2f(xPos, yPos));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::V))
	{
		Game::m_gameMode = GameMode::MainMenu;
		Game::m_screenView = sf::View(sf::FloatRect(0, 0, 1920, 1280));
		Game::m_screenView.setCenter(955, 640);
	}
	// (Reset camera before leaving screen)
	// ======================================================================================

	//circlesUpdate(m_enemyOne.getPath());

	for (int i = 0; i < m_levelDoors.size(); i++)
	{
		if (m_levelDoors.at(i)->isActive() == false)
		{
			std::vector<Door*>::iterator it = m_levelDoors.begin();
			std::vector<Key*>::iterator itK = m_levelKeys.begin();
			std::vector<Door*>::iterator end = m_levelDoors.end();

			for (; it != end; it++, itK++)
			{
				if ((*it) == m_levelDoors.at(i))
				{
					delete (*it);
					m_levelDoors.erase(it);
					delete (*itK);
					m_levelKeys.erase(itK);
					break;
				}
			}
		}
	}
	bool endCol = false;
	endCol = Collider::collisionPosSize(

		m_player.getPosition(),
		sf::Vector2f(45, 35),
		end.getPosition() + sf::Vector2f(0, 0),
		sf::Vector2f(100, 100)
	);
	if (endCol == true)
	{
		Game::m_gameMode = GameMode::Winning;
		Game::m_win = true;
		Game::m_screenView = sf::View(sf::FloatRect(0, 0, 1920, 1280));
		Game::m_screenView.setCenter(955, 640);
		Game::m_screenChangeTimer = 0.5f;
	}

}

void Gameplay::render(sf::RenderWindow& t_window)
{
	t_window.clear(sf::Color::Black);
	lightShader.setUniform("hasTexture", true);
	//lightShader.setUniform("lightPos", sf::Vector2f(m_player.getPosition() + sf::Vector2f(32, 32)));
	sf::Vector2f camPos = Game::m_screenView.getCenter();
	// Level
	sf::Vector2f Lts[10];
	Lts[0] = sf::Vector2f(64 * 2, 64 * 1);
	Lts[1] = sf::Vector2f(64 * 8, 64 * 5);
	Lts[2] = sf::Vector2f(64 * 4, 64 * 3);
	Lts[3] = sf::Vector2f(64 * 5, 64 * 7);
	Lts[4] = sf::Vector2f(64 * 7, 64 * 2);
	Lts[5] = sf::Vector2f(64 * 2, 64 * 4);
	Lts[6] = sf::Vector2f(64 * 12, 64 * 1);
	Lts[7] = sf::Vector2f(64 * 10, 64 * 3);
	Lts[8] = sf::Vector2f(64 * 4, 64 * 12);
	Lts[9] = sf::Vector2f(64 * 15, 64 * 2);

	for (int i = 0; i < m_bottomLayer.size(); i++)
	{
		sf::Vector2f tile = m_bottomLayer.at(i)->getPosition();
		if (
			tile.x > (camPos.x - SCREEN_WIDTH / 3) &&
			tile.x < (camPos.x + SCREEN_WIDTH / 3) &&
			tile.y >(camPos.y - SCREEN_HEIGHT / 3) &&
			tile.y < (camPos.y + SCREEN_HEIGHT / 3)
			)
		{
			// Array of light positions
			// distance check to get the closest in a loop
			// Pass that light into the shader, lightShader.setUniform("lightPos", light[x]);

			lightShader.setUniform("lightPos", sf::Vector2f(m_player.getPosition() + sf::Vector2f(32, 32)));
			t_window.draw(*(m_bottomLayer.at(i)->getSprite()), &lightShader);
			/*lightShader.setUniformArray("lightPos", Lts, 10);

			t_window.draw(*(m_bottomLayer.at(i)->getSprite()), &lightShader);*/

		}
	}
	for (int i = 0; i < m_level.size(); i++)
	{
		sf::Vector2f tile = m_level.at(i)->getPosition();
		if (
			tile.x > (camPos.x - SCREEN_WIDTH / 3) &&
			tile.x < (camPos.x + SCREEN_WIDTH / 3) &&
			tile.y >(camPos.y - SCREEN_HEIGHT / 3) &&
			tile.y < (camPos.y + SCREEN_HEIGHT / 3)
			)
		{

			lightShader.setUniform("lightPos", sf::Vector2f(m_player.getPosition() + sf::Vector2f(32, 32)));
			t_window.draw(*(m_level.at(i)->getSprite()), &lightShader);
			//t_window.draw(*(m_level.at(i)->getSprite()));
		}
	}
	for (int i = 0; i < m_levelDoors.size(); i++)
	{
		m_levelDoors.at(i)->render(t_window, lightShader);
	}
	sf::Vector2f keyUI = Game::m_screenView.getCenter() + sf::Vector2f{ 350,-250 };
	for (int i = 0; i < m_levelKeys.size(); i++)
	{
		if (m_levelKeys.at(i)->held() == false)
		{
			m_levelKeys.at(i)->render(t_window, lightShader);
		}
		else
		{
			m_levelKeys.at(i)->setPosition(keyUI);
			keyUI = keyUI - sf::Vector2f{ 35,0 };
			m_levelKeys.at(i)->render(t_window, lightShader);
		}

	}

	// Game entities
	if (rock.getHeld() == false)
	{
		rock.render(t_window, lightShader);
	}

	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies.at(i).render(t_window, lightShader);
	}
	m_player.render(t_window);
	if (rock.getHeld() == true)
	{
		rock.render(t_window, lightShader);
	}

	if (debug)
	{
		for (int i = 0; i < graph->getNodes()->size(); i++)
		{
			t_window.draw(graph->getNodes()->at(i)->m_data.m_circle);
		}
	}
	//t_window.draw(end);

}

void Gameplay::initialize()
{
	end.setSize(sf::Vector2f(200, 150));
	end.setPosition(3600, 775);
	end.setFillColor(sf::Color::Red);

	if (!backgroundMusik.openFromFile("Assets/Audio/creepy_track_1.wav"))
	{
		std::cout << "ERROR, loading background musik" << std::endl;
	}
	backgroundMusik.setVolume(Game::MUSIC_VOLUME / 2);
	if (backgroundMusik.getStatus() != sf::Music::Status::Playing)
		backgroundMusik.play();
	backgroundMusik.setLoop(true);

	initializeEnemies();

	lightShader.loadFromFile("vertex_shader.vert", "frag_shader.txt");
	m_player.update();
	// Reads in from fill in Form (Name, score)
	int index, xPos, yPos;
	int layer{ 0 };
	std::string line;
	std::string st;
	std::string stg = "levelone.txt";
	std::ifstream file(stg);
	bool isCopy = false;
	// Read in names and scores from file
	int counter = 0;
	if (file.is_open())
	{
		while (file >> index >> xPos >> yPos >> layer)
		{
			counter++;
			if (layer == 0)
			{
				st = "Test" + std::to_string(index);
				Tile* sp = new Tile(*gameAssets, st, index, 0);
				sp->setPosition(sf::Vector2f(xPos, yPos));
				m_bottomLayer.push_back(sp);
			}
			else if (layer == 1)
			{
				if (index == 4)				// Door
				{
					int r, g, b;
					r = rand() % 255;
					g = rand() % 255;
					b = rand() % 255;
					currentColor = sf::Color(r, g, b, 255);
					Door* d = new Door(sf::Vector2f(xPos, yPos), *gameAssets);
					currentDoor = d;
					d->setColor(currentColor);
					m_levelDoors.push_back(d);
				}
				else if (index == 20)		// Key
				{
					Key* k = new Key(currentDoor, *gameAssets);
					k->setPosition(sf::Vector2f(xPos, yPos));
					currentDoor->setKey(k);
					k->setColor(currentColor);
					m_levelKeys.push_back(k);
				}
				else if (index == 5)		// Player
				{
					m_player.setPosition(sf::Vector2f(xPos, yPos));
				}
				else 	// Change this to the correct one for the door
				{
					st = "Test" + std::to_string(index);
					Tile* sp = new Tile(*gameAssets, st, index, 0);
					sp->setPosition(sf::Vector2f(xPos, yPos));
					m_level.push_back(sp);
				}
			}
		}
		file.close();
		std::cout << m_level.size() << std::endl;

		/*for (int i = 0; i < m_levelDoors.size(); i++)
		{
			Key* k = new Key(m_levelDoors.at(i), *gameAssets);
			k->setPosition(sf::Vector2f(64, 128));
			m_levelDoors.at(i)->setKey(k);
			m_levelKeys.push_back(k);
		}*/
		for (int i = 0; i < m_levelDoors.size(); i++)
		{
			std::cout << "X: " << m_levelDoors.at(i)->getPosition().x << " Y: " << m_levelDoors.at(i)->getPosition().y << std::endl;
		}
		std::cout << "Door count: " << m_levelDoors.size() << std::endl;
		for (int i = 0; i < m_levelKeys.size(); i++)
		{
			std::cout << "X: " << m_levelKeys.at(i)->getPosition().x << " Y: " << m_levelKeys.at(i)->getPosition().y << std::endl;
		}
		std::cout << "Key count: " << m_levelKeys.size() << std::endl;

		//m_levelKeys.at(0)->setPosition(sf::Vector2f(-1000,-1000)); // Door no open
		//m_levelKeys.at(1)->setPosition(sf::Vector2f(1984,1728));
		//m_levelKeys.at(2)->setPosition(sf::Vector2f(960,512));
		//m_levelKeys.at(3)->setPosition(sf::Vector2f(1664, 896));
		//m_levelKeys.at(4)->setPosition(sf::Vector2f(960,256));
		//m_levelKeys.at(5)->setPosition(sf::Vector2f(832,128));
		//m_levelKeys.at(6)->setPosition(sf::Vector2f(1024,1600));
		//m_levelKeys.at(7)->setPosition(sf::Vector2f(1280,2240));
		//m_levelKeys.at(8)->setPosition(sf::Vector2f(64,640));
		//m_levelKeys.at(9)->setPosition(sf::Vector2f(64,640));
		//m_levelKeys.at(10)->setPosition(sf::Vector2f(64,640));
		//m_levelKeys.at(11)->setPosition(sf::Vector2f(64,640));
		//m_levelKeys.at(12)->setPosition(sf::Vector2f(64,640));
		//m_levelKeys.at(13)->setPosition(sf::Vector2f(64,640));
		//m_levelKeys.at(14)->setPosition(sf::Vector2f(3264, 2048));
		initializeGraph();
		setGraphNeighbours();
	}
}
void Gameplay::runAction(std::string& t_actionString)
{

}

void Gameplay::handleControllerInput()
{

}

void Gameplay::initializeEnemies()
{
	m_enemies.clear();
	Enemy* tempEnemy;
	std::vector<MyVector3> tempEnemyPath;
	std::string fileName = "LVLONEE.txt";
	std::ifstream file(fileName);
	// Read in enemy info from file
	int index, xPos, yPos, xPosOne, yPosOne, xPosTwo, yPosTwo, xPosThree, yPosThree;
	if (file.is_open())
	{
		while (file >> index >> xPos >> yPos >> xPosOne >> yPosOne >> xPosTwo >> yPosTwo >> xPosThree >> yPosThree)
		{
			if (index == 6)
			{
				tempEnemyPath.clear();
				// create Enemy
				tempEnemy = new Enemy(&m_player, graph, MyVector3(xPos, yPos, 0));
				// create its set path
				tempEnemyPath.push_back(MyVector3(xPos, yPos, 0));
				tempEnemyPath.push_back(MyVector3(xPosOne, yPosOne, 0));
				tempEnemyPath.push_back(MyVector3(xPosTwo, yPosTwo, 0));
				tempEnemyPath.push_back(MyVector3(xPosThree, yPosThree, 0));
				tempEnemy->passSetPath(tempEnemyPath);
				m_enemies.push_back(*tempEnemy);
			}
		}
		file.close();
	}
}


void Gameplay::initializeGraph()
{
	delete graph; // delete from heap
	graph = new Graph<NodeData, int>(2360);// m_bottomLayer.size());

	NodeData nodeData; // needed for graph populating
	bool isCopy = false;

	int index = 0;
	for (Tile* tile : m_bottomLayer)
	{
		isCopy = false;
		for (int i = 0; i < index; i++)
		{
			if ((MyVector3)tile->getPosition() == graph->getNodes()->at(i)->m_data.m_position) // this node position already exists
			{
				isCopy = true;
			}
		}

		if (!isCopy)
		{
			nodeData.m_position = tile->getPosition();
			nodeData.m_isPassable = true;
			nodeData.m_circle.setFillColor(sf::Color::Green);
			nodeData.m_circle.setRadius(20);
			nodeData.m_circle.setPosition(nodeData.m_position);
			graph->addNode(nodeData, index);
			index++;

		}
		if (index >= 2360)
		{
			break;
		}
	}

	int test = 0;
	for (Tile* tile : m_level)
	{
		for (int i = 0; i < graph->getNodes()->size(); i++)
		{
			if ((MyVector3)tile->getPosition() == graph->getNodes()->at(i)->m_data.m_position) // this node position already exists
			{
				graph->getNodes()->at(i)->m_data.m_isPassable = false;
				graph->getNodes()->at(i)->m_data.m_circle.setFillColor(sf::Color::Blue);
				//m_circles.at(i)->setFillColor(sf::Color::Blue);
				test++;
			}
		}
	}
	//std::cout << test << std::endl;

	std::sort(graph->getNodes()->begin(), graph->getNodes()->end(), sortNodes);
	setGraphNeighbours();
}

void Gameplay::setGraphNeighbours()
{
	int mapWidth = 59;
	int mapHeight = 40;

	for (int y = 0; y < mapHeight; y++)
	{
		for (int i = 0; i < mapWidth; i++)
		{
			// left and right neighbours======================================================
			//LEFT COLUMMN CATCH
			if (i == 0) { // THE LEFT COLUMN
				graph->addArc(i + (mapWidth * y), i + (mapWidth * y) + 1, 64);
			}
			// RIGHT COLUMN CATCH
			else if (i == (mapWidth - 1)) {
				graph->addArc(i + (mapWidth * y), i + (mapWidth * y) - 1, 64);
			}
			else
			{
				graph->addArc(i + (mapWidth * y), i + (mapWidth * y) + 1, 64);
				graph->addArc(i + (mapWidth * y), i + (mapWidth * y) - 1, 64);
			}

			// top and bottom neighbours========================================================
			// TOP ROW CATCH
			if (y == 0) { // TOP ROW
				graph->addArc(i + (mapWidth * (y + 1)), i + (mapWidth * y), 64);
			}
			//BOTTOM ROW CATCH
			else if (y == (mapHeight - 1))
			{
				graph->addArc(i + (mapWidth * (y - 1)), i + (mapWidth * y), 64);
			}
			else {
				graph->addArc(i + (mapWidth * (y - 1)), i + (mapWidth * y), 64);
				graph->addArc(i + (mapWidth * (y + 1)), i + (mapWidth * y), 64);
			}
		}
	}

	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies.at(i).passGraph(graph);
	}
	m_player.passGraph(graph);

}

void Gameplay::rockCheck(Rock& t_rock, bool pressed, sf::Time t_deltaTime, sf::RenderWindow& t_window, MyVector3 mouseClick)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		float rockNearDist = ((m_player.getPosition() + MyVector3(32, 32, 0)) - t_rock.getPosition()).length();
		if (rockNearDist < 40)
		{
			t_rock.setHeld(true);
		}
	}
	if (t_rock.getHeld() == true)
	{
		t_rock.setPosition(m_player.getPosition() + MyVector3(25, 50, 0));
	}
	if (pressed == true && t_rock.getHeld() == true)
	{
		t_rock.beThrown(MyVector3(400, 380, 0));
	}
	if (t_rock.checkEmitSound())
	{ 
		for (int i = 0; i < m_enemies.size(); i++)
		{
			m_enemies.at(i).rockLanded(t_rock.getPosition());
		}
	}

	bool coll = false;
	bool collRock = false;
	for (int i = 0; i < m_level.size(); i++)
	{
		sf::Vector2f camPos = Game::m_screenView.getCenter();

		sf::Vector2f tile = m_level.at(i)->getPosition();
		if (
			tile.x > (camPos.x - SCREEN_WIDTH / 2) &&
			tile.x < (camPos.x + SCREEN_WIDTH / 2) &&
			tile.y >(camPos.y - SCREEN_HEIGHT / 2) &&
			tile.y < (camPos.y + SCREEN_HEIGHT / 2)
			)
		{
			coll = Collider::collisionPosSize(

				m_player.getPosition() + sf::Vector2f(20, 35),
				sf::Vector2f(25, 25),
				m_level.at(i)->getPosition() + sf::Vector2f(0, 0),
				sf::Vector2f(64, 64)
			);
			if (coll == true)
			{
				m_player.stepBack();
				break;
			}

			collRock = Collider::collisionPosSize(

				t_rock.getPosition(),
				sf::Vector2f(8, 8),
				m_level.at(i)->getPosition(),
				sf::Vector2f(64, 64)
			);
			if (collRock == true)
			{
				t_rock.collideStop(true);
			}
		}

	}
	t_rock.update(t_deltaTime, t_window.mapPixelToCoords(mouseClick), pressed);
}

void Gameplay::updateVolume()
{
	backgroundMusik.setVolume(Game::MUSIC_VOLUME / 2);
}
