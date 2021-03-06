/*
Student Name			: Melvin Ong, Bryan Seah	
Student ID				: S10170601E, S10175683B
Module Group			: P05
Features to highlight	: Validation & displaying of tree algorithm
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
	cout << "[2] Add a new value \n";
	cout << "[3] Remove a value \n";
	cout << "[4] Display values in ascending order \n";
	cout << "[5] Display value of a node \n";
	cout << "[6] Display tree \n"; 
	cout << "[7] Exit \n";
	cout << "----------------------------------------\n";
	cout << "Enter option: ";
}

// returns the number of consecutive numbers that adds => sum
List getNoOfConsecNums(int sum)
{
	int noOfNumbers = 0, currentSum = 0;
	List listOfNumbers;

	for (int i = 1; currentSum < sum; i++)
	{
		currentSum += i;
		noOfNumbers++;
	}

	for (int i = 1; i <= noOfNumbers; i++) // Inserting consecutive numbers into a list 
	{
		listOfNumbers.add(i);
	}

	return listOfNumbers;
}

// function to convert string to integer
int convertToInt(string input)
{
	int integer = stoi(input);
	return integer;
}

// validation for integers input
bool intValidation(string input) 
{
	char c;
	bool error = false;

	for each (c in input) // check each character in string
	{
		if (c != '0' && c != '1' && c != '2' && c != '3' && c != '4' && c != '5' && c != '6' && c != '7' && c != '8' && c != '9') // All other characters except for 0 to 9 are not allowed
		{
			error = true;
		}
	}

	if (input == "0") // Inputs that are only 0 are not allowed (e.g. 0 cannot be a value to be added)
	{
		error = true;
	}

	return error;	
}


int main()
{
	BST tree;
	ItemType value;
	string stringValue;
	string input;
	cout << "Enter a number: "; // Sum of consecutive numbers - to create initial tree
	cin >> input;
	cin.ignore(1000, '\n'); // To ignore spaces

	while (intValidation(input) == true || convertToInt(input) > 100)
	{
		cout << "Input is invalid, please try again!" << endl << endl << "Enter a number: ";
		cin >> input;
		cin.ignore(1000, '\n');
	}

	List listOfValues = getNoOfConsecNums(convertToInt(input));

	// algorithm to ensure the resulting BST do not degenerate into a linked list.
	int middleValue = ceil(listOfValues.getLength()/2.0);

	tree.insert(listOfValues.get(middleValue));
	listOfValues.remove(middleValue);

	for (int i = 1; i <= listOfValues.getLength(); i++) // Inserting consecutive numbers into tree 
	{
		tree.insert(listOfValues.get(i));
	}
	

	int option = 1;
	while (option != 7)
	{
		displayMenu();
		cin >> input;
		cin.ignore(1000, '\n');

		while (intValidation(input) == true )
		{
			cout << "Invalid option, please try again!" << endl;
			displayMenu();
			cin >> input;
			cin.ignore(1000, '\n');
		}

		option = convertToInt(input);

		if (option == 1) // Search for a value and print the path
		{
			cout << "Enter a number to search: ";
			cin >> stringValue;
			cin.ignore(1000, '\n');

			while (intValidation(stringValue) == true)
			{
				cout << "Invalid number, please try again!" << endl;
				cout << endl;
				cout << "Enter a number to search: ";
				cin >> stringValue;
				cin.ignore(1000, '\n');
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
				cout << endl;
				cout << "Enter a value to add: ";
				cin >> stringValue;
				cin.ignore(1000, '\n');
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
					cout << endl;
					cout << "Enter a value to add: ";
					cin >> stringValue;
					cin.ignore(1000, '\n');
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
			cout << "Value " << value << " is added!" << endl;
		}

		else if (option == 3) // Remove a value
		{
			cout << "Enter a value to remove: ";
			cin >> stringValue;

			while (intValidation(stringValue) == true)
			{
				cout << "Invalid value, please try again!" << endl;
				cout << endl;
				cout << "Enter a value to remove: ";
				cin >> stringValue;
				cin.ignore(1000, '\n');
			}

			value = convertToInt(stringValue);
			
			int initialNoOfNodes = tree.countNodes();

			bool removed = tree.remove(value);

			if (removed == false)
			{
				cout << "Value not found, please try again!" << endl;
			}
			else
			{
				cout << "Value " << value << " is removed!" << endl;
			}
		}

		else if (option == 4) // Display values in ascending order
		{
			if (tree.isEmpty()) 
			{
				cout << "Tree is empty!" << endl;
			}
			else 
			{
				cout << "Values in ascending order: ";
				tree.inorder(); // In-order traversal of a tree will always be in ascending order
				cout << endl;
			}
		}

		else if (option == 5) // Display value of a node
		{
			cout << "Enter node's number: ";
			cin >> stringValue;

			while (intValidation(stringValue) == true)
			{
				cout << "Invalid input, please try again!" << endl;
				cout << endl;
				cout << "Enter node's number: ";
				cin >> stringValue;
				cin.ignore(1000, '\n');
			}

			value = convertToInt(stringValue);

			if (tree.displayValueofNode(value) == -1)
			{
				cout << "There are < " << value << " nodes in this tree!" << endl;
			}
			else 
			{
				cout << "Value of Node: " << tree.displayValueofNode(value) << endl;
			}
		}

		else if (option == 6) // Display tree
		{
			cout << endl;
			tree.displayTree();
		}

		else if (option == 7) // Exit application
		{
			cout << "Bye! A+ Please" << endl;
		}

		else 
		{
			cout << "Invalid option, please try again!"<< endl;
		}
	}
    return 0;
}

