#ifndef INFOARETECARTE_HPP_INCLUDED
#define INFOARETECARTE_HPP_INCLUDED

#include <iostream>
#include <sstream>
using namespace std;
/**
Information associée à une arête  (segment rectiligne) joignant 2 lieux d'une carte routière.

On ne stocke que le côut de l'arête, c-à-d sa longueur
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