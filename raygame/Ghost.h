#pragma once
#include "Agent.h"
#include "SeekBehaviour.h"
#include "SeekPathBehavior.h"

class Maze;
class DecisionBehavior;

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

	/// <summary>
	/// Set the target of the ghost
	/// </summary>
	/// <param name="target">The new target</param>
	void setTarget(Actor* target);

private:
	Maze* m_maze;
	Actor* m_target = nullptr;
	float m_speedBoost =  100.0f;

	SeekPathBehavior* m_seekPathBehavior;

	DecisionBehavior* m_decision;
};