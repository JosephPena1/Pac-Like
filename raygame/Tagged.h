#pragma once
#include "ABDecision.h"

class Tagged : public ABDecision
{
public:
	using ABDecision::ABDecision;

	//Decides what happens when a decision is made
	void makeDecision(Agent* agent, float deltaTime) override;

	bool checkCondition(Agent* agent, float deltaTime) override;
};