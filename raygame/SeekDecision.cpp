#include "SeekDecision.h"
#include "Ghost.h"

void SeekDecision::makeDecision(Agent* agent, float deltaTime)
{
	Ghost* ghost = dynamic_cast<Ghost*>(agent);

	if (ghost)
	{
		ghost->getSeek()->setEnabled(true);
		ghost->getFlee()->setEnabled(false);

		if (ghost->getSeek()->getNeedPath())
			ghost->getSeek()->updatePath(agent);

		else if (ghost->getSeek()->getPath().empty())
			ghost->getSeek()->setNeedPath(true);
	}
}
