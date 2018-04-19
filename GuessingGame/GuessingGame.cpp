//-----------------------------------------------------------------------------------------------------
//
// Name: Tellon Smith
//
// Course: CS 3013 - Advanced Structures and Algorithms, Spring 16, Dr. Johnson
//
// Program Assignment : #3
//
// Due Date: Thursday, Mar. 31, 2016, 2PM
//
// Purpose: This program uses a binary search tree to implement a guessing game. The program will
//          load a default database with a few simple questions it will ask the user or it can load
//          a custom or updated database. If the guess is incorrect the program will update its 
//          database by asking the user a series of questions.
//
//-----------------------------------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <string>
#include "QATree.h"

using namespace std;

void openInputFile(ifstream & infile);
//Purpose: opens an input stream
//Requires: infile
//Returns: an opened input stream

void openOutputFile(ofstream & outfile);
//Purpose: opens an output stream
//Requires: outfile
//Returns: an opened output stream

void printHeading();
//Purpose: prints headings
//Requires: opened output stream
//Returns: outfile with headings appended to it

void printWelcomeMessage();
//Purpose: prints a welcome message
//Requires: opened output stream
//Returns: outfile with welcome message appended to it

void printExitMessage();
//Purpose: prints an exit message
//Requires: opened output stream
//Returns: outfile with exit message appended to it

void importDatabase(ifstream & infile, QATree & tree);
//Purpose: imports a databse with questions and answers in pre-order format 
//Requires: infile, tree
//Returns: tree loaded with data from infile

void exportDatabase(ofstream & outfile, QATree & tree);
//Purpose: exports the tree to an outfile in pre-order format
//Requires: outfile, tree
//Returns: outfile with data from the tree in pre-order format

void runAgain(bool & repeat);
//Purpose: asks the user if they would like to play again
//Requires: repeat (bool)
//Returns: repeat (bool) with true or false 

char getYesNo();
//Purpose: ask the to enter 'y' for yes and 'n' for no
//Requires: none
//Returns: char (y or n)

void query(QATree & tree);
//Purpose: asks the user questions in the tree
//Requires: tree
//Returns: the questions in the tree

void guess(QATree & tree);
//Purpose: makes a guess of what the user is thinking of
//Requires: tree
//Returns: a guess of what the user is thinking of

void updateTree(QATree & tree);
//Purpose: updates the tree with what the user was thinking of
//Requires: tree
//Returns: tree updated with what the user was thinking of

void main()
{
	//variable declarations
	ifstream infile;
	ofstream outfile;
	QATree tree;
	bool repeat = true;

	//begin process
	printHeading();
	printWelcomeMessage();
	importDatabase(infile, tree); //read data from input file
	
	while (repeat)
	{
		query(tree); //ask the user questions
		runAgain(repeat); //ask user if they would like to play again
	}
	
	exportDatabase(outfile, tree); //save database
	printExitMessage();

	system("pause");
}

void printHeading()
{
	cout << "\nName: Tellon Smith" << endl;
	cout << "Course: CS 3013 - Advanced Structures and Algorithms, Spring 16, Dr. Johnson" << endl;
	cout << "Program Assignment: #3" << endl;
	cout << "Due Date: Thursday, Mar. 31, 2016, 2PM" << endl;
	cout << "Purpose: This program uses a binary search tree to implement a guessing game." << endl;
	cout << "The program will load a default database with a few simple questions it will" << endl;
	cout << "ask the user or it can load a custom or updated database. If the guess is" << endl;
	cout << "incorrect the program will update its database by asking the user a series" << endl;
	cout << "of questions" << endl;
}

void printWelcomeMessage()
{
	cout << "\nWelcome to the Guessing Game Program!" << endl;
	cout << "\n----------------------------------------------------------------------" << endl;
	cout << "                     Guessing Game Program" << endl;
	cout << "----------------------------------------------------------------------" << endl;
}

void printExitMessage()
{
	cout << "\nThank you for using the Guessing Game Program... Goodbye!" << endl;
}

void openInputFile(ifstream & infile)
{
	char inFileName[40];

	//open input stream
	cout << "\nEnter the database filename (enter 'default.txt' to use the default database): ";
	cin >> inFileName;
	infile.open(inFileName);

	//display error message if the specified file cannot be opened
	if (!infile)
	{
		cout << "\nERROR: cannot open the specified file. please run the program again." << endl;
		system("pause");
		exit(1);
	}
}

void openOutputFile(ofstream & outfile)
{
	char outFileName[40];

	//open output stream
	cout << "Enter a filename to save the updated database to: ";
	cin >> outFileName;
	outfile.open(outFileName);
}

void importDatabase(ifstream & infile, QATree & tree)
{
	openInputFile(infile); //open input file
	tree.importTree(infile); //import from input file
	infile.close(); //closes the input file
	tree.resetPosition(); //reset position of pointer 
	cout << "\nDatabase loaded successfully! Think of something and I would try to guess it \
:)\n" << endl;
}

void exportDatabase(ofstream & outfile, QATree & tree)
{
	char userInput;

	//if tree is updated
	if (tree.isUpdated())
	{
		cout << "The database has been updated... Would you like to export it? (y/n)" << endl;
		userInput = getYesNo();
		
		//if user wants to export
		if (userInput == 'y')
		{
			openOutputFile(outfile); //open output file
			tree.exportTree(outfile); //expor to output file
			outfile.close(); //close output file
			tree.resetPosition(); //reset position of pointer
			cout << "\nDatabase exported!" << endl;
		}
		//if user does not want to export
		else
		{
			cout << "Database will not be exported." << endl;
		}
	}
	//if tree if not updated
	else
	{
		cout << "Database not updated... Export not needed." << endl;
	}
}

void runAgain(bool & repeat) 
{
	char userInput;

	cout << "would you like to play again? (y/n)" << endl;
	userInput = getYesNo();

	//if user does not want to play again
	if (userInput == 'n')
	{
		repeat = false;
	}
	//if user wants to play again
	else
	{
		repeat = true;
	}
}

char getYesNo()
{
	char userInput;
	bool validInput = false;

	//continues to prompt until user enters a valid input
	while (!validInput)
	{
		cin >> userInput;
		userInput = tolower(userInput);
		
		if (userInput != 'y' && userInput != 'n')
		{
			cout << "invalid option... please enter 'y' for yes and 'n' for no." << endl;
		}
		else
		{
			validInput = true;
		}
	}
	return userInput;
}

void query(QATree & tree)
{
	char UserInput;

	//if it is a question
	if (tree.isQuestion())
	{
		cout << tree.getCurrentItem() + " (y/n)" << endl;
		UserInput = getYesNo();
		
		//goes to left subtree is user says yes
		if (UserInput == 'y')
		{
			tree.traverseLeft();
			query(tree);
		}
		//goes to right subtree if user says no
		else
		{
			tree.traverseRight();
			query(tree);
		}
	}
	//if it is an answer
	else
		guess(tree);
}

void guess(QATree & tree)
{
	char userInput;

	cout << "Are you thinking of a(n) " + tree.getCurrentItem() + "? (y/n)" << endl;
	userInput = getYesNo();
	
	//if user says yes
	if (userInput == 'y')
	{
		cout << ("The Computer Wins!\n");
	}
	//if user says no
	else
	{
		updateTree(tree); //update tree with what user was thinking of
	}
	tree.resetPosition(); //reset position of pointer
}

void updateTree(QATree & tree)
{

	string userObject;
	char userQuestion[100];
	char userInput;

	cout << "You win!" <<endl;
	cout << "What were you thinking of?" << endl;
	cin >> userObject;
	cout << "Please enter a question to distinguish a(n) " + tree.getCurrentItem() + " from a(n) " + 
		userObject + ":" << endl;
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); //discard characters until newline is found
	cin.getline(userQuestion,250);
	cout << "If you were thinking of a(n) " + userObject + ", what would the answer to that question \
be? (y/n)" << endl;
	userInput = getYesNo();

	//if the answer is yes
	if (userInput == 'y')
	{
		tree.setRightNode(tree.getCurrentItem());
		tree.setLeftNode(userObject);
	}
	//if the answer is no
	else
	{
		tree.setLeftNode(tree.getCurrentItem());
		tree.setRightNode(userObject);
	}

	tree.setCurrentItem(userQuestion); //set current item to user question
	cout << "Thank you! My database has been updated" << endl;
	tree.incrementUpdates(); //increment updates to tree
}