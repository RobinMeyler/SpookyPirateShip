#include "StateChangeHandler.h"

StateChangeHandler::StateChangeHandler(int t_animationType)
{
	m_current = new Idle(t_animationType);
}

StateChangeHandler::~StateChangeHandler()
{
}

void StateChangeHandler::setCurrent(State* newCurrent)
{
	m_current = newCurrent;
}

State* StateChangeHandler::getCurrent()
{
	return m_current;
}
