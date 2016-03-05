#ifndef GELEMENT_HPP_INCLUDED
#define GELEMENT_HPP_INCLUDED
#include<iostream>
#include<sstream>
using namespace std;
/**
Représente la classe de base des éléments d'un graphe qui peuvent être des sommets ou des arêtes.

A ce niveau, on ne peut que définir que la clef d'un élément.

En effet tout élément d'un graphe est défini par une clef (c-à-d une valeur non nulle et unique)
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