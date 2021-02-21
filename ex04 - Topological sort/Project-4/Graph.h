#pragma once
#include <iostream>
#include <string>
#include <list>
#include <functional>
using namespace std;

static int T = 0; //timer

enum Color {black, white, gray};

class Edge;

class Vertix
{
	Color color; //the current color of the vertix
	double d; //the discovery time of this vertix
	double f; //the finishing time the vertix (when black)
	Vertix* pi = NULL; //the father of this vertix- where did we come from, starts at null

	string key; //the task's name
	list<Edge*> EdgeList; //a list of all the edges this vertix conects to

public:
	Vertix(string K); //constructor

	bool addE(Vertix* v); //adds a new edge to the list
	bool findE(Edge* e); //finds the correct edge
	bool destinationExists() { return(!EdgeList.empty()); } //checks if this destination exists in the graph
	void print() { cout << key; } //prints out the vertix's - the task's details
	bool removeEdges(Edge* e); //removers the edges from  the graph
	string getKey() { return key; }//returns the key of the vertix that's connected to this edge

	friend class Edge;
	friend class Graph;
};

class Edge
{
	Vertix* source = NULL; //the source vertix of this edge, starts at null
	Vertix* destination = NULL; //the destination vertix this edge is leading to, starts at null

public:
	Edge(Vertix* F, Vertix* S); //constructor

	bool operator ==(const Edge* e);

	friend class Vertix;
	friend class Graph;
};

class Graph
{
	list <Vertix*> vertixList; //a list of vertices
	list <Vertix*> order; //the order of the tasks - the vertices after the topological sort

public:
	Vertix* findV(string V); //finds the vertix in the graph
	bool addE(string V1, string V2); //adds an edge to the grapg by adding it between two vertices
	bool addV(string V); //adds a vertix to the graph
	void printGraph(); //prints out all the graph

	list <Vertix*> DFS(); //DFS algorithem 
	void DFSVisit(Vertix *V); //DFS-visit algorithem
	void topologicalSort(); //the topological sort algorithem

	~Graph(); //distructor
};