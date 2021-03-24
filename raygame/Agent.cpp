#include "Agent.h"
#include "Behavior.h"
#include "raymath.h"

Agent::Agent()
	: Actor()
{
	m_maxForce = 1;
}

Agent::Agent(float x, float y, float collisionRadius, float maxSpeed, float maxForce, char icon)
	: Actor(x, y, collisionRadius, maxSpeed, icon)
{
	m_maxForce = maxForce;
}

Agent::Agent(float x, float y, float collisionRadius, float maxSpeed, float maxForce, int color)
	: Actor(x, y, collisionRadius, maxSpeed, color)
{
	m_maxForce = maxForce;
}

Agent::Agent(float x, float y, float collisionRadius, float maxSpeed, float maxForce, Sprite* sprite)
	: Actor(x, y, collisionRadius, maxSpeed, sprite)
{
	m_maxForce = maxForce;
}

Agent::Agent(float x, float y, float collisionRadius, float maxSpeed, float maxForce, const char* spriteFilePath)
	: Actor(x, y, collisionRadius, maxSpeed, spriteFilePath)
{
	m_maxForce = maxForce;
}

void Agent::update(float deltaTime)
{
	Actor::update(deltaTime);

	// Reset force to zero
	m_force = { 0,0 };

	// For each Behavior in Behavior list...
	for (int i = 0; i < m_behaviorList.size(); i++) 
	{
		// Update that behavior if it's enabled
		if (m_behaviorList[i]->getEnabled())
			m_behaviorList[i]->update(this, deltaTime);
	}

	// Add force times delta time to velocity
	setVelocity(getVelocity() + m_force * deltaTime);
	updateFacing();
}

void Agent::applyForce(MathLibrary::Vector2 force)
{
	m_force = force + m_force;

	if (m_force.getMagnitude() > m_maxForce)
		m_force = m_force.getNormalized() * m_maxForce;
}

void Agent::addBehavior(Behavior* behavior)
{
	m_behaviorList.push_back(behavior);
}
