#include <sstream>
#include "Vecteur2D.hpp"

Vecteur2D::operator string() const
{
	ostringstream oss;

	oss << "( " << x << ", " << y << ")";

	return oss.str();
}


ostream & operator << (ostream & os, const Vecteur2D & u)
{
	os << (string)u;
	return os;
}


void fusionne(const double x[], const double y[], int m, Vecteur2D v[])
{
	int i;
	for (i = 0; i <= m; ++i)
		v[i] = Vecteur2D(x[i], y[i]);
}
