#include "Player.h"

Player::Player() : m_state(0)
{
	speed = 5;
	m_playerPos = sf::Vector2f(64, 64);
	m_speechBubble = nullptr;

	footStepBuffers.resize(4);
	for (int i = 0; i < 4; i++)
	{
		footStepBuffers.at(i).loadFromFile("Assets/Audio/footsteps/step_cloth" + std::to_string(i + 1) + ".ogg");
	}

	/*if (!footStepBuffers.loadFromFile("Assets/Audio/footsteps/step_cloth1.ogg"))
	{
		std::cout << "ERROR, loading footstep sound" << std::endl;
	}
	else
	{
		footStepSound.setBuffer(footStepBuffers);
	}*/
}

Player::~Player()
{
}

void Player::update()
{
	m_state.getCurrent()->update();

	if (m_speechBubble != nullptr)
	{
		m_speechBubble->update(m_playerPos);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::T) && m_speechBubble == nullptr)
	{
		std::string m_message = "Howdy partner, THERE'S A SNAKE IN MY BOOT!!! This is just an example block of text to showcase the speech box.";
		m_speechBubble = new SpeechBubble(m_playerPos, m_message);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
	{
		int index = -1;
		int distanceToNode = 900; // used to find closest node
		for (int i = 0; i < graph->getNodes()->size(); i++)
		{
			if ((m_playerPos - graph->getNodes()->at(i)->m_data.m_position).length() < distanceToNode && graph->getNodes()->at(i)->m_data.m_isPassable)
			{
				index = i;
				distanceToNode = (m_playerPos - graph->getNodes()->at(i)->m_data.m_position).length();
			}
		}
		std::cout << "Player at Pos: " + std::to_string(graph->getNodes()->at(index)->m_data.m_position.x) + ", " + std::to_string(graph->getNodes()->at(index)->m_data.m_position.y) << std::endl;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		m_state.getCurrent()->movingUp(&m_state);
		m_previousPos = m_playerPos;
		m_playerPos.y += -speed;

	
		if (footStepSound.getStatus() != sf::Sound::Status::Playing)
		{
			footStepSound.setBuffer(footStepBuffers.at(rand() % 4)); 
			footStepSound.play();
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		m_state.getCurrent()->movingDown(&m_state);
		m_previousPos = m_playerPos;
		m_playerPos.y += speed;

		
		if (footStepSound.getStatus() != sf::Sound::Status::Playing)
		{
			footStepSound.setBuffer(footStepBuffers.at(rand() % 4));
			footStepSound.play();
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_state.getCurrent()->movingRight(&m_state);
		m_previousPos = m_playerPos;
		m_playerPos.x += speed;

		
		if (footStepSound.getStatus() != sf::Sound::Status::Playing)
		{
			footStepSound.setBuffer(footStepBuffers.at(rand() % 4));
			footStepSound.play();
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		m_state.getCurrent()->movingLeft(&m_state);
		m_previousPos = m_playerPos;
		m_playerPos.x += -speed;

	
		if (footStepSound.getStatus() != sf::Sound::Status::Playing)
		{
			footStepSound.setBuffer(footStepBuffers.at(rand() % 4));
			footStepSound.play();
		}
	}
	else
	{
		m_state.getCurrent()->idle(&m_state);
	}
	m_state.getCurrent()->setSpritePos(m_playerPos);

	//const sf::Texture* tempTexture = m_state.getCurrent()->getSprite().getTexture();
	//m_sprite.setTexture(*m_state.getCurrent()->getSprite().getTexture(), false);
}


void Player::render(sf::RenderWindow& t_rendWind)
{
	t_rendWind.draw(m_state.getCurrent()->getSprite());
	if (m_speechBubble != nullptr)
	m_speechBubble->render(t_rendWind);
}

std::vector<Key*> & Player::heldKeys()
{
	return m_heldKeys;
}

void Player::stepBack()
{
	m_playerPos = m_previousPos;
}

MyVector3 Player::getPosition()
{
	return m_playerPos;
}

void Player::addKey(Key* t_key)
{
	m_heldKeys.push_back(t_key);
}

State* Player::getState()
{
	return m_state.getCurrent();
}

void Player::setPosition(sf::Vector2f pos)
{
	m_playerPos = pos;
}

void Player::passGraph(Graph<NodeData, int>* t_graph)
{
	graph = t_graph;
}


