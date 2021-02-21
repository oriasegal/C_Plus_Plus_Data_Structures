//Hadas Levi 206786519
//Oria Segal 209338193
#include <iostream>
#include"HashTable.h"

using namespace std;

int main()
{
	char ch;
	Item hit;
	Client c;
	Lending ht;
	cout << "Hash Tables\n";
	cout << "\nChoose one of the following" << endl;
	cout << "n: New item" << endl;
	cout << "d: Del an item " << endl;
	cout << "c: New client" << endl;
	cout << "l: Add a Landing " << endl;
	cout << "j: Dell a Landing " << endl;
	cout << "*: Print clients list of an item " << endl;
	cout << "e: Exit" << endl;
	do
	{
		cin >> ch;
		switch (ch)
		{
		case 'n':cout << "enter item name" << endl;  cin >> hit; ht.addItem(hit);  break;
		case 'd':cout << "enter item name" << endl; cin >> hit.name; if (!ht.delItem(hit)) cout << "ERROR";  break;
		case 'c':
			cin >> c; ht.addClient(c); break;
		case 'l': cout << "enter client id and item name ";
			cin >> c.ID >> hit.name; if (!ht.addLanding(c.ID, hit.name)) cout << "ERROR"; break;
		case 'j': cout << "enter client id and item name ";
			cin >> c.ID >> hit.name; if (!ht.delLanding(c.ID, hit.name)) cout << "ERROR"; break;
		case '*': cout << "enter item name ";  cin >> hit.name; ht.printLandingItem(hit); break;
		case 'e':cout << "bye "; break;
		default: cout << "ERROR ";  break;
		}
	} while (ch != 'e');
	return 0;
}