#pragma once
#include <iostream>
#include <string>
#include <list>
using namespace std;

class DecisionTreeNode;
class ValidAnswer;

class DecisionTreeNode
{
public:
	string value; //a question
	list<ValidAnswer> answersList; //a list of pointers to the next level's sons

	DecisionTreeNode* son; //a node in the decition tree that has a question ans a list of answers in it

	DecisionTreeNode(string val) { value = val; } //deafualt constructor- enters the value- the question
	bool isLeaf() { return answersList.empty(); } //checks if the list is empty- if there are no more answers and this is a leaf

	string getValue() { return value; } //gets the value- the question
	list<ValidAnswer>& getAnswersList() { return answersList; } //gets the list of valid answers to the question in this node
};

class ValidAnswer
{
public:
	string ans; //an answer
	DecisionTreeNode* son; //a pointer to the next question (the next son)

	ValidAnswer(string answer, string val) { ans = answer; son = new DecisionTreeNode(val); } //constructor- creates a new list of valid answers

	string getAns() { return ans; } //gets the answer
	DecisionTreeNode* getSon() { return son; } //gets the pointer of the next son, the next question
};

class Tree
{
private:
	DecisionTreeNode * root;

	void erase(DecisionTreeNode* R); //erases the tree one root at a time recursively
	DecisionTreeNode* search(string val, DecisionTreeNode* R, DecisionTreeNode* &father); //searches for a root with the question and returns a pointer to it
	void print(DecisionTreeNode* R, int counter = 0); //prints the tree one root at a time recursively
	void process(DecisionTreeNode *R); //will get the customer a full process- ank him the question and will get his answers

public:
	Tree(); //deafault constroctor
	Tree(string val); //constructor that askes for a string for the value of the root
	~Tree(); //distructor

	bool addNewSon(string val, string ans, string qus); //adds a new son to the existing question
	void addNewRoot(string val); //adds a new root with a new question if didn't find the question
	DecisionTreeNode* search(string val, DecisionTreeNode* &R); //searches for a root with the question and returns a pointer to it
	void searchAndPrint(string val); //searches for a root with the question and prints the route we followed to get to it
	void printTree(); //prints the tree by it's questions and answers' options
	void deleteSubTree(string val); //another erasing function the is calling erase
	void process() { process(root); } //another processing function the is calling process

};