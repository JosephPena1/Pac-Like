#include "FleePathBehavior.h"

MathLibrary::Vector2 FleePathBehavior::findDestination(Agent* owner)
{
	return owner->getWorldPosition() - getTarget()->getWorldPosition();
}
