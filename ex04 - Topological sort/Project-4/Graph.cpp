#include <iostream>
#include <string>
#include <list>
#include <functional>
#include "Graph.h"

Vertix::Vertix(string K)
{
	color = white; //marks the color as white - haven't been checked yet
	key = K; //enters the new key that was sent
}

bool Vertix::addE(Vertix* v)
{
	Edge* e = new Edge(this, v); //adding a new edge with the new vertix that was send and using an existing one
	if (findE(e)) //if this edge has been found - it's in the graph
	{
		delete e;
		return false;
	}
	EdgeList.push_back(e); //inserts the new edge to the list of edges we have
	return true; //after it's succesfuly was added
}

bool Vertix::findE(Edge* e)
{
	for (list<Edge*>::iterator it = EdgeList.begin(); it != EdgeList.end(); it++) //runs throgh the list of edges with the new iterator
		if (**it == e) //if the edge we're lookimg for is matching
			return true;
	return false; //when it's not found in the list of edges of the graph we saved
}

bool Vertix::removeEdges(Edge* e)
{
	if (findE(e)) //if this edge is found - is in the graph
	{
		EdgeList.remove(e); //removes the edge e
		delete e; //deletes it
		return true; //when it was deleted
	}
	return false; //if for some reason it wasn't deleted
}



Edge::Edge(Vertix* F, Vertix* S)
{
	this->destination = S; //saves the son that was sent as this' destination
	this->source = F; //saves the father that was sent as this' source
}

bool Edge::operator == (const Edge* e)
{
	if (this->destination->key == e->destination->key) //if they are the same at their destination and key 
		if (this->destination->key == e->destination->key)
			return true;
	return false;
}



Vertix* Graph::findV(string V)
{
	for (list<Vertix*>::iterator it = vertixList.begin(); it != vertixList.end(); it++) //runs through the vertices list we have of the graph
		if (V == (**it).getKey()) //if the keys are the same
			return *it; //returns the pointer itself
	return NULL;
}

bool Graph::addE(string V1, string V2)
{
	Vertix* Ver1 = findV(V1); //saves the first vertix that was send and found
	Vertix* Ver2 = findV(V2); //saves the second vertix that was send and found
	if (((!Ver1) || (!Ver2))) //if ine of the two is null
		return false;
	Edge* E1 = new Edge(Ver1, Ver2); //makes a new edge using the two new vertices
	if ((*Ver1).findE(E1)) //if findE for this vertix returns true
		return false;
	return (*Ver1).addE(Ver2);
}

bool Graph::addV(string V)
{
	Vertix* v = findV(V); //saves the vertix that was found
	if (v) //if it's not null
		return false;
	vertixList.push_back(new Vertix(V)); //enters the vertix that was sent to the vertices list af the graph we saved
	return true;
}

void Graph::printGraph()
{
	for (list<Vertix*>::iterator it = vertixList.begin(); it != vertixList.end(); it++) //runs through the vertices list we have of the graph
	{
		(**it).print(); //prints at this point
		cout << ": ";
		for (list<Edge*>::iterator IT = (**it).EdgeList.begin(); IT != (**it).EdgeList.end(); IT++) //runs through the edges list we have of the graph
		{
			(**IT).destination->print();
			cout << " ";
		}
		cout << endl;
	}
}

list<Vertix*> Graph::DFS()
{
	for (list<Vertix*>::iterator it = vertixList.begin(); it != vertixList.end(); it++)
		if ((**it).color == white) //if it hasn't been visited yet
			DFSVisit(*it); //use DFS-visit to visit it
	return order; //returns the order of the tasts after the topological sort
}

void Graph::DFSVisit(Vertix* V)
{
	V->color = gray; //sets the color as gray that means that it's in the prosses of being visited
	T++; //adding one to the timer fot this jump
	V->d = T; //enters the current time saved in the timer as d- when we first visited the vertix

	for (list<Edge*>::iterator it = V->EdgeList.begin(); it != V->EdgeList.end(); it++)
	{
		if ((**it).destination->color == white) //if the color is white witch means that i hasn't been visited yet
		{
			(**it).destination->pi = V; //changes the pi to be as V
			DFSVisit((**it).destination); //uses DFS-visit to visit this vertix
		}
	}

	V->color = black; //changes the color to back witch means that it was visited
	V->f = ++T; //enters the time's current time plus one for this current jump
	order.push_front(V); //pushes the vertix to the front of the order (the topological sorted vertices list)
}

void Graph::topologicalSort()
{
	for (list<Vertix*>::iterator it = vertixList.begin(); it != vertixList.end(); it++) //runs throug the list of vertices we have of the graph
	{
		(**it).color = white; //sets it as white that means it hasn't been visited yet
		(**it).pi = NULL; //it's null because it's not been prossesed yet
		(**it).d = 0; //sets it as 0 for a starting point
		(**it).f = 0; //sets it as 0 for a starting point
	}

	order.clear(); //makes sure that the list named order is empty 
	DFS(); //starts the DFS algorithem on the graph

	cout << "order: ";
	for (list<Vertix*>::iterator it = order.begin(); it != order.end(); it++) //runs through the order list
	{
		(**it).print(); //prints out the item we're pointing at
		cout << " ";
	}
}

Graph::~Graph()
{
	for (list<Vertix*>::iterator it = vertixList.begin(); it != vertixList.end(); it++) //runs through the vertices list we have of the graph
	{
		for (list<Edge*>::iterator IT = (**it).EdgeList.begin(); IT != (**it).EdgeList.end(); IT++) //runs through the edges list we have of the graph
			if (*IT) //if it's not null
				delete (*IT);
		if (*it) //if it's not null
			delete (*it);
	}
}
