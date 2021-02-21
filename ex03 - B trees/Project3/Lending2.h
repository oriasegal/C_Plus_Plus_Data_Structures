#pragma once//hodaya fenesh 318630571
#include <iostream>
#include <string>
using namespace std;
class Lending
{
	int id;
	string name;
	string date;
	int code;

public:
	friend istream& operator>>(istream& is, Lending& l);
	friend ostream& operator<<(ostream& os, Lending& l);
	bool operator!=(const Lending x);
	bool operator==(const Lending x);
	bool operator>(const Lending x);
	bool operator<(const Lending x);
	bool operator<=(const Lending x);
	bool operator>=(const Lending x);
	void set_date(string str1);


};