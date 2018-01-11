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
#include "List.h"

void displayMenu()
{
	cout << endl;
	cout << "	     DSA Assignment\n";
	cout << "----------------------------------------\n";
	cout << "[1] Search for a value \n";
	cout << "[2] Add a new value \n"; // <!> optimize algorithm for insert - to balance tree
	cout << "[3] Remove a value \n"; // <!> optimize algorithm for remove - to balance tree
	cout << "[4] Display values in ascending order \n";
	cout << "[5] Display value of a node \n"; //display the value of the k-th node of the tree using level-by-level traversal. For example, the 3rd node is the right child of the root; the 5th node is the right child of the left child of the root.
	cout << "[6] Display tree \n"; 
	cout << "[0] Exit \n";
	cout << "----------------------------------------\n";
	cout << "Enter option: ";
}

int getNoOfConsecNums(int sum) // Returns the number of consecutive numbers that adds => sum
{
	int noOfNumbers = 0, currentSum = 0;
	for (int i = 1; currentSum <= sum; i++)
	{
		currentSum += i;
		noOfNumbers++;
	}

	return noOfNumbers;
}

bool intValidation(string input) 
{
	char c;
	bool error = false;

	for each (c in input) 
	{
		if (c != '0' && c != '1' && c != '2' && c != '3' && c != '4' && c != '5' && c != '6' && c != '7' && c != '8' && c != '9')
		{
			error = true;
		}
	}

	return error;
}

int convertToInt(string input) 
{
	int integer = stoi(input);
	return integer;
}

int main()
{
	BST tree;
	ItemType value;
	string stringValue;

	string input;
	cout << "Enter a number: "; // Sum of consecutive numbers - to create initial tree
	cin >> input;
	cin.ignore();

	while (intValidation(input) == true)
	{
		cout << "Input is invalid, please try again!" << endl << endl << "Enter a number: ";
		cin.clear();
		cin.ignore();
		cin >> input;
	}

	for (int i = 1; i <= getNoOfConsecNums(convertToInt(input)); i++) // Inserting consecutive numbers into tree 
	{
		tree.insert(i);
	}
	
	int option = 1;
	while (option != 0)
	{
		displayMenu();
		cin >> input;

		while (intValidation(input) == true)
		{
			cout << "Invalid option, please try again!" << endl;
			cin.clear();
			cin.ignore();
			displayMenu();
			cin >> input;
		}

		option = convertToInt(input);

		if (option == 1) // Search for a value and print the path
		{
			cout << "Enter a number to search: ";
			cin >> stringValue;

			while (intValidation(stringValue) == true)
			{
				cout << "Invalid number, please try again!" << endl;
				cin.clear();
				cin.ignore();
				cout << endl;
				cout << "Enter a number to search: ";
				cin >> stringValue;
			}

			cout << tree.findPath(convertToInt(stringValue));
		}

		else if (option == 2) // Add a new value
		{
			cout << "Enter a value to add: ";
			cin >> stringValue;

			while (intValidation(stringValue) == true)
			{
				cout << "Invalid value, please try again!" << endl;
				cin.clear();
				cin.ignore();
				cout << endl;
				cout << "Enter a value to add: ";
				cin >> stringValue;
			}

			value = convertToInt(stringValue);

			// validation for unique value in tree
			bool uniqueValue = true;
			List valuesList = tree.listOfAllValues();
			
			for (int i = 1; i <= valuesList.getLength(); i++)
			{
				if (valuesList.get(i) == value)
				{
					uniqueValue = false;
				}
			}

			while (uniqueValue == false)
			{
				cout << "Value is not unique, please try again!" << endl << endl << "Enter a value to add: ";
				cin >> stringValue;

				while (intValidation(stringValue) == true)
				{
					cout << "Invalid value, please try again!" << endl;
					cin.clear();
					cin.ignore();
					cout << endl;
					cout << "Enter a value to add: ";
					cin >> stringValue;
				}

				value = convertToInt(stringValue);
				uniqueValue = true;

				for (int i = 1; i <= valuesList.getLength(); i++)
				{
					if (valuesList.get(i) == value)
					{
						uniqueValue = false;
					}
				}
			}

			tree.insert(value);
			cout << "Value " << value << " is added!";
		}

		else if (option == 3) // Remove a value
		{
			cout << "Enter a value to remove: ";
			cin >> stringValue;

			while (intValidation(stringValue) == true)
			{
				cout << "Invalid value, please try again!" << endl;
				cin.clear();
				cin.ignore();
				cout << endl;
				cout << "Enter a value to add: ";
				cin >> stringValue;
			}

			value = convertToInt(stringValue);
			
			bool removed = tree.remove(value);
			if (removed == false)
			{
				cout << "Value not found, please try again!";
			}
			else
			{
				cout << "Value " << value << " is removed!";
			}
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
			cout << "Invalid option, please try again!"<< endl;
		}
	}

    return 0;
}

