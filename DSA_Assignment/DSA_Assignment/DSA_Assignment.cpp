/*
Student Name			: Melvin Ong, Bryan Seah	
Student ID				: S10170601E, S10175683B
Module Group			: P05
Features to highlight	:
*/

// DSA_Assignment.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include<iostream>
#include<string>
using namespace std;
#include "BST.h"

void displayMenu()
{
	cout << endl;
	cout << "	     DSA Assignment\n";
	cout << "----------------------------------------\n";
	cout << "[1] Search for a value \n"; //search for a value, val, and print the path to that node from the root. If root has value equal to val, print “root”; otherwise print “L” when the left child is visited and “R” when the right child is visited.
	cout << "[2] Add a new value \n"; // <!> optimize algorithm for insert - to balance tree
	cout << "[3] Remove a value \n"; // <!> optimize algorithm for remove - to balance tree
	cout << "[4] Display values in ascending order \n";
	cout << "[5] Display value of a node \n"; //display the value of the k-th node of the tree using level-by-level traversal. For example, the 3rd node is the right child of the root; the 5th node is the right child of the left child of the root.
	cout << "[6] Display tree \n"; 
	cout << "[0] Exit \n";
	cout << "----------------------------------------\n";
	cout << "Enter option: ";
}

int getNoOfConsecNums(int sum) // Returns the number of consecutive numbers that adds >= sum
{
	int noOfNumbers = 0, currentSum = 0;
	for (int i = 1; currentSum < sum; i++)
	{
		currentSum += i;
		noOfNumbers++;
	}

	return noOfNumbers;
}

int main()
{
	BST tree;
	ItemType value;

	int input;
	int option = 1;

	cout << "Enter a number: "; // Sum of consecutive numbers; to create initial tree
	cin >> input; // <!> validation - > 0?

	for (int i = 1; i <= getNoOfConsecNums(input); i++) // Inserting consecutive numbers into tree 
	{
		tree.insert(i);
	}
	
	while (option != 0) 
	{
		displayMenu();
		cin >> option;

		if (option == 1) // Search for a value and print the path
		{
			cout << "Enter a number to search: ";
			cin >> value;
			cout << tree.findPath(value);
		}

		else if (option == 2) // Add a new value
		{
			cout << "Enter a value to add: "; // <!> validation - unique value only & >= 0?
			cin >> value;
			tree.insert(value);
		}

		else if (option == 3) // Remove a value
		{
			cout << "Enter a value to remove: ";
			cin >> value;
			tree.remove(value);
		}

		else if (option == 4) // Display values in ascending order
		{
			cout << "Values in ascending order: ";
			tree.inorder(); // In-order traversal of a balanced tree will always be in ascending order
		}

		else if (option == 5) // Display value of a node
		{
			
		}

		else if (option == 6) // Display tree
		{

		}

		else if (option == 0)
		{
			cout << "Bye! \n";
		}

		else 
		{
			cout << "Invalid option. Please try again!"<< endl;
		}
	}

    return 0;
}

