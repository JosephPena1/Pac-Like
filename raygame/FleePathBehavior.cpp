#include "FleePathBehavior.h"

MathLibrary::Vector2 FleePathBehavior::findDestination(Agent* owner)
{
	return getTarget()->getWorldPosition();
}
