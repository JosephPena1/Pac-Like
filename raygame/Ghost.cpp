#include "Ghost.h"
#include "Pac.h"
#include "Maze.h"
#include "Wall.h"
#include "raylib.h"
#include "DecisionBehavior.h"
#include "SeekDecision.h"
#include "FleeDecision.h"
#include "Tagged.h"

Ghost::Ghost(float x, float y, float maxSpeed, int color, Maze* maze)
	: Agent(x, y, Maze::TILE_SIZE / 2.5f, maxSpeed, maxSpeed, color)
{
	m_maze = maze;
	m_seekPathBehavior = new SeekPathBehavior(maze);
	m_fleePathBehavior = new FleePathBehavior(maze);

	SeekDecision* seek = new SeekDecision();
	FleeDecision* flee = new FleeDecision();
	m_tagged = new Tagged(seek, flee);
	m_decisionBehavior = new DecisionBehavior(m_tagged);
	//Sets the ghost color for it's seek and flee
	m_seekPathBehavior->setColor(color);
	m_fleePathBehavior->setColor(color);
	//Adds behaviours to ghost
	addBehavior(m_decisionBehavior);
	addBehavior(m_seekPathBehavior);
	addBehavior(m_fleePathBehavior);
}

Ghost::~Ghost()
{
	delete m_seekPathBehavior;
	delete m_fleePathBehavior;
	delete m_tagged;
	delete m_decisionBehavior;
}

void Ghost::update(float deltaTime)
{
	Agent::update(deltaTime);
}

void Ghost::draw()
{
	m_seekPathBehavior->draw(this);
	Agent::draw();
}

void Ghost::onCollision(Actor* other)
{
	if (Wall* wall = dynamic_cast<Wall*>(other)) {
		MathLibrary::Vector2 halfTile = { Maze::TILE_SIZE / 2.0f, Maze::TILE_SIZE / 2.0f };
		MathLibrary::Vector2 position = getWorldPosition();
		position = position + halfTile;
		MathLibrary::Vector2 tilePosition = {
			roundf(position.x / Maze::TILE_SIZE) * Maze::TILE_SIZE,
			roundf(position.y / Maze::TILE_SIZE) * Maze::TILE_SIZE
		};

		tilePosition = tilePosition - halfTile;
		setWorldPostion(tilePosition);

		setVelocity({ 0, 0 });
	}

}

bool Ghost::checkCollision(Actor* other)
{
	return Actor::checkCollision(other);
}

void Ghost::setTarget(Actor* target)
{
	m_target = target;
	m_seekPathBehavior->setTarget(target);
	m_fleePathBehavior->setTarget(target);
}

Actor* Ghost::getTarget()
{
	return m_target;
}
