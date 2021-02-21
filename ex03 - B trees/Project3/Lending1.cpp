#include "Lending.h"
//We exercised various operators of the class
istream& operator>>(istream& is, Lending& l)
{
	cout << "enter id name date item ";
	is >> l.id >> l.client >> l.date >> l.code;
	return is;
}


ostream& operator<<(ostream& os, Lending& l)
{
	os << endl << "Lending details: id: " << l.id << " name: " << l.client << " date: " << l.date << " item: " << l.code << endl;
	return os;
}
bool Lending::operator!=(const Lending x)
{
	return(!(id == x.id&&client == x.client&&code == x.code&&date == x.date));
}
bool Lending::operator==(const Lending x)
{
	return(!(*this != x));
}
bool Lending::operator>(const Lending x)
{
	return(date > x.date);
}
bool Lending::operator<(const Lending x)
{
	return(date < x.date);
}
bool Lending::operator>=(const Lending x)
{
	if (date > x.date)
		return true;
	if (date == x.date)
		if (code == x.code)
			if (id == x.id)
				return true;
	return false;
}
bool Lending::operator<=(const Lending x)
{
	if (date < x.date)
		return true;
	if (date == x.date)
		if (code == x.code)
			if (id == x.id)
				return true;
	return false;
}
void Lending::set_date(string str1)
{
	date = str1;
}