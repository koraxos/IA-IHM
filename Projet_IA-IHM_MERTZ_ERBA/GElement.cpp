#include "GElement.h"

GElement::GElement(const int clef) : clef(clef){}

GElement::operator string() const
{
	ostringstream oss;
	oss << "clef = " << clef;
	return oss.str();
}

ostream & operator << (ostream & os, const GElement& gElement)
{
	return os << (string)gElement;
}
