#pragma once
#include "State.h"
#include "Idle.h"

class StateChangeHandler
{

private:
	State* m_current;

public:
	StateChangeHandler(int t_animationType);
	~StateChangeHandler();

	void setCurrent(State* newCurrent);
	State* getCurrent();

};