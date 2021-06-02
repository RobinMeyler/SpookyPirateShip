#include "Enemy.h"
#include "Game.h"

// used for pathfinding only (not of importance)
void visit(Node* t_node)
{
	std::cout << "Visiting: " << t_node->m_data.m_position.x << ", " << t_node->m_data.m_position.y << std::endl;
}


Enemy::Enemy(Player* t_player, Graph<NodeData, int>* t_graph, MyVector3 t_pos) : m_state(1), m_playerRef(t_player), graph(t_graph), m_enemyPos(t_pos)
{
	
	speed = 2;
	moveDirection = -1;
	//m_enemyPos = { 64 * 12, 64 * 3, 0 }; // starting pos
	m_FOV.setPointCount(3);
}

Enemy::~Enemy()
{
}

void Enemy::update(sf::Time t_deltaTime)
{
	if ((m_playerRef->getPosition() - m_enemyPos).length() < 64)
	{
		Game::m_gameMode = GameMode::GameOver;
	}

	m_state.getCurrent()->update();
	seenPlayerTimer -= t_deltaTime.asSeconds();
	speechTimer -= t_deltaTime.asSeconds();
	m_speechBubble.update(m_enemyPos);
	if (speechTimer < 0)
	{
		m_speechBubble.changeMessage("", m_enemyPos);
	}

	if (checkPlayerInFOV(m_playerRef->getPosition()))
	{
		speechTimer = 3;
		if (speechTimer > 0)
		{
			std::string m_message = "I see an intruder! Get back here you punk kid!! :'(";
			m_speechBubble.changeMessage(m_message, m_enemyPos);
		}

		//Pathfinding
		isPlayerVisisble = true;
		if (speed == 2)
		{
			m_enemyPos = findClosestNodeToPos(m_enemyPos)->m_data.m_position;
			speed = 4;
		}
		seenPlayerTimer = 4;
	}
	else if (!checkPlayerInFOV(m_playerRef->getPosition()))
	{
		if (speechTimer > 0)
		{
			std::string m_message = "Gosh darn it, i lost em!";
			m_speechBubble.changeMessage(m_message, m_enemyPos);
		}
		
		//Pathfinding
		if (seenPlayerTimer < 0)
		{
			isPlayerVisisble = false;
			if (speed == 4)
			{
				m_enemyPos = findClosestNodeToPos(m_enemyPos)->m_data.m_position;
				speed = 2; // back to normal speed
			}
		}
	}

	switch (moveDirection)
	{
	case 0:
		//moving left
		m_state.getCurrent()->movingLeft(&m_state);
		m_enemyPos.x += -speed;
		facingVector = { -1,0,0 };
		break;
	case 1:
		//moving up
		m_state.getCurrent()->movingUp(&m_state);
		m_enemyPos.y += -speed;
		facingVector = { 0,-1,0 };
		break;
	case 2:
		//moving right
		m_state.getCurrent()->movingRight(&m_state);
		m_enemyPos.x += speed;
		facingVector = { 1,0,0 };
		break;
	case 3:
		//moving down
		m_state.getCurrent()->movingDown(&m_state);
		m_enemyPos.y += speed;
		facingVector = { 0,1,0 };
		break;
	default:
		break;
	}

	m_state.getCurrent()->setSpritePos(m_enemyPos);
	

	walkPath(t_deltaTime);
}

void Enemy::render(sf::RenderWindow &t_rendWind, sf::Shader & lighting)
{
	t_rendWind.draw(m_state.getCurrent()->getSprite(), & lighting);
	t_rendWind.draw(m_FOV);
	m_speechBubble.render(t_rendWind);
}

bool Enemy::checkPlayerInFOV(MyVector3 t_playerPos)
{
	m_centerImagePos = m_enemyPos;
	m_centerImagePos.x += m_state.getCurrent()->getSprite().getLocalBounds().width / 2;
	m_centerImagePos.y += m_state.getCurrent()->getSprite().getLocalBounds().height / 2;


	// Set FOV visual (yellow triangle)
	m_FOV.setFillColor(sf::Color(255, 255, 255, 40));
	m_FOV.setPoint(0, m_centerImagePos);
	m_FOV.setPoint(1, m_centerImagePos + (rotateVec(-facingVector, 60) * 200));
	m_FOV.setPoint(2, m_centerImagePos + (rotateVec(-facingVector, -60) * 200));

	MyVector3 directionToPlayer = t_playerPos - m_enemyPos;
	float angle = directionToPlayer.angleBetween(facingVector);
	if (angle <= 30 && directionToPlayer.length() <= 200)
	{
		return true;
	}
	else
	{
		return false;
	}
	return false;
}

MyVector3 Enemy::rotateVec(MyVector3 t_vec, int t_angle)
{
	MyVector3 newVec;
	newVec.x = t_vec.x * cos(t_angle) - t_vec.y * sin(t_angle);
	newVec.y = t_vec.x * sin(t_angle) + t_vec.y * cos(t_angle);

	return newVec;
}

void Enemy::movePos(MyVector3 moveVec)
{
	m_enemyPos = m_enemyPos + moveVec;
}

void Enemy::walkPath(sf::Time t_deltaTime)
{
	aStarTimer -= t_deltaTime.asSeconds();
	if (isPlayerVisisble)
	{
		if (path.size() < 1)
		{
			moveDirection = -1; // dont move baii
		}

		if ((m_playerRef->getPosition() - m_enemyPos).length() > 64 && aStarTimer < 0)
		{
			unMarkGraph();  // unmark all nodes so fresh graph
			path.clear(); // clear for the craic

			Node* startNode = findClosestNodeToPos(m_enemyPos);
			Node* goalNode = findClosestNodeToPos(m_playerRef->getPosition());

			graph->aStar(startNode, goalNode, visit, path);
			aStarTimer = 1;
		}
	}
	// If there is a path, but enemy is on front waypoint, delete it
	if (path.size() > 0 && (m_enemyPos - path.front()->m_data.m_position).length() < 5)
	{
		m_enemyPos = path.front()->m_data.m_position;
		path.front()->m_data.m_circle.setFillColor(sf::Color::Green);
		path.erase(path.begin());

		for (Node* node : path)
		{
			node->m_data.m_circle.setFillColor(sf::Color::Red);
		}
	}
	if (path.size() < 1 && !isPlayerVisisble)  // IF NO PATH, FIND PATH
	{
		moveDirection = -1; // dont move baii

		if (enemySetPath.size() < 1)
		{
			enemySetPath = enemySetPathUnchanged;
		}
		path.clear();
		unMarkGraph();  // unmark all nodes so fresh graph
		graph->aStar(findClosestNodeToPos(m_enemyPos), findNodeAtPos(enemySetPath.at(0)), visit, path);
		enemySetPath.erase(enemySetPath.begin());
	}
	if (path.size() > 0)
	{
		moveVec = (path.front()->m_data.m_position - m_enemyPos);

		if (moveVec == MyVector3(-64, 0, 0)) // move left
		{
			moveDirection = 0;
		}
		else if (moveVec == MyVector3(64, 0, 0)) // move right
		{
			moveDirection = 2;
		}
		else if (moveVec == MyVector3(0, 64, 0)) // move down
		{
			moveDirection = 3;
		}
		else if (moveVec == MyVector3(0, -64, 0)) // move up
		{
			moveDirection = 1;
		}
	}
}

void Enemy::unMarkGraph()
{
	for (int i = 0; i < graph->getNodes()->size(); i++)
	{
		graph->getNodes()->at(i)->setMarked(false);
	}
}

void Enemy::passGraph(Graph<NodeData, int>* t_graph)
{
	graph = t_graph;
}

Node* Enemy::findNodeAtPos(MyVector3 pos)
{
	for (int i = 0; i < graph->getNodes()->size(); i++)
	{
		if (graph->getNodes()->at(i)->m_data.m_position == pos)
		{
			return graph->getNodes()->at(i);
		}
	}
	return nullptr;
}

Node* Enemy::findClosestNodeToPos(MyVector3 pos)
{
	int index = -1;
	int distanceToNode = 900;

	for (int i = 0; i < graph->getNodes()->size(); i++)
	{
		if ((pos - graph->getNodes()->at(i)->m_data.m_position).length() < distanceToNode && graph->getNodes()->at(i)->m_data.m_isPassable)
		{
			index = i;
			distanceToNode = (pos - graph->getNodes()->at(i)->m_data.m_position).length();
		}
	}
	return graph->getNodes()->at(index);
}

void Enemy::rockLanded(MyVector3 landedPos)
{
	float distance = (m_enemyPos - landedPos).length();

	if (distance < 400 && !isPlayerVisisble)
	{
		unMarkGraph();  // unmark all nodes so fresh graph
		path.clear(); // clear for the craic

		Node* startNode = findClosestNodeToPos(m_enemyPos);
		Node* goalNode = findClosestNodeToPos(landedPos);

		graph->aStar(startNode, goalNode, visit, path);
	}
}
