#ifndef GRAPHE_HPP_INCLUDED
#define GRAPHE_HPP_INCLUDED

#include"Sommet.hpp"
#include "Arete.hpp"

using namespace std;

template <class S, class T>
class Graphe
{
protected:
	int prochaineClef;
public:

	PElement< Sommet<T> > * lSommets; // liste de sommets
	PElement< Arete<S, T> > * lAretes; // liste d'arêtes

	/**
	* crée un graphe vide
	* */
	Graphe();

	/**
	* constructeur de copie obligatoire car la classe comporte une partie dynamique
	* */
	Graphe(const Graphe<S, T> & graphe);

	/**
	* opérateur = obligatoire car la classe comporte une partie dynamique
	* */
	const Graphe<S, T> & operator = (const Graphe<S, T> & graphe);

	/**
	* destructeur obligatoire car la classe comporte une partie dynamique
	* */
	~Graphe();

	int nombreSommets() const;
	int nombreAretes() const;

	/**
	* crée un sommet isolé
	* */
	Sommet<T> * creeSommet(const T & info);

	/**
	* crée une arête joignant les 2 sommets debut et fin
	*
	* * met à jour les champs degré de debut et de fin
	* */
	Arete<S, T> *
		creeArete(Sommet<T> * debut, Sommet<T> * fin, const S & info);

	/**
	recherche la liste des paires (voisin, arête) adjacentes de sommet dans le graphe
	*/
	PElement< pair< Sommet<T> *, Arete<S, T>* > >  *
		adjacences(const Sommet<T> * sommet) const;
	operator string() const;

	/**
	* cherche l'arête s1 - s2 ou l'arête s2 - s1 si elle existe
	*
	* DONNEES : s1 et s2 deux sommets quelconques du graphe
	* RESULTATS : l'arête s'appuyant sur s1 et s2 si elle existe, NULL sinon
	*
	* */
	Arete<S, T> * getAreteParSommets(const Sommet<T> * s1, const Sommet<T> * s2) const;


	//---------------------- Graphe ----------------------------------
};



/**
* crée un graphe vide
*
* */
template <class S, class T>
Graphe<S, T>::Graphe() :prochaineClef(0), lAretes(NULL), lSommets(NULL){}

template <class S, class T>
Graphe<S, T>::Graphe(const Graphe<S, T> & graphe)
{
	throw Erreur("pas encore écrit : reste à faire");
}

template <class S, class T>
const Graphe<S, T> & Graphe<S, T>::operator = (const Graphe<S, T> & graphe)
{
	throw Erreur("pas encore écrit : reste à faire");
}

template <class S, class T>
Graphe<S, T>::~Graphe()
{
	PElement< Arete<S, T>>::efface2(this->lAretes);
	PElement<Sommet<T> >::efface2(this->lSommets);
}


/**
* crée un sommet isolé
*
* */
template <class S, class T>
Sommet<T> * Graphe<S, T>::creeSommet(const T & info)
{
	Sommet<T> * sommetCree = new Sommet<T>(prochaineClef++, info);
	lSommets = new PElement< Sommet<T> >(sommetCree, lSommets);

	return sommetCree;
}

/**
* crée une arête joignant les 2 sommets debut et fin
*
* met à jour les champs degre de debut et de fin
* */
template <class S, class T>
Arete<S, T> * Graphe<S, T>::creeArete(Sommet<T> * debut, Sommet<T> * fin, const S & info)
{
	Arete<S, T> * nouvelleArete;

	// ici tester que les 2 sommets sont bien existants dans le graphe
	/*if (!(PElement< Sommet<T> >::appartient(debut, lSommets))) throw exception("début d'arête non défini");
	if (!(PElement< Sommet<T> >::appartient(fin, lSommets))) throw exception("fin d'arête non définie");*/

	nouvelleArete = new Arete<S, T>(prochaineClef++, debut, fin, info);

	lAretes = new PElement< Arete<S, T> >(nouvelleArete, lAretes);
	debut->degre++; fin->degre++;

	return nouvelleArete;
}

template <class S, class T>
int Graphe<S, T>::nombreSommets() const
{
	return PElement< Sommet<T> >::taille(lSommets);
}


template <class S, class T>
int Graphe<S, T>::nombreAretes() const
{
	return PElement< Arete<S, T> >::taille(lAretes);
}


template <class S, class T>
Graphe<S, T>::operator string() const
{
	ostringstream oss;
	oss << "Graphe( \n";
	oss << "prochaine clef = " << this->prochaineClef << endl;
	oss << "nombre de sommets = " << this->nombreSommets() << "\n";

	oss << PElement<Sommet<T> >::toString(lSommets, "", "\n", "");

	oss << "nombre d'arêtes = " << this->nombreAretes() << "\n";

	oss << PElement<Arete<S, T> >::toString(lAretes, "", "\n", "");
	oss << ")";
	return oss.str();
}

template <class S, class T>
ostream & operator << (ostream & os, const Graphe<S, T> & gr)
{
	return os << (string)gr;
}

/**
* cherche l'arête s1 - s2 ou l'arête s2 - s1 si elle existe
*
* DONNEES : s1 et s2 deux sommets quelconques du graphe
* RESULTATS : l'arête s'appuyant sur s1 et s2 si elle existe, NULL sinon
*
* */
template <class S, class T>
Arete<S, T> * Graphe<S, T>::getAreteParSommets(const Sommet<T> * s1, const Sommet<T> * s2) const
{
	PElement<Arete<S, T> > * l;

	for (l = this->lAretes; l; l = l->s)
	if (l->v->estEgal(s1, s2))
		return l->v;

	return NULL;
}



/**
recherche la liste des paires (voisin, arête) adjacentes de sommet dans le graphe
*/
template <class S, class T>
PElement< pair< Sommet<T> *, Arete<S, T>* > >  *  Graphe<S, T>::adjacences(const Sommet<T> * sommet) const
{
	const PElement< Arete<S, T> > * l;

	PElement< pair< Sommet<T> *, Arete<S, T>* > > * r;				// pair< Sommet<T> *, Arete<S,T>* >

	for (l = lAretes, r = NULL; l; l = l->s)

	if (sommet == l->v->debut)
		r = new PElement< pair< Sommet<T> *, Arete<S, T>* > >
		(new pair< Sommet<T> *, Arete<S, T>* >(l->v->fin, l->v), r);
	else
	if (sommet == l->v->fin)
		r = new PElement< pair< Sommet<T> *, Arete<S, T>* > >
		(new pair< Sommet<T> *, Arete<S, T>* >
		(l->v->debut, l->v), r);
	return r;
}

#endif