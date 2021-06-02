#pragma once
#include "StateChangeHandler.h"
#include "MyVector3.h"
#include "Player.h"


#include "Graph.h"
#include "NodeData.h"
typedef GraphArc<NodeData, int> Arc;
typedef GraphNode<NodeData, int> Node;

class Enemy
{

private:
	SpeechBubble m_speechBubble{ m_enemyPos, "" };


public:
	Enemy() : m_state(1) {};
	Enemy(Player * t_player, Graph<NodeData, int>* t_graph, MyVector3 t_pos);
	~Enemy();

	void update(sf::Time t_deltaTime);
	void render(sf::RenderWindow &t_rendWind, sf::Shader& lighting);
	bool checkPlayerInFOV(MyVector3 t_playerPos);
	MyVector3 rotateVec(MyVector3 t_vec, int t_angle);
	void movePos(MyVector3 moveVec);
	void walkPath(sf::Time t_deltaTime);
	void unMarkGraph();
	void passGraph(Graph<NodeData, int>* t_graph);
	void passSetPath(std::vector<MyVector3> t_setPath) { enemySetPath = t_setPath; enemySetPathUnchanged = t_setPath;};
	Node* findNodeAtPos(MyVector3 pos);
	Node* findClosestNodeToPos(MyVector3 pos);
	void rockLanded(MyVector3 landedPos);

	StateChangeHandler m_state;

	float speed;
	int moveDirection; // direction enemy is moving
	MyVector3 m_enemyPos;
	MyVector3 m_centerImagePos;
	MyVector3 facingVector;
	sf::ConvexShape m_FOV; //FOV representation
	bool isPlayerVisisble;

	int changeDirectionCount;
	int changeDirectionMax;

	Graph<NodeData, int>* graph;
	std::vector<Node*> path; // a path used for pathfinding
	std::vector<Node*>* getPath() { return &path; }
	std::vector<MyVector3> enemySetPath;
	std::vector<MyVector3> enemySetPathUnchanged;
	MyVector3 moveVec;
	int startingIndex;
	double distanceToStartNode = 900; // used to find closest node
	int endIndex;
	double distanceToEndNode = 900; // used to find closest node

	float seenPlayerTimer = 0; // used to time how long player is seen
	float aStarTimer = 0; // used to run astar after elapsed time
	float speechTimer = 0; // used to time how long text box displays

	Player* m_playerRef;
};