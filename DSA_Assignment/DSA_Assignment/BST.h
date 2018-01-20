// BST.h
#pragma once
#include "BinaryNode.h"
#include "List.h"

class BST
{
private:

	BinaryNode* root;		// root of the BST

public:

	// constructor
	BST();

	// check if value exists in the binary search tree
	BinaryNode* search(ItemType target);
	BinaryNode* search(BinaryNode* root, ItemType target);

	// prints path to value, only if value exists in the binary search tree
	string findPath(ItemType target);
	BinaryNode* findPath(BinaryNode* root, ItemType target);

	// insert an item to the binary search tree
	void insert(ItemType item);
	void insert(BinaryNode* &root, ItemType item);

	// delete an item from the binary search tree
	bool remove(ItemType target);
	void remove(BinaryNode* &root, ItemType target);

	// traverse the binary search tree in inorder
	void inorder();
	void inorder(BinaryNode* t, List& list);

	// traverse the binary search tree in preorder
	List listOfAllValues();

	// traverse the binary search tree level by level
	List levelByLevel();
	void levelByLevel(BinaryNode* t, ItemType level, List& list);

	// return integer of value of given node no
	int displayValueofNode(ItemType nodeNum);

	// compute the height of the binary search tree
	int getHeight();
	int getHeight(BinaryNode* t);

	// count the number of nodes in the binary search tree
	int countNodes();
	int countNodes(BinaryNode* t);

	// check if the binary search tree is empty
	bool isEmpty();

	// for display tree
	int getMaxSpaces();
	string spaceMultiplier(int noOfSpaces);
	void displayTree();
	void levelByLeveForDisplay(BinaryNode* t, ItemType level, List& list);
};