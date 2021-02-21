#include "Lending.h"

istream& operator>>(istream& is, Lending& l)
{
	cout << "enter id name date item ";
	is >> l.id >> l.name >> l.date >> l.code;
	return is;
}

ostream& operator<<(ostream& os, Lending& l)
{
	os << endl << "Lending details: id: " << l.id << " name: " << l.name << " date: " << l.date << " item: " << l.code << endl;
	return os;
}
bool Lending::operator!=(const Lending x)
{
	return(!(id == x.id && name == x.name && code == x.code && date == x.date));
}
bool Lending::operator==(const Lending x)
{
	return(!(*this != x));
}

bool Lending::operator>(const Lending x)
{
	if (date == x.date)
		if (code == x.code)
			if (id == x.id)
				return false;
	return(!(*this < x));
}
bool Lending::operator<(const Lending x)
{
	if (date < x.date)
		return true;
	if (date == x.date)
		if (code < x.code)
			return true;
	if (code == x.code)
		if (id < x.id)
			return true;
	return false;

}
bool Lending::operator>=(const Lending x)
{
	if (date > x.date)
		return true;
	if (date == x.date)
		if (code == x.code)
			if (id == x.id)
				return true;
	if (!(*this <= x))
		return true;
	return false;
}

bool Lending::operator<=(const Lending x)
{
	if (date < x.date)
		return true;
	if (date == x.date)
	{
		if (code == x.code)
			if (id <= x.id)
				return true;

		if (code < x.code)
			return true;
	}

	return false;
}

void Lending::set_date(string str1)
{
	date = str1;
}
