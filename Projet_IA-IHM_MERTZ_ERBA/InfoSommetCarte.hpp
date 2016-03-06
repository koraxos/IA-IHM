#ifndef INFOSOMMETCARTE_HPP_INCLUDED
#define INFOSOMMETCARTE_HPP_INCLUDED
#include<string>
#include<sstream>
#include "Vecteur2D.hpp"

class InfoSommetCarte
{
public:
	string nom;
	Vecteur2D position;

	InfoSommetCarte(const string & nom, const Vecteur2D & position) :nom(nom), position(position){}

	operator string() const;
};

ostream & operator << (ostream & os, const InfoSommetCarte & infoSommetCarte);

#endif