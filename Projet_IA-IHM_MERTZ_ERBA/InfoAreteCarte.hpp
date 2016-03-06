#ifndef INFOARETECARTE_HPP_INCLUDED
#define INFOARETECARTE_HPP_INCLUDED

#include <iostream>
#include <sstream>
using namespace std;
/**
Information associ�e � une ar�te  (segment rectiligne) joignant 2 lieux d'une carte routi�re.

On ne stocke que le c�ut de l'ar�te, c-�-d sa longueur
*/

class InfoAreteCarte
{
public:

	double cout;

	InfoAreteCarte(const double & cout) :cout(cout){}

	operator string() const;
};

ostream & operator << (ostream & os, const InfoAreteCarte & infoAreteCarte);
#endif