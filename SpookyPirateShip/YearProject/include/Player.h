#pragma once
#include "StateChangeHandler.h"
#include "MyVector3.h"
#include "SpeechBubble.h"
#include "SFML/Audio.hpp"

//TEMPORARY -JOSH
#include "Graph.h"
#include "NodeData.h"

typedef GraphArc<NodeData, int> Arc;
typedef GraphNode<NodeData, int> Node;

class Key;

class Player
{

private:
	MyVector3 m_previousPos;
	float speed;
	MyVector3 m_playerPos;
	SpeechBubble* m_speechBubble;
	std::vector<Key*> m_heldKeys;

	std::vector<sf::SoundBuffer> footStepBuffers;
	sf::Sound footStepSound;

public:
	Player();
	~Player();

	void update();
	void render(sf::RenderWindow& t_rendWind);
	std::vector<Key*>& heldKeys();
	void stepBack();
	StateChangeHandler m_state;
	MyVector3 getPosition();
	void addKey(Key* t_key);
	State* getState();
	void setPosition(sf::Vector2f pos);
	// temporary!! -josh
	Graph<NodeData, int>* graph;
	void passGraph(Graph<NodeData, int>* t_graph);
};

#include "Key.h"