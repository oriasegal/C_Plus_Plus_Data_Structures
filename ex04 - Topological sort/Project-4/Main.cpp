/*
Oria Segal
209338193
Question 4
This program sorts a list of tasks in a topological sort using a graph.
*/

#include <iostream>
#include "Graph.h"

using namespace std;

int main()
{
	Graph g;
	try {
		string v1, v2, name;
		int choice;
		cout << "Choose one of the following:\n";
		cout << "1-to add a task\n";
		cout << "2 - to add a priority rule\n";
		cout << "3 - to print all the graph\n";
		cout << "4 - print a recommended task order\n";
		cout << "5 - exit\n";
		do
		{
			cin >> choice;
			switch (choice)
			{

			case 1:cout << "Enter the task you want to add\n";
				cin >> v1;
				if (!g.addV(v1)) cout << "ERROR\n";// add vertex to the graph
				break;
			case 2:cout << "Enter earlier task and the later task\n";
				cin >> v1 >> v2;
				if (!g.addE(v1, v2)) cout << "ERROR\n";// add edge to the graph
				break;
			case 3:
				cout << "The graph:\n";
				g.printGraph();// print the graph
				cout << endl;
				break;
			case 4:
				cout << "The recommended order:\n";
				g.topologicalSort();//topological Sort
				cout << endl;
				break;
			case 5:cout << "byebye";  break;
			default:cout << "ERROR\n"; break;

			}
		} while (choice != 5);
	}
	catch (string s)
	{
		cout << s << endl;
	}
	return 0;
}