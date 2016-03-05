#ifndef SOMMET_HPP_INCLUDED
#define SOMMET_HPP_INCLUDED

/**
Sommet d'un graphe en général
v est l'information associée au sommet : elle dépend de l'application du graphe
*/
template <class T>
class Sommet : public GElement
{
public:
	int degre;
	T v;
	Sommet(const int clef, const T & v) :GElement(clef), degre(0), v(v){}

	operator string () const;
};

template <class T>
Sommet<T>::operator string () const
{
	ostringstream oss;

	oss << "Sommet(" << endl;
	oss << GElement::operator string() << endl;
	oss << "degré = " << degre << endl;
	oss << "v = " << v << endl;
	oss << ")";
	return oss.str();
}

template <class T>
ostream & operator << (ostream & os, const Sommet<T> & sommet)
{
	return os << (string)sommet;
}

#endif