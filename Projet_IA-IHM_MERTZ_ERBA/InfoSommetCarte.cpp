#include "InfoSommetCarte.hpp"

InfoSommetCarte::operator string() const
{
	ostringstream oss;
	oss << "nom = " << nom << ", position = " << position << endl;

	return oss.str();
}

ostream & operator << (ostream & os, const InfoSommetCarte & infoSommetCarte)
{
	return os << (string)infoSommetCarte;
}