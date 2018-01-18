// BST.cpp

#include "stdafx.h"
#include<iostream>
using namespace std;
#include <cstddef>  // for NULL
#include <new>      // for bad_alloc
#include <string>
#include "BST.h"
#include "List.h"

// constructor
BST::BST()
{
	root = NULL;
}

// check if value exists in the binary search tree
BinaryNode* BST::search(ItemType target)
{
	return search(root, target);
}

BinaryNode* BST::search(BinaryNode* t, ItemType target)
{
	if (t == NULL)	// item not found
	{
		return NULL;
	}
	else
	{
		if (t->item == target)	// item found
		{
			return t;
		}
		else 
		{
			if (target < t->item)	// search in left subtree
			{
				return search(t->left, target);
			}
			else // search in right subtree
			{
				return search(t->right, target);
			}
		}
	}
}

// prints path to value, only if value exists in the binary search tree
string BST::findPath(ItemType target)
{
	BinaryNode* p = search(target);
	
	if (p == NULL) 
	{
		return "Value not in tree!";
	}
	else 
	{
		cout << "Path: Root ";
		findPath(root, target);
		return "";
	}
}

BinaryNode* BST::findPath(BinaryNode* t, ItemType target)
{
	if (t->item == target)	// item found
	{
		return t;
	}
	else
	{
		if (target < t->item)	// search in left subtree
		{
			cout << "-> L ";
			return findPath(t->left, target);
		}
		else // search in right subtree
		{
			cout << "-> R ";
			return findPath(t->right, target);
		}
	}
}

// insert an item to the binary search tree
void BST::insert(ItemType item)
{
	insert(root, item);
}

void BST::insert(BinaryNode* &t, ItemType item)
{
	if (t == NULL)
	{
		BinaryNode *newNode = new BinaryNode;
		newNode->item = item;
		newNode->left = NULL;
		newNode->right = NULL;
		t = newNode;
	}
	else
		if (item < t->item) 
		{
			insert(t->left, item);  // insert in left subtree
		}
		else 
		{
			insert(t->right, item); // insert in right subtree
		}
}

// delete an item from the binary search tree
bool BST::remove(ItemType target)
{
	int initialNoOfNodes = countNodes();
	remove(root, target);
	int afterChangeNoOfNodes = countNodes();

	if (initialNoOfNodes == afterChangeNoOfNodes) 
	{
		return false; // return false = unsuccessful in removing
	}
}

void BST::remove(BinaryNode* &t, ItemType target)
{
	// search for the node to be deleted

	BinaryNode* current = t;
	BinaryNode* parent = NULL;
	bool isLeftChild = false;
	bool found = false;
	while ((!found) && (current != NULL))
	{
		if (target == current->item)
		{
			found = true;
		}
		else
		{
			parent = current;
			if (target < current->item)
			{
				current = current->left;	// go to left subtree
				isLeftChild = true;
			}
			else
			{
				current = current->right;	// go to right subtree
				isLeftChild = false;
			}
		}
	}

	if (found)
	{
		// -----------------------  case 0 : removing root of unbalance tree ------------------------
		if (current == t) // node to be deleted is a root
		{
			if (current->left != NULL)
			{
				current = current->left;
				root = current;
			}
			else if (current->right != NULL)
			{
				current = current->right;
				root = current;
			}
			else
			{
				root = NULL;
			}
		}
		// -----------------------  case 1 : node is a leaf ------------------------
		else if (current->left == NULL && current->right == NULL)
		{
			if (current == t)	// node to be deleted is a root
				t = NULL;
			if (current != t)
				if (isLeftChild)
					parent->left = NULL;
				else
					parent->right = NULL;
		}
		else
			// -----------------------  case 2 : node has only 1 child  ----------------
			if (current->left == NULL)
			{
				if (isLeftChild)
					parent->left = current->right;
				else
					parent->right = current->right;
			}
			else
				if (current->right == NULL)
				{
					if (isLeftChild)
						parent->left = current->left;
					else
						parent->right = current->left;;
				}
				else
					// -----------------------  case 3 : node has 2 children  ------------------
				{
					// find the successor ( rightmost child in the node’s left subtree)
					BinaryNode* successor = current->left;
					while (successor->right != NULL)
						successor = successor->right;
					// replace the node’s item with that of the successor
					int n = successor->item;
					// delete the successor (either case 1 or case 2)
					remove(t, n);
					// replace the node’s item with that of the successor
					current->item = n;
				}
	}
}

// traverse the binary search tree in inorder
void BST::inorder()
{
	List list;

	if (isEmpty()) 
	{
		cout << "No item found" << endl;
	}
	else
	{
		inorder(root, list);
	}

	for (int i = 1; i <= list.getLength(); i++) 
	{
		if (i == list.getLength()) // last number
		{
			cout << list.get(i);
		}
		else 
		{
			cout << list.get(i) << ", ";
		}
	}
}

void BST::inorder(BinaryNode* t, List& list)
{
	if (t != NULL)
	{
		inorder(t->left, list);
		list.add(t->item);
		inorder(t->right, list);
	}
}

// add all values to a given list
List BST::listOfAllValues()
{
	List list;
	listOfAllValues(root, list);
	return list;
}

void BST::listOfAllValues(BinaryNode* t, List& list) // using in-order traversal, add all values to array
{
	if (t != NULL)
	{
		listOfAllValues(t->left, list);
		list.add(t->item);
		listOfAllValues(t->right, list);
	}
}

// traverse the binary search tree level by level
List BST::levelByLevel()
{
	List list;

	for (int i = 1; i <= getHeight(); i++)
	{
		levelByLevel(root, i, list);
	}

	return list;
}

void BST::levelByLevel(BinaryNode* t, ItemType level, List& list)
{
	if (t == NULL)
	{
		return;
	}

	if (level == 1)
	{
		list.add(t->item);
	}
	else if (level > 1)
	{
		levelByLevel(t->left, level - 1, list);
		levelByLevel(t->right, level - 1, list);
	}
}

// display value of given node no
int BST::displayValueofNode(ItemType nodeNum)
{
	List list = levelByLevel();

	if (nodeNum > list.getLength()) // nodeNum not in tree
	{
		return -1;
	}
	else 
	{
		return list.get(nodeNum);
	}
}

// compute the height of the binary search tree
int BST::getHeight()
{
	return getHeight(root);
}

int BST::getHeight(BinaryNode* t)
{
	if (t == NULL)
		return 0;
	else
		return 1 + std::fmaxl(getHeight(t->left), getHeight(t->right));
}

// count the number of nodes in the binary search tree
int BST::countNodes()
{
	return countNodes(root);
}

int BST::countNodes(BinaryNode* t)
{
	if (t == NULL)
		return 0;
	else
		return 1 + countNodes(t->left) + countNodes(t->right);
}

// check if the binary search tree is empty
bool BST::isEmpty()
{
	return (root == NULL);
}

int BST::getMaxSpaces() 
{
	List lastLevelList;

	displayTree(root, getHeight(), lastLevelList); // storing all last level nodes in list

	return (lastLevelList.getLength() * 2) -1;
}

string BST::spaceMultiplier(int noOfSpaces)
{
	string spaces = "";

	for (int i = 0; i < noOfSpaces; i++) 
	{
		spaces += " ";
	}

	return spaces;
}

void BST::displayTree()
{
	int heightOfTree = getHeight();

	int oldSpaces = getMaxSpaces();
	int newSpaces = oldSpaces;

	for (int i = 1; i <= getHeight(); i++)
	{
		cout << spaceMultiplier(newSpaces);
		List list;
		displayTree(root, i, list);
		
		for (int j = 1; j <= list.getLength(); j++) 
		{
			if (list.get(j) == -1) 
			{
				cout << "x";
			}
			else 
			{
				cout << list.get(j);
			}
			cout << spaceMultiplier(oldSpaces);
		}
		cout << endl;

		if (i > 1)
		{
			oldSpaces = newSpaces;
		}
		newSpaces = newSpaces / 2;
	}
}

void BST::displayTree(BinaryNode* t, ItemType level, List& list)
{
	if (level == 1)
	{
		if (t != NULL) 
		{
			list.add(t->item);
		}
		else 
		{
			list.add(-1);
		}
	}
	else if (level > 1)
	{
		if (t == NULL)
		{
			displayTree(NULL, level - 1, list);
			displayTree(NULL, level - 1, list);
		}
		else 
		{
			displayTree(t->left, level - 1, list);
			displayTree(t->right, level - 1, list);
		}
	}
}