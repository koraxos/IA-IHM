/*
* AlgebreLineaire.h
*
*  Created on: 30 juin 2011
*      Author: Dominique
*/

#ifndef ALGEBRELINEAIRE_HPP_INCLUDED
#define ALGEBRELINEAIRE_HPP_INCLUDED

#include <math.h>
#include <iostream>
using namespace std;

template <class T>
inline const T operator - (const T & u, const T & v)
{
	return u + -v;
}

/*
template <class T>
inline const T operator * (const double & a, const T & u)
{
return u * a;
}
*/

template <class T>
inline const T operator / (const T & u, const double & a)
{
	return u * (1 / a);
}

template <class T>
inline const T & operator *=(T & u, const T & v)
{
	u = u * v;

	return u;
}

template <class T>
inline const T & operator -= (T & u, const T & v)
{
	return u += -v;
}

template <class T>
inline const T & operator /= (T & u, const double & a)
{
	return u *= (1 / a);
}

template <class T>
inline double norme(const T & u)
{
	return sqrt(u*u);
}

template <class T>
inline double norme2(const T & u)
{
	return (u*u);
}

/*
template <class T>
inline ostream & operator << (ostream & os, const T & x)
{
os << (string) x;
return os;
}
*/

#endif /* ALGEBRELINEAIRE_H_ */