#pragma once

#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "ResourceManager.h"
#include "GUIGlobals.h"
#include "GUI.h"
#include "Tile.h"
#include "Player.h"
#include "Enemy.h"
#include "Rock.h"
#include "Key.h"
#include "Door.h"


#include "Graph.h"
#include "NodeData.h"

typedef GraphArc<NodeData, int> Arc;
typedef GraphNode<NodeData, int> Node;
class Gameplay                         
{
public:
	Gameplay(ResourceManager& t_gameAssets);
	~Gameplay();
	void update(sf::Time t_deltaTime, MyVector3 mouseClick, bool pressed, sf::RenderWindow& t_window);
	void render(sf::RenderWindow & t_window);
	void initialize();
	void runAction(std::string & t_actionString);
	void handleControllerInput();
	void initializeEnemies();
	void initializeGraph();
	void setGraphNeighbours();
	void rockCheck(Rock& t_rock, bool pressed, sf::Time t_deltaTime, sf::RenderWindow& t_window, MyVector3 mouseClick);
	void reset();
	void updateVolume();

private:
	ResourceManager* gameAssets;
	std::vector<Tile*> m_level;
	std::vector<Tile*> m_bottomLayer;
	Rock rock;

	Player m_player;
	std::vector<Enemy> m_enemies;
	sf::Music backgroundMusik; // music for gameplay
	

	Graph<NodeData, int>* graph;
	//std::vector<sf::CircleShape*> m_circles; // for testing purposes -j

	std::vector<Key*> m_levelKeys;
	std::vector<Door*> m_levelDoors;

	sf::Shader lightShader;
	bool debug = false;

	sf::RectangleShape end;
	Door* currentDoor{ nullptr };
	sf::Color currentColor;
};

