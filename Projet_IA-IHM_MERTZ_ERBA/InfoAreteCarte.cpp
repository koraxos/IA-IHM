#include "InfoAreteCarte.hpp"

InfoAreteCarte::operator string() const
{
	ostringstream oss;

	oss << "coût = " << cout << endl;

	return oss.str();
}


ostream & operator << (ostream & os, const InfoAreteCarte & infoAreteCarte)
{
	return os << (string)infoAreteCarte;
}
