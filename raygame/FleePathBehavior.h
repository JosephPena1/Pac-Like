#pragma once
#include "PathfindBehavior.h"

class FleePathBehavior : public PathfindBehavior
{
public:
	FleePathBehavior(Maze* maze) :PathfindBehavior(maze) {}

protected:
	virtual MathLibrary::Vector2 findDestination(Agent* owner) override;
};