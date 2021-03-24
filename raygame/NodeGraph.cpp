#include "NodeGraph.h"
#include <raylib.h>

std::deque<NodeGraph::Node*> NodeGraph::findPath(Node* start, Node* end)
{
	// Find a path from start to end (The current implementation is obviously insufficient)
	Node* begin = start;
	Node* goal = end;

	begin->gScore = 1;
	//Check if the start or the goal pointer is null
	//if so return an empty list
	if (!begin || !goal)
		return std::deque<Node*>();

	//Create a node pointer that will act as an iterator
	Node* currentNode;

	std::deque<Node*> openList;
	std::deque<Node*> closedList;

	openList.push_back(begin);

	//Loop while the open list is not empty
	while (!openList.empty())
	{
		//Sort the items in the open list by the g score
		//Uses Selection Sorting
		int pos = 0;
		Node* temp = nullptr;

		for (int i = 0; i < openList.size(); i++)
		{
			pos = findSmallest(openList, i);
			temp = openList[i];
			openList[i] = openList[pos];
			openList[pos] = temp;
		}
		//End Sorting//

		currentNode = openList[0];

		//If the current node is the goal
		//return new path found
		if (currentNode == goal)
		{
			Node* iter = nullptr;
			std::deque<Node*> goalPath;
			goalPath.push_front(currentNode);

			for (int i = 0; i < closedList.size(); i++)
				if (goalPath[0]->previous)
				{
					if (goalPath[0]->gScore != 1)
						goalPath.push_front(goalPath[0]->previous);
					else
						break;
				}

			return goalPath;
		}

		//Pop the first item off the open list
		openList.pop_front();
		//Add the first item to the closed list
		closedList.push_back(currentNode);

		//Loop through all of the edges for the iterator
		for (int i = 0; i < currentNode->connections.size(); i++)
		{
			Node* currentEdgeEnd = nullptr;

			currentEdgeEnd = currentNode->connections[i].target;

			//Check if node at the end of the edge is in the closed list
			if (!InList(closedList, currentEdgeEnd))
			{
				//Create a float and set it to be the g score of the iterator plus the cost of the edge
				float gScoreTotal = currentNode->gScore + currentNode->connections[i].cost;

				//Check if the node at the end of the edge is in the open list
				if (!InList(openList, currentEdgeEnd))
				{
					currentEdgeEnd->gScore = gScoreTotal;
					currentEdgeEnd->previous = currentNode;
					//Add the node to the open list
					openList.push_front(currentEdgeEnd);
				}

				//Otherwise if the g score is less than the node at the end of the edge's g score...
				else if (currentNode->gScore < currentEdgeEnd->gScore)
				{
					currentEdgeEnd->gScore = gScoreTotal;
					currentEdgeEnd->previous = currentNode;
				}
			}
			//end if statement
		}
		//end loop

		//Removes any nodes with a gscore of 100 or greater
		for (int i = 0; i < openList.size(); i++)
		{
			if (openList[i]->gScore >= 100)
			{
				Node* temp = openList.back();
				openList.back() = openList[i];
				openList[i] = temp;

				openList.pop_back();
			}
		}

	}
	//end loop
}

void NodeGraph::drawGraph(Node* start)
{
	std::deque<Node*>* drawnList = new std::deque<Node*>();
	drawConnectedNodes(start, drawnList);
	delete drawnList;
}

void NodeGraph::drawNode(Node* node, int color)
{
	static char buffer[10];
	sprintf_s(buffer, "%.0f", node->gScore);

	//Draw the circle for the outline
	DrawCircle((int)node->position.x, (int)node->position.y, 16, GetColor(color));
	//Draw the inner circle
	DrawCircle((int)node->position.x, (int)node->position.y, 14, BLACK);
	//Draw the text
	DrawText(buffer, (int)node->position.x, (int)node->position.y, 24, RAYWHITE);
}

void NodeGraph::drawConnectedNodes(Node* node, std::deque<Node*>* drawnList)
{
	//drawNode(node);
	drawnList->push_back(node);

	//For each Edge in this node's connections
	for (Edge e : node->connections) {
		//Draw the Edge
		DrawLine((int)node->position.x, (int)node->position.y, (int)e.target->position.x, (int)e.target->position.y, WHITE);
		//Draw the cost
		MathLibrary::Vector2 costPos = { (node->position.x + e.target->position.x) / 2, (node->position.y + e.target->position.y) / 2 };
		static char buffer[10];
		sprintf_s(buffer, "%.0f", e.cost);
		DrawText(buffer, (int)costPos.x, (int)costPos.y, 16, RAYWHITE);
		//Draw the target node
		if (std::find(drawnList->begin(), drawnList->end(), e.target) == drawnList->end()) {
			drawConnectedNodes(e.target, drawnList);
		}
	}
}

bool NodeGraph::InList(std::deque<Node*> list, Node* current)
{
	for (int j = 0; j < list.size(); j++)
		if (current == list[j])
			return true;

	return false;
}

float NodeGraph::findSmallest(std::deque<Node*> list, int i)
{
	float smallNum = list[i]->gScore;
	int position = i;

	for (int j = i + 1; j < list.size(); j++)
		if (list[j]->gScore < smallNum)
		{
			smallNum = list[j]->gScore;
			position = j;
		}

	return position;
}
