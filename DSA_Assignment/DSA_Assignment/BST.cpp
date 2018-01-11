// BST.cpp

#include "stdafx.h"
#include<iostream>
using namespace std;
#include <cstddef>  // for NULL
#include <new>      // for bad_alloc
#include <string>
#include "BST.h"

// constructor
BST::BST()
{
	root = NULL;
}

void BST::DisplayValue(ItemType nodeNum)
{
	int intArray[100];
	int count = 0;

	for (int i = 1; i <= getHeight(); i++)
	{
		levelBylevelQueue(root, i, intArray, count);
		count++;

	}
	if (nodeNum - 1 <= count && nodeNum - 1 > -1)
		cout << intArray[nodeNum - 1] << endl;
	else
		cout << "Node not found" << endl;
}

void BST::levelBylevelQueue(BinaryNode* t, ItemType level, int *intArray, int count)
{	
	if (t == NULL)
		return;
	if (level == 1)
	{
		intArray[count] = t->item;
	}
	else if (level > 1)
	{
		levelBylevelQueue(t->left, level - 1, intArray, count);
		levelBylevelQueue(t->right, level - 1, intArray, count);
	}
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
			insert(t->left, item);  // insert in left subtree
		else
			insert(t->right, item); // insert in right subtree
}

// delete an item from the binary search tree
void BST::remove(ItemType target)
{
	remove(root, target);
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
		// -----------------------  case 1 : node is a leaf ------------------------
		if (current->left == NULL && current->right == NULL)
		{
			if (current == t)	// node to be deleted is a root
				t = NULL;
			else
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
					parent->right = current->right;;
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
	if (isEmpty())
		cout << "No item found" << endl;
	else
		inorder(root);
}

void BST::inorder(BinaryNode* t)
{
	if (t != NULL)
	{
		inorder(t->left);
		cout << t->item << ", ";
		inorder(t->right);
	}
}
// traverse the binary search tree in preorder
void BST::preorder()
{
	if (isEmpty())
		cout << "No item found" << endl;
	else
		preorder(root);
}

void BST::preorder(BinaryNode* t)
{
	if (t != NULL)
	{
		cout << t->item << endl;
		preorder(t->left);
		preorder(t->right);
	}
}

// traverse the binary search tree in postorder
void BST::postorder()
{
	if (isEmpty())
		cout << "No item found" << endl;
	else
		postorder(root);
}

void BST::postorder(BinaryNode* t)
{
	if (t != NULL)
	{
		postorder(t->left);
		postorder(t->right);
		cout << t->item << endl;
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

// check if the binary search tree is balanced
bool BST::isBalanced()
{
	return isBalanced(root);
}

bool BST::isBalanced(BinaryNode *t)
{
	if (t != NULL)
	{
		if (getHeight(t) < 4)
		{
			int leftHeight = getHeight(t->left);
			int rightHeight = getHeight(t->right);

			if (abs(leftHeight - rightHeight) <= 1)
				return true;
			else
				return false;
		}
		else
			return (isBalanced(t->left) && isBalanced(t->right));
	}
	else
		return true;
}

// check if the binary search tree is empty
bool BST::isEmpty()
{
	return (root == NULL);
}
