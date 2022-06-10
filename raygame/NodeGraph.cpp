#include "NodeGraph.h"
#include <raylib.h>

std::deque<NodeGraph::Node*> NodeGraph::findPath(Node* start, Node* end)
{
	// Find a path from start to end (The current implementation is obviously insufficient)
	std::deque<Node*> path;

	if (!start || !end)
		return std::deque<Node*>();

	//Create a node pointer that will act as an iterator
	Node* currentNode = nullptr;

	std::deque<Node*> openList;
	std::deque<Node*> closedList;

	//Add start to the open list
	openList.push_back(start);

	//Loop while the open list is not empty
	while (!openList.empty())
	{
		//Sort the items in the open list by the g score
		int pos = 0;
		Node* temp = nullptr;

		for (unsigned int i = 0; i < openList.size(); i++)
			for (unsigned int j = openList.size() - 1; j > i; j--)
				if (openList[j]->fScore < openList[j - 1]->fScore)
				{
					Node* temp = openList[j];
					openList[j] = openList[j - 1];
					openList[j - 1] = temp;
				}

		currentNode = openList[0];

		//Check if the current node is the end
		if (currentNode == end)
		{
			while (currentNode->previous != nullptr)
			{
				path.push_front(currentNode);
				Node* nextNode = currentNode;
				currentNode = currentNode->previous;
				nextNode->previous = nullptr;
			}
			return path;
		}

		//Pop the first item off the open list
		openList.pop_front();
		//Add the first item to the closed list
		closedList.push_back(currentNode);

		//Loop through all of the edges for the iterator
		for (int i = 0; i < currentNode->connections.size(); i++)
		{
			//Create a node pointer to store the other end of the edge
			Node* currentEdgeEnd = currentNode->connections[i].target;

			//Check if node at the end of the edge is in the closed list
			if (!InList(closedList, currentEdgeEnd))
			{
				//Create a float and set it to be the g score of the iterator plus the cost of the edge
				float gScore = currentNode->gScore + currentNode->connections[i].cost;
				//Create a float and set it to be the h score of the node at the end of the edge
				float hScore = updateHScore(currentEdgeEnd, end);

				float fScore = gScore + hScore;

				//Check if the node at the end of the edge is in the open list
				if (!InList(openList, currentEdgeEnd))
				{
					//Set the scores to the calculated scores
					currentEdgeEnd->gScore = gScore;
					currentEdgeEnd->hScore = hScore;
					currentEdgeEnd->fScore = fScore;
					//Set the nodes previous to be the iterator
					currentEdgeEnd->previous = currentNode;
					//Add the node to the open list
					openList.push_back(currentEdgeEnd);
				}

				//Otherwise if the f score is less than the node at the end of the edge's g score...
				else if (currentNode->fScore < currentEdgeEnd->fScore)
				{
					//Set the scores to the calculated scores
					currentEdgeEnd->gScore = gScore;
					currentEdgeEnd->hScore = hScore;
					currentEdgeEnd->fScore = fScore;
					//Set the nodes previous to be the iterator
					currentEdgeEnd->previous = currentNode;
				}
			}
		}
	}
	return path;
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

bool NodeGraph::InList(std::deque<Node*> list, Node* node)
{
	for (int i = 0; i < list.size(); i++)
		if (list[i] == node)
			return true;

	return false;
}

float NodeGraph::updateHScore(Node* currentNode, Node* end)
{
	float distance = (currentNode->position - end->position).getMagnitude();
	return distance;
}