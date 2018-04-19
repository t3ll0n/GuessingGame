//Tellon Smith
//CMPS 3013 - Program 3
//QATree.h
//This file declares a binary search tree to store qestrions and answers for a guessing game.


#pragma once

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct QANode
{
	string item;
	QANode *leftNode;
	QANode *rightNode;

	//default constructor
	QANode()
	{
		item = "";
		leftNode = NULL;
		rightNode = NULL;
	}

	//parameterized constructor
	QANode(string newItem)
	{
		item = newItem;
		leftNode = NULL;
		rightNode = NULL;
	}
};

class QATree
{
public:
	//default constructor
	QATree();

	//parameterized constructor
	QATree(string newItem);

	//destructor
	~QATree();

	void setCurrentItem(string newItem);
	//Purpose: sets the item of the current pointer
	//Requires: new item to insert
	//Returns: current pointer set with new item
	
	string getCurrentItem();
	//Purpose: returns the item of the current pointer
	//Requires: none
	//Returns: item of the current pointer

	void setLeftNode(string newLeftNode);
	//Purpose: sets the item of the current pointer's left node
	//Requires: new item to insert
	//Returns: current pointer's left node set with new item

	void setRightNode(string newRightNode);
	//Purpose: sets the item of the current pointer's right node
	//Requires: new item to insert
	//Returns: current pointer's right node set with new item

	void traverseLeft();
	//Purpose: moves the current pointer to the current pointer's left node  
	//Requires: none
	//Returns: none

	void traverseRight();
	//Purpose: moves the current pointer to the current pointer's right node  
	//Requires: none
	//Returns: none

	bool isQuestion();
	//Purpose: checks if the current pointer is not an answer (leaf node)
	//Requires: none
	//Returns: false if it is an answer, else true.

	void importTree(ifstream & infile);
	//Purpose: recursively builds the binary tree from an input file in pre-order format
	//Requires: an opened input stream
	//Returns: tree built with data from input file

	void exportTree(ofstream & outfile);
	//Purpose: recursively exports the binary tree to an output file pre-order format
	//Requires: an opened output stream
	//Returns: outfile with information from the bianry tree in pre-order format

	void resetPosition();
	//Purpose: sets the current pointer to the root pointer
	//Requires: none
	//Returns:	current pointer as root pointer

	void incrementUpdates();
	//Purpose: increments the number of updates to the tree
	//Requires: none
	//Returns: none

	bool isUpdated();
	//Purpose: checks if the tree has been updated
	//Requires: none
	//Returns: true if updates > 0, else  false 	

private:
	void destroySubtree(QANode *& root);
	//Purpose: recursively deletes all nodes in the tree
	//Requires: root node
	//Returns: empty tree

	QANode *root;
	QANode *current;
	int updates;
};