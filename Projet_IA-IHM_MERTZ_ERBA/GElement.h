#ifndef GELEMENT_HPP_INCLUDED
#define GELEMENT_HPP_INCLUDED
#include<iostream>
#include<sstream>
using namespace std;
/**
Repr�sente la classe de base des �l�ments d'un graphe qui peuvent �tre des sommets ou des ar�tes.

A ce niveau, on ne peut que d�finir que la clef d'un �l�ment.

En effet tout �l�ment d'un graphe est d�fini par une clef (c-�-d une valeur non nulle et unique)
*/

class GElement
{
public:
	int clef;
	GElement(const int clef);
	operator string() const;
};

ostream & operator << (ostream & os, const GElement& gElement);



#endif