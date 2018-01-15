// Queue.cpp - Implementation of Queue ADT using Pointers

#include <iostream>
#include <string>
using namespace std;
#include "stdafx.h"
#include "Queue.h"
#include "BinaryNode.h"
// constructor
Queue::Queue() {}

// destructor
Queue::~Queue() { frontNode == NULL; }

// check if the queue is empty
bool Queue::isEmpty()
{
	if (frontNode == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// enqueue(add) item at the back of queue
bool Queue::enqueue(BinaryNode* item)
{
	Node *newNode = new Node;
	newNode->item = item;
	newNode->next = NULL;

	if (isEmpty() == true) 
	{
		frontNode = newNode;
	}

	else 
	{
		backNode->next = newNode; // back node's next pointer point to new node
	}

	backNode = newNode;

	return true;
}

// dequeue item from front of queue
bool Queue::dequeue()
{
	if (frontNode == backNode) // only 1 node in queue
	{
		frontNode = NULL;
		backNode = NULL;
		return true;
	}
	else
	{
		Node* tempNode = frontNode;
		frontNode = frontNode->next;
		tempNode->next = NULL;
		delete tempNode;
		return true;
	}
}

// dequeue and retrieve item from front of queue
bool Queue::dequeue(BinaryNode* item)
{
	item = frontNode->item;

	if (frontNode == backNode) // only 1 node in queue
	{
		frontNode = NULL;
		backNode = NULL;
		return true;
	}
	else
	{
		Node* tempNode = frontNode;
		frontNode = frontNode->next;
		tempNode->next = NULL;
		delete tempNode;
		return true;
	}
}

// retrieve item from top of stack
void Queue::getFront(BinaryNode* item)
{
	if (isEmpty() != true)
	{
		item = frontNode->item;
	}
}

// display items in queue from front to back
void Queue::displayItems() 
{
	if (isEmpty()) 
	{
		cout << "Queue is empty";
	}

	else 
	{
		Node *tempNode = frontNode;

		cout << "Items in queue (from front to back): ";
		while (true)
		{
			cout << tempNode->item->item << " ";

			if (tempNode->next == NULL)
			{
				cout << endl;
				break;
			}
			tempNode = tempNode->next;
		}
	}
}
