#include "SeekBehaviour.h"
#include "Maze.h"
#include "raylib.h"

void SeekBehaviour::update(Agent* owner, float deltaTime)
{
	//Don't update if disabled or no target
	if (!getEnabled() || !m_target)
		return;

	MathLibrary::Vector2 position = owner->getWorldPosition();
	MathLibrary::Vector2 destination = m_target->getWorldPosition();

	//If owner is at the destination, exit
	if (position == destination)
		return;

	//Find the direction
	MathLibrary::Vector2 direction = MathLibrary::Vector2::normalize(destination - position);

	//Calculate the force
	MathLibrary::Vector2 desiredVelocity = direction * owner->getMaxSpeed();
	MathLibrary::Vector2 steeringForce = desiredVelocity - owner->getVelocity();

	//Apply the force
	owner->applyForce(steeringForce);
}

void SeekBehaviour::draw(Agent* owner)
{
	int x = (int)owner->getWorldPosition().x;
	int y = (int)owner->getWorldPosition().y;
	x += Maze::TILE_SIZE / 2;
	y += Maze::TILE_SIZE / 2;
	DrawCircle(x, y, Maze::TILE_SIZE / 2, GetColor(owner->getColor()));
}