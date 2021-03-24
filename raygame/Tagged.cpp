#include "Tagged.h"
#include "Ghost.h"

void Tagged::makeDecision(Agent* agent, float deltaTime)
{
		ABDecision::makeDecision(agent, deltaTime);
}

bool Tagged::checkCondition(Agent* agent, float deltaTime)
{
	Ghost* ghost = dynamic_cast<Ghost*>(agent);
	if (ghost->checkCollision(ghost->getTarget()))
		return true;

	return false;
}
