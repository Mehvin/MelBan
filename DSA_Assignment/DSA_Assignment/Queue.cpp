#include "stdafx.h"
#include "Queue.h"


Queue::Queue()
{
	count = 0;
}

Queue::~Queue() {}

bool Queue::enqueue(ItemTypeQueue& item)
{
	Node* tempNode = new Node;
	tempNode->item = item;
	tempNode->next = NULL;

	if (isEmpty())
		frontNode = tempNode;
	else
		backNode->next = tempNode;

	backNode = tempNode;
	count++;
	return true;
}

bool Queue::dequeue()
{
	Node* tempNode = new Node;

	if (count == 1)
	{
		frontNode = NULL;
		backNode = NULL;
	}
	else
	{
		tempNode = frontNode;
		frontNode = frontNode->next;
	}
	tempNode->next = NULL;
	delete tempNode;

	count--;
	return true;
}

bool Queue::dequeue(ItemTypeQueue& item)
{
	if (frontNode != NULL)
	{
		item = frontNode->item;
		return dequeue();
	}
	else
		return false;
}

void Queue::getFront(ItemTypeQueue& item)
{
	if (!isEmpty())
		item = frontNode->item;
}

void Queue::displayItems()
{
	Node* tempNode = frontNode;
	cout << count << endl;

	for (int i = 0; i < count; i++)
	{
		cout << tempNode->item;
		tempNode = tempNode->next;
	}
}

bool Queue::isEmpty()
{
	return frontNode == NULL;
}

