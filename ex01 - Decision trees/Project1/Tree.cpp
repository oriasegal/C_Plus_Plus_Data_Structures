#include <iostream>
#include <string>
#include <list>
#include "Tree.h"
using namespace std;

Tree::Tree()
{
	root = NULL; //the root points at NULL
}
Tree::Tree(string val)
{
	root = new DecisionTreeNode(val); //creats a new node with the val as the question
}
Tree::~Tree()
{
	erase(root); //uses the erase function to recursivly delete all the tree
}
void Tree::erase(DecisionTreeNode* R)
{
		list<ValidAnswer>::iterator it = R->getAnswersList().begin(); //creats a pointer named 'it' for the beginning of the answers' list
		while (it != R->getAnswersList().end()) //while the pointer 'it' didn't get to the end of the list
		{
			erase(it->getSon()); //sends it again to the function recursivly
			it++;
		}
		delete R; //deletes the root
}
DecisionTreeNode* Tree::search(string val, DecisionTreeNode* R, DecisionTreeNode* &father)
{
	if (R->getValue() == val)
		return R;
	DecisionTreeNode *T = NULL; 
	list<ValidAnswer>::iterator it = R->getAnswersList().begin(); //creats a pointer named 'it' for the beginning of the answers' list
	while (it != R->getAnswersList().end()) //starts with the 'it' pointer at the start of the list and goes on until it gets to the end
	{
		T = search(val, it->getSon(), father); //if not found yet- sends it again to the function recursivly
		if (T == it->getSon()) //if this root's value (question) is the same as the question we were looking for
			father = R;
		it++;
	}
	return T;
}
void Tree::print(DecisionTreeNode* R, int counter)
{
	for (int i = 0; i < counter; i++) //prints out the necessary anount of spaces befor the answer
		cout << " ";
	cout << R->getValue() << endl; //prints out the root's question
	list<ValidAnswer>::iterator it; //creats a pointer named 'it' for the answers' list
	for (it = R->getAnswersList().begin(); it != R->getAnswersList().end(); it++) //starts with the 'it' pointer at the start of the list and goes on until it gets to the end
	{
		for (int i = 0; i < counter; i++)
			cout << " ";
		cout << ": " << it->getAns() << endl; //prints out the answer with ':' before
		print(it->getSon(), counter + 3);//sends the son again to the function recursivly
	}
}
void Tree::process(DecisionTreeNode *R)
{
	string val; 
	cout << R->getValue() << endl; //prints out the root's value- the question
	if (!(R->isLeaf())) //if this isn't a leaf
	{
		cin >> val; //asks for an answer to add
		for (list<ValidAnswer>::iterator it = R->getAnswersList().begin(); it != R->getAnswersList().end(); it++) //runs trought the tree with a pointer from the begining to the end of the answers' list
		{
			if (val == (*it).getAns()) //if this answer already exists
				process((*it).getSon()); //sends it recursivly to the process function to go lower on the tree
		}
	}
}
bool Tree::addNewSon(string val, string ans, string qus)
{
	DecisionTreeNode* A; //creats a new pointer to point at the tree's nodes
	DecisionTreeNode* B; //creats a new pointer to point at the tree's nodes

	ValidAnswer a(ans, qus); //uses the ValidAnswer constructor to build a new structor of an answer as a

	A = search(val, B); //saves in A the results of the search function that looks for the node with the question as the value that was sent
	if (A == NULL) //if A is NULL- if the question wasn't found
		return false; 
	A->getAnswersList().push_back(a); //pushes the answer to the A pointer and returns true - the son was added
	return true;
}
void Tree::addNewRoot(string val)
{
	root = new DecisionTreeNode(val); //creats a new root with the val that was sent as the question
}
DecisionTreeNode* Tree::search(string val, DecisionTreeNode* &father)
{
	return search(val, root, father); //using the search function recursivly 
}
void Tree::searchAndPrint(string val)
{
	if (val != root->getValue()) //if this isn't the root we're looking for
	{
		DecisionTreeNode* R; //creates a new root to search with
		DecisionTreeNode* P = search(val, R); //creates another new pionter that will have the same value as the one we're looking for
		cout << val << "=>"; //prints out the value- the question of the root we're at right now 
		searchAndPrint(R->getValue()); //uses the searchAndPrint function to recursivly print the rest of the roots on the way to the root we're looking for
	}
	else //if this is the one we're looking for
		cout << val; //prints it's value- it's question
}
void Tree::printTree()
{
	print(root,0); //sends the root to the print function to get printed
}
void Tree::deleteSubTree(string val)
{
	DecisionTreeNode * P; //creats a pointer to the nodes of the tree
	DecisionTreeNode* pointer = search(val, P); //sends the pointer with value of the question that was sent to search for the matching node
	erase(P); //sends the node that was found to be erased
}
