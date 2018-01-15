// List.cpp - Implementation of List ADT using Pointers

#include <iostream>
#include <string>
using namespace std;
#include "stdafx.h"
#include "List.h"

// constructor
List::List() {}

// add an item to the back of the list (append)
bool List::add(ItemType item)
{
	Node *newNode = new Node;
	newNode->item = item;
	newNode->next = NULL;

	if (isEmpty())
	{
		firstNode = newNode; // set first node to point to new node
	}

	else
	{
		Node *tempNode = firstNode; // get first node

		while (tempNode->next != NULL)
		{
			tempNode = tempNode->next; // replaces tempNode with the next node
		}

		tempNode->next = newNode; // make last node's pointer(next) to newNode
	}

	size++; // increase size by 1
	return true;
}

// add an item at a specified position in the list (insert)
bool List::add(int index, ItemType item)
{
	if ((index >= 1) && (index <= size))  // if index is valid
	{
		Node *nodeAfter, *nodeBefore;
		Node *newNode = new Node;
		newNode->item = item;
		newNode->next = NULL;

		if (index == 1)
		{
			nodeAfter = firstNode; // Node after newNode will be the 2nd one here
			newNode->next = nodeAfter;	 // newNode point to next node
			firstNode = newNode;	 // firstNode to point to newNode
		}
		else
		{
			nodeBefore = firstNode; // get first node

			for (int i = 1; i < index - 1; i++) // to get node before newNode
			{
				nodeBefore = nodeBefore->next;
			}

			nodeAfter = nodeBefore->next; // to get node after newNode

			nodeBefore->next = newNode;
			newNode->next = nodeAfter;

		}
		size++;
		return true;
	}

	else
	{
		return false;
	}

}

// remove an item at a specified position in the list
void List::remove(int index)
{
	if ((index >= 1) && (index <= size))  // if index is valid
	{
		if (index == 1) // node to be removed is first node
		{
			if (size == 1) // only 1 node in list 
			{
				firstNode->next = NULL;
			}
			else
			{
				firstNode = firstNode->next;	 // replace firstNode with secondNode
			}
		}

		else
		{
			Node *nodeAfter, *nodeBefore;
			nodeBefore = firstNode; // get first node

			for (int i = 1; i < index - 1; i++) // to get node before node that need to be removed
			{
				nodeBefore = nodeBefore->next;
			}

			nodeAfter = nodeBefore->next->next; // to get node after node that need to be removed

			nodeBefore->next = nodeAfter;
		}
		size--;
	}
}

// get an item at a specified position of the list (retrieve)
ItemType List::get(int index)
{
	if ((index >= 1) && (index <= size))  // if index is valid
	{
		Node *tempNode = firstNode;

		for (int i = 1; i < index; i++)
		{
			tempNode = tempNode->next;
		}

		return tempNode->item;
	}
}

// check if the list is empty
bool List::isEmpty() { return size == 0; }

// check the size of the list
int List::getLength() { return size; }

// display the items in the list
void List::print()
{
	Node *tempNode = firstNode;

	if (isEmpty())
	{
		cout << "List is empty" << endl;
	}

	else
	{
		for (int i = 1; i <= size; i++)
		{
			cout << tempNode->item << endl;
			tempNode = tempNode->next;
		}
		cout << endl;
	}
}