//Queue.h - Specification of Queue ADT (implemented using Pointers)
#pragma once
#include<string>
#include<iostream>
using namespace std;
#include "BinaryNode.h"

class Queue
{
private:
	struct Node
	{
		BinaryNode *item;	// item
		Node     *next;	// pointer pointing to next item
	};

	Node *frontNode;	// point to the first item
	Node *backNode;		// point to the last item


public:
	// constructor
	Queue();

	~Queue();

	// check if the queue is empty
	bool isEmpty();

	// enqueue item at the back of queue
	bool enqueue(BinaryNode* newItem);

	// dequeue item from front of queue
	bool dequeue();

	// dequeue and retrieve item from front of queue
	bool dequeue(BinaryNode* item);

	// retrieve item from front of queue
	void getFront(BinaryNode* item);

	// display items in queue from front to back
	void displayItems();
};
