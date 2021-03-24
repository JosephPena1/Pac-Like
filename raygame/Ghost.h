#pragma once
#include "Agent.h"
#include "SeekPathBehavior.h"
#include "FleePathBehavior.h"

class Maze;
class DecisionBehavior;
class Tagged;
class SeekBehavior;
class FleeBehavior;

class Ghost : public Agent
{
public:
	/// <param name="x">The x-position</param>
	/// <param name="y">The y-position</param>
	/// <param name="speed">The maximum movement speed (magnitude)</param>
	/// <param name="color">The color in 0xRRGGBBAA</param>
	/// <param name="maze">The maze used for pathfinding</param>
	Ghost(float x, float y, float speed, int color, Maze* maze);
	~Ghost();

	virtual void update(float deltaTime) override;
	virtual void draw() override;

	virtual void onCollision(Actor* other) override;

	bool checkCollision(Actor* other);

	///<returns>The current target</returns>
	Actor* getTarget();
	SeekPathBehavior* getSeek() { return m_seekPathBehavior; }
	FleePathBehavior* getFlee() { return m_fleePathBehavior; }

	/// <summary>
	/// Set the target of the ghost
	/// </summary>
	/// <param name="target">The new target</param>
	void setTarget(Actor* target);

private:
	SeekPathBehavior* m_seekPathBehavior;
	FleePathBehavior* m_fleePathBehavior;
	DecisionBehavior* m_decisionBehavior;
	Tagged* m_tagged;

	Maze* m_maze;

	Actor* m_target = nullptr;
};

