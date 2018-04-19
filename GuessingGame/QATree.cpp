//Tellon Smith
//CMPS 3013 - Program 3
//QATree.cpp
//Implements QATree class in QATree.h

#include "QATree.h"
#include <iostream>
#include <fstream>


QATree::QATree()
{
	root = new QANode;
	current = root;
	updates = 0;
}

QATree::QATree(string newItem)
{
	root = new QANode(newItem);
	current = root;
	updates = 0;
}

QATree::~QATree()
{
	destroySubtree(root);
}

void QATree::setCurrentItem(string newItem)
{
	current->item = newItem;
}

string QATree::getCurrentItem()
{
	return current->item;
}

void QATree::setLeftNode(string newLeftNode)
{
	current->leftNode = new QANode(newLeftNode);
}

void QATree::setRightNode(string newRightNode)
{
	current->rightNode = new QANode(newRightNode);
}

void QATree::traverseLeft()
{
	//move to left node
	current = current->leftNode;
}

void QATree::traverseRight()
{
	//mode to right node
	current = current->rightNode;
}

bool QATree::isQuestion()
{
	//if it is a leaf node
	if (current->leftNode == NULL && current->rightNode == NULL)
		return false;
	else
		return true;
}

void QATree::importTree(ifstream & infile)
{
	//variable declaration
	QANode *tempNode;
	string pre;
	string item;

	//read data from file
	getline(infile, pre, ':'); //read first character in file (Q or A)
	getline(infile, item); //read rest of line

	//if it is an answer
	if (pre == "A")
	{
		setCurrentItem(item);
	}
	//if it is a question
	else
	{
		//build subtrees
		setCurrentItem(item); //set the question
		tempNode = current; //keep track of node
		
		//left subtree
		setLeftNode(""); //make left node a blank node
		traverseLeft(); //move to left node
		importTree(infile); //recursive call
		
		//return current to node on this level (recursive level)
		current = tempNode;

		//right subtree
		setRightNode(""); //make right node a blank node
		traverseRight(); //move to right node
		importTree(infile); //recursive call
	}
	//delete tempNode on this level
	tempNode = NULL;
	delete tempNode; 
}

void QATree::exportTree(ofstream & outfile)
{
	//variable declaration
	QANode *tempNode;
	string output;

	//if it is an answer
	if (!isQuestion())
	{
		output = "A:" + getCurrentItem();
		outfile << output << endl;
	}
	//if it is a question
	else
	{
		output = "Q:" + getCurrentItem();
		outfile << output << endl;

		tempNode = current; //keep track of node
		
		//left subtree
		traverseLeft();
		exportTree(outfile);

		//return current to node on this level (recursive level)
		current = tempNode;

		//rightsubtree
		traverseRight();
		exportTree(outfile);
	}
	//delete tempNode on this level
	tempNode = NULL;
	delete tempNode; 
}

void QATree::resetPosition()
{
	current = root;
}

void QATree::incrementUpdates()
{
	updates++;
}

bool QATree::isUpdated()
{
	if (updates > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void QATree::destroySubtree(QANode *& root)
{
	//if node is not empty
	if (root != NULL)
	{
		destroySubtree(root->leftNode); //left substree
		destroySubtree(root->rightNode); //right substree
		delete root;
		root = NULL;
	}
}