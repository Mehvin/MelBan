#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;
#include "Stack.h"

Stack::Stack() {}
Stack::~Stack() {}

bool Stack::push(ItemTypeStack &item)
{
	Node *newnode = new Node;
	newnode->item = item;
	newnode->next = topNode;
	topNode = newnode;
	return true;
}

bool Stack::pop()
{
	if (!isEmpty())
	{
		Node *temp = new Node;
		temp = topNode;
		topNode = topNode->next;
		temp->next = NULL;
		delete temp;
		return true;
	}
	else
		return false;
}

bool Stack::pop(ItemTypeStack &item)
{
	if (!isEmpty())
	{
		item = topNode->item;
		Node *temp = new Node;
		temp = topNode;
		topNode = topNode->next;
		temp->next = NULL;
		delete temp;
		return true;
	}
	else
		return false;
}

void Stack::getTop(ItemTypeStack &item)
{
	if (!isEmpty())
		item = topNode->item;
}

bool Stack::isEmpty()
{
	if (topNode == NULL)
		return true;
	else
		return false;
}