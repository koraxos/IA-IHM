#include "Vecteur2D.hpp"
#include "OutilsCarteRecuitSimule.hpp"

/*static*/ double OutilsCarteRecuitSimule::distance(const Sommet<InfoSommetCarte> * s1, const Sommet<InfoSommetCarte> * s2)
{
	return norme(s1->v.position - s2->v.position);
}
/*static*/ Arete<InfoAreteCarte, InfoSommetCarte> *  OutilsCarteRecuitSimule::creeArete(Sommet<InfoSommetCarte> * sA,
	Sommet<InfoSommetCarte> * sB,
	Graphe<InfoAreteCarte, InfoSommetCarte> & graphe)
{
	return graphe.creeArete(sA, sB, InfoAreteCarte(OutilsCarteRecuitSimule::distance(sA, sB)));
}