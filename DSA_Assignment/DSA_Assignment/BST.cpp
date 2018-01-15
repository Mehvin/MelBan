// BST.cpp

#include "stdafx.h"
#include<iostream>
using namespace std;
#include <cstddef>  // for NULL
#include <new>      // for bad_alloc
#include <string>
#include "BST.h"
#include "List.h"
#include "Queue.h"

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
		if (current == t)
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
		list.add(-1);
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

// check if the binary search tree is balanced
bool BST::isBalanced()
{
	return isBalanced(root);
}

bool BST::isBalanced(BinaryNode *t)
{
	if (t != NULL)
	{
		int leftHeight = getHeight(t->left);	// height of left sub-tree
		int rightHeight = getHeight(t->right);	// height of right sub-tree
		bool isBalancedNode = (abs(leftHeight - rightHeight) <= 1);
		return (isBalancedNode && isBalanced(t->left) && isBalanced(t->right));
	}
	else
		return true;
}

// check if the binary search tree is empty
bool BST::isEmpty()
{
	return (root == NULL);
}

void BST::displayTree()
{
	if (isEmpty()) 
	{
		cout << "Tree is empty!";
	}
	else 
	{
		//displayTree(root);


		List lbl = levelByLevel();
		bool check = true;
		int power = 0;
		int checksum;
		while (!lbl.isEmpty())
		{
			checksum = pow(2, power);

			if (getHeight() > 1 && power == 0)
			{
				cout << lbl.get(1) << endl;
				lbl.remove(1);
			}
			else
			{
				for (int i = 1; i <= checksum; i++)
				{
					if (lbl.get(1) != -1 && !lbl.isEmpty())
					{
						cout << lbl.get(1) << " ";
						lbl.remove(1);
					}
					else if (!lbl.isEmpty())
					{
						cout << lbl.get(1) << " ";

						lbl.remove(1);
					}

					if (i == checksum)
					{
						cout << endl;
					}					
				}
				
			}
			power++;

		}
	}
}




//void BST::displayTree(BinaryNode* t)
//{
//	if (t == NULL)
//	{
//		return;
//	}
//
//	Queue q1;
//	Queue q2;
//	BinaryNode* currentNode = t;
//
//	q1.enqueue(t);
//
//	while (!q1.isEmpty() || !q2.isEmpty()) // while q1 is not empty OR while q2 is not empty
//	{
//		while (!q1.isEmpty()) 
//		{
//			q1.dequeue(currentNode);
//			t = currentNode;
//
//			cout << t->item;
//			
//			if (t->left != NULL) 
//			{
//				q2.enqueue(t->left);
//			}
//			
//			if (t->right != NULL)
//			{
//				q2.enqueue(t->right);
//			}
//		}
//
//		cout << endl;
//		
//		while (!q2.isEmpty()) 
//		{
//			q2.dequeue(currentNode);
//			t = currentNode;
//
//			cout << t->item;
//
//			if (t->left != NULL)
//			{
//				q1.enqueue(t->left);
//			}
//
//			if (t->right != NULL)
//			{
//				q1.enqueue(t->right);
//			}
//		}
//	}
//
//	cout << endl;
//
//}


