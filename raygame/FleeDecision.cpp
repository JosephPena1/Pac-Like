#include "FleeDecision.h"
#include "Ghost.h"

void FleeDecision::makeDecision(Agent* agent, float deltaTime)
{
	Ghost* ghost = dynamic_cast<Ghost*>(agent);

	if (ghost)
	{
		//ghost->getFlee()->setEnabled(true);
		ghost->getSeek()->setEnabled(false);
	}
}