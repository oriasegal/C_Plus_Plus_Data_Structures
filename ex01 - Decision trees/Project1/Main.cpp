/*
Oria Segal
209338193
Question 1
This program is using a decition tree to help customers with their questions.
*/

#include <iostream>
#include <list>
#include <string>
#include "Tree.h"

using namespace std;

int main()
{
	Tree t;
	string father, val, sol;
	char ch;
	cout << "\nDECISION TREE\n";
	cout << "Choose one of the following:" << endl;
	cout << "n: New decision tree" << endl;
	cout << "s: Add a new option for a question" << endl;
	cout << "d: Delete a subtree" << endl;
	cout << "p: Print all tree" << endl;
	cout << "w: Print the path to a decision or a question" << endl;
	cout << "r: Run a process of questions" << endl;
	cout << "e: exit:" << endl;
	do
	{
		cin >> ch;
		switch (ch)
		{
		case 'n':
			cout << "enter the main question (with no space) "; 
			cin >> val; 
			t.addNewRoot(val);
			break;
		case 's':
			cout << "enter the question (with no space) "; 
			cin >> father;
			cout << "enter the new ValidAnswer (with no space) "; 
			cin >> val;
			cout << "enter the new solution(possible a new question, with no space) "; 
			cin >> sol;
			if (t.addNewSon(father, val, sol))
				cout << "success\n"; 
			else 
				cout << "ERROR\n"; 
			break;
		case 'd':
			cout << "enter value of subtree to delete (with no space) "; 
			cin >> val; 
			t.deleteSubTree(val);  
			break;
		case 'p':
			t.printTree();  
			break;
		case 'w':
			cout << "enter a value (with no space) "; 
			cin >> val; 
			t.searchAndPrint(val); 
			cout << endl;  
			break;
		case 'r':
			t.process(); 
			cout << endl;  
			break;
		case 'e':
			cout << "bye "; 
			break;
		default: 
			cout << "ERROR\n";  
			break;
		}
	} while (ch != 'e');
}