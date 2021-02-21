#pragma once
#include <iostream>
#include <string>
#include <list>
#include <math.h>

using namespace std;

enum Status
{
	nothing,
	full,
	deleted
};

class Client;
class Hclient;
class Hitem;
class Lending;
class Item;



template <class T, class K>
class HashTable
{
protected:
	class  Item //for every item in the table
	{
	public:
		T data;
		K Key;
		Status flag;

		Item() {}
		Item(T d, K k, Status f) { data = d; Key = k; flag = f; }
	};

public:
	int m; //the table's size

	Item* table;

	virtual int h1(K) = 0; //first hashing function
	virtual int h2(K) = 0; //second hashing function

	int getPrime(int num) //returns the smallest prime number that's bigger than the number inserted
	{
		while (true)
		{
			if (isPrime(num))
				return num;
			num++;
		}
	}
	bool isPrime(int num) //checks if the number itselfe is a prime number
	{
		for (int i = 2; i <= num / 2; i++)
		{
			if (num%i == 0)
				return false;
		}
		return true;
	}

	HashTable(int s = 10) //contsructor
	{
		m = getPrime(s);
		table = new Item[m];
		for (int i = 0; i < m; i++)
		{
			table[i].flag = nothing;
		}
	}
	~HashTable() { delete[] table; } //destructor 

	void insert(K key, T data) //inserts a new item to the table
	{
		for (int i = 0; i < m; i++)
		{
			int index = hash(key, i);
			if (table[index].flag != full)
			{
				table[index].flag = full;
				table[index].Key = key;
				table[index].data = data;
				return;
			}
		}
	}
	int hash(K k, int i) { return (h1(k) + i * h2(k)) % m; } //calculats the index by using the hashing functions
	bool remove(K key) //deletes an item from the table
	{
		for (int i = 0; i < m; i++)
		{
			int index = hash(key, i);
			if (table[index].flag == full && table[index].Key == key)
			{
				table[index].flag = deleted;
				return true;
			}
		}
		return false;
	}
	T getItem(K key) //gets the data that is saved in an item in the table by the key
	{
		if (search(key) != -1)
			return table[search(key)].data;
		T temp;
		return temp;
	}
	int search(K key) //searches for an item in the table and returns it's index 
	{
		for (int i = 0; i < m; i++)
		{
			int index = hash(key, i);
			if (table[index].flag == full && table[index].Key == key)
			{
				return index;
			}
		}
		return -1;
	}
	void print() //print all the data that is saved in the table
	{
		for (int i = 0; i < m; i++)
		{
			if (table[i].flag == full)
			{
				cout << table[i].data;
			}
		}
	}
	void update(K key, T data) //updates the data of the item 
	{
		table[search(key)].data = data;
	}
};

class Hitem :public HashTable<Item, string> //Hash table of items with their names as keys
{
public:
	int h1(string k); //hashing function
	int h2(string k); //jumping function

	Hitem(int s = 10) :HashTable(s) {}
};


class Hclient :public HashTable<Client, int> //Hash table of clents with their ID numbers as keys
{
public:
	int h1(int k) { return k % m; } //hashing function
	int h2(int k) { return k % (m - 1) + 1; } //jumping function

	Hclient(int s = 10) :HashTable(s) {}
};

class Item //represents one item in the Gmach
{
public:
	string name;
	list<int> clientsID;

	friend ostream& operator<< (ostream& os, Item& c) { os << c.name; return os; }
	friend istream& operator >> (istream& is, Item & c) { is >> c.name; return is; }
};

class Client //represents one client in the Gmach
{
public:
	string name;
	int ID;
	string phone;
	list<string> lends;

	friend ostream& operator << (ostream& os, Client& c) { os << c.name << " " << c.ID << " " << c.phone << endl; return os; }
	friend istream& operator >> (istream& is, Client & c)
	{
		cout << "please enter name id phone\n";
		is >> c.name >> c.ID >> c.phone;
		return is;
	}
};
class Lending
{
public:
	Hitem hItem;
	Hclient hClient;

	Lending() {} //default constructor
	Lending(int size1, int size2 = 10) :hItem(size1), hClient(size2) {} //constructor

	void addItem(Item item) { hItem.insert(item.name, item); } //adds a new item
	bool delItem(Item item); //deletes an item, returns true if got deleted
	void addClient(Client c) { hClient.insert(c.ID, c); } //adds a new client
	bool delClient(Client c); //deletes a client
	bool addLanding(int ID, string name); //adds the ID number and a name of a new person the is lending this item
	bool delLanding(int ID, string name); //deletes the lending record with the ID nubmer and name entered, returns true if got deleted
	void printLandingItem(Item i); //prints the ID of all the clients who lent this item
};




bool Lending::delItem(Item item)
{
	if (hItem.remove(item.name))
		return true;
	return false;
}

bool Lending::delClient(Client c)
{
	if (hClient.remove(c.ID))
		return true;
	return false;
}

bool Lending::addLanding(int ID, string name)
{
	if (hItem.search(name) != -1 && hClient.search(ID) != -1)
	{
		Item item = hItem.getItem(name);
		Client c = hClient.getItem(ID);
		item.clientsID.push_back(c.ID);
		c.lends.push_back(item.name);
		hItem.update(item.name, item);
		hClient.update(c.ID, c);
		return true;
	}
	return false;
}

bool Lending::delLanding(int ID, string name)
{
	if (hItem.search(name) != -1 && hClient.search(ID) != -1)
	{
		Item item = hItem.getItem(name);
		Client c = hClient.getItem(ID);
		item.clientsID.remove(c.ID);
		c.lends.remove(item.name);
		hItem.update(item.name, item);
		hClient.update(c.ID, c);
		return true;
	}
	return false;
}

void Lending::printLandingItem(Item i)
{
	Item item = hItem.getItem(i.name);
	cout << " ";
	for (list<int>::iterator it = item.clientsID.begin(); it != item.clientsID.end(); it++)
	{

		cout << (*it) << " ";
	}
	if (item.clientsID.empty() == false)
		cout << endl;
}

//Hitem
int Hitem::h1(string k)
{
	int count = 0;
	for (int i = 0; i < k.length(); i++)
	{
		count += k[i] * (int)pow(26, i) % m;
	}
	return count % m;
}

int Hitem::h2(string k)
{
	int count = 0;
	for (int i = 0; i < k.length(); i++)
	{
		count += k[i] * (int)pow(26, i) % (m - 1);
	}
	return count % (m - 1) + 1;
}


class Item;
class Hitem :public HashTable<Item, string> //Hash table of items with their names as keys
{
public:
	int h1(string k) //hashing function
	{
		int count = 0;
		for (int i = 0; i < k.length(); i++)
		{
			count += k[i] * (int)pow(26, i) % m;
		}
		return count % m;
	}
	int h2(string k) //jumping function
	{
		int count = 0;
		for (int i = 0; i < k.length(); i++)
		{
			count += k[i] * (int)pow(26, i) % (m - 1);
		}
		return count % (m - 1) + 1;
	}
	
	Hitem(int s = 10) :HashTable(s) {}
};


class Hclient :public HashTable<Client, int> //Hash table of clents with their ID numbers as keys
{
public:
	int h1(int k) { return k % m; } //hashing function
	int h2(int k) { return k % (m - 1) + 1; } //jumping function

	Hclient(int s = 10) :HashTable(s) {}
};


class Client;
class Item //represents one item in the Gmach
{
public:
	string name;
	list<int> clientsID;

	friend ostream& operator<< (ostream& os, Item& c) { os << c.name; return os; } 
	friend istream& operator >> (istream& is, Item & c) { is >> c.name; return is; }
};

class Client //represents one client in the Gmach
{
public:
	string name;
	int ID;
	string phone;
	list<string> lends;

	friend ostream& operator << (ostream& os, Client& c) { os << c.name << " " << c.ID << " " << c.phone << endl; return os; }
	friend istream& operator >> (istream& is, Client & c)
	{
		cout << "please enter name id phone\n";
		is >> c.name >> c.ID >> c.phone;
		return is;
	}
};


