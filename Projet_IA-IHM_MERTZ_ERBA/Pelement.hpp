#ifndef PELEMENT_HPP_INCLUDED
#define PELEMENT_HPP_INCLUDED

#include <iostream>
#include<sstream>

using namespace std;

template <class T>
class PElement
{
public:
	T * v;
	PElement<T> * s;

	
	/**
	*Retourne le i-ème de la liste de sommet
	*/
	static T * getElement(const int i,  PElement<T> * l);

	/**
	* Ne crée pas de copie de *v.
	Pointe donc sur la donnée originale *v
	* */

	PElement(T * v, PElement<T> * s);


	static const string toString(const PElement<T> * p,
		const char * debut = "( ",
		const char * separateur = ", ",
		const char * fin = ")");

	static int taille(const PElement<T> * l);

	/**
	* efface toute la liste l
	* mais n'efface pas les données *v
	*
	* */
	static void efface1(PElement<T>* & l);

	/**
	* efface toute la liste l
	* et efface toutes les données *v
	*
	* */
	static void efface2(PElement<T>* & l);


	/**
	* Insère * a dans l de telle sorte que l reste ordonnée par ordre croissant (l'élement en tête est le plus petit).
	* Ne réalise pas de copie de *a. En sortie l et a partagent donc physiquement des données.
	*
	* Données : a (l'élément à insérer), l, estPlusPetitOuEgal(la fonction de comparaison))
	* Résultats : l modifiée par l'insertion
	* Hypothèses : on suppose l ordonnée par ordre croissant à l'appel
	*
	* */
	static void insertionOrdonnee(T * a, PElement<T> * & l,
		bool(*estPlusPetitOuEgal)(const T * a1, const T * a2));

	/**
	* retire la 1ère occurrence de a de l si a est présent dans l, sinon ne fait rien
	*
	* L'élément trouvé n'est pas effacé
	*
	* La comparaison est faite sur les pointeurs
	*
	* Données : a, l
	* Résultats : l (éventuellement modifiée), par return : true si l'élément a été trouvé, false sinon
	* */
	static bool retire(const T * a, PElement<T> * & l);


	/**
	* retire l'élément situé en tête de l et le renvoie. Le 1er maillon de l est effacé.
	*
	* l est donc modifiée par l'appel. En sortie l compte un élément de moins.
	* lance une exception Erreur si l == NULL à l'appel
	*
	* */
	static T * depiler(PElement<T> * & l);


	//-------------------------- PElement<T> ---------------------------
};


/**
* Retourn le i-ème sommet de la liste de sommets du Graphe
* @param i : la place dans la liste du sommet a retourné
* @return le sommet à la place i dans la liste
*/
template <class T>
T * PElement<T>::getElement(const int i,  PElement<T> * l)
{
	PElement<T> *  temp=l;
	int compteur = 0;
	
	while (compteur < i){
		temp=temp->s;
		compteur++;
	}
	return  temp->v;
}



template<class T>
ostream& operator <<(ostream & os, const PElement<T> * p)
{
	return os << PElement<T>::toString(p);
}

/**
* Ne crée pas de copie de *v.
Pointe donc sur la donnée originale *v
* */
template <class T>
PElement<T>::PElement(T * v, PElement<T> * s) :v(v), s(s){}

template <class T>
/*static*/ const string PElement<T>::toString(const PElement<T> * p, const char * debut, const char * separateur, const char * fin)
{
	PElement<T> * r;
	ostringstream oss;

	for (r = (PElement<T>*) p, oss << debut; r; r = r->s)
		oss << *(r->v) << separateur;

	oss << fin;
	return oss.str();
}

template <class T>
/* static */ int PElement<T>::taille(const PElement<T> * l)
{
	if (!l) return 0;
	else
		return 1 + PElement<T>::taille(l->s);
}

/**
* efface toute la liste l
* mais n'efface pas les données *v
* */
template <class T>
/* static */ void PElement<T>::efface1(PElement<T>* & l)
{
	if (l)
	{
		PElement<T>::efface1(l->s);
		delete l; l = NULL;
	}
}

/**
* efface toute la liste l
* et efface toutes les données *v
* */
template <class T>
/* static */ void PElement<T>::efface2(PElement<T>* & l)
{
	if (l)
	{
		PElement<T>::efface2(l->s);
		delete l->v; delete l; l = NULL;
	}
}

/**
* Insère * a dans l de telle sorte que l reste ordonnée par ordre croissant (l'élement en tête est le plus petit).
* Ne réalise pas de copie de *a. En sortie l et a partagent donc physiquement des données.
*
* Données : a (l'élément à insérer), l, estPlusPetitOuEgal(la fonction de comparaison))
* Résultats : l modifiée par l'insertion
* Hypothèses : on suppose l ordonnée par ordre croissant à l'appel
*
* */
template<class T>
/*static*/ void PElement<T>::
insertionOrdonnee(T * a, PElement<T> * & l,
bool(*estPlusPetitOuEgal)(const T * a1, const T * a2))
{
	if (!l || estPlusPetitOuEgal(a, l->v))
		l = new PElement<T>(a, l);
	else
		PElement<T>::insertionOrdonnee(a, l->s, estPlusPetitOuEgal);
}

/**
* retire la 1ère occurrence de a de l si a est présent dans l, sinon ne fait rien
*
* L'élément trouvé n'est pas effacé
*
* La comparaison est faite sur les pointeurs
*
* Données : a, l
* Résultats : l (éventuellement modifiée), par return : true si l'élément a été trouvé, false sinon
* */
template<class T>
/*static*/ bool PElement<T>::retire(const T * a, PElement<T> * & l)
{
	if (!l)
		return false;
	else
	if (a == l->v)
	{
		PElement<T> * r = l; l = l->s; delete r;
		return true;
	}
	else
		return PElement<T>::retire(a, l->s);
}

/**
* retire l'élément situé en tête de l et le renvoie. Le 1er maillon de l est effacé.
*
* l est donc modifiée par l'appel. En sortie l compte un élément de moins.
* lance une exception Erreur si l == NULL à l'appel
*
* */
template <class T>
/* static */ T * PElement<T>::depiler(PElement<T> * & l)
{
	if (l== NULL)	
		throw exception("Impossible de dépiler une pile vide");

	T * a = l->v;
	PElement<T> * tete = l;

	l = l->s; delete tete;
	return a;

}

#endif