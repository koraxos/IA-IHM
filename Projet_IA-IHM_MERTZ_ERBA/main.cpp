#pragma once

#include <float.h>
#include <math.h>
#include <list>
#include <stdlib.h>
#include <sstream>
#include<fstream>
#include <iostream>
#include <string>
#include <stdlib.h>
#include "Pelement.hpp"
#include "Graphe.hpp"
#include "Arete.hpp"
#include "GElement.h"
#include "Sommet.hpp"
#include "SolutionCout.hpp"
#include "DessinGrapheRecuitSimule.hpp"
#include "OutilsCarteRecuitSimule.hpp"


using namespace std;

#define K 1	// constante pour le test de M�tropolis, telle que K > 0

#define S1 6				// nombre de sommets du graphe g1
#define A1 (S1*(S1-1)/2)	// nombre d'ar�tes du graphe g1 car g1 est complet


/**
r�alise un tirage pseudo-al�atoire dans l'intervalle [a,b]
ATTENTION : Il faut appeler srand() au pr�alable !
*/
inline double tirageAleatoire(const double & a, const double &b)
{
	const static int MAX(100);
	const static double MAX1(99);

	int n = rand() % MAX;	// n est tir� au hasard tel que 0 <= n <= MAX-1
	double x = n / MAX1; // x est un nombre r�el au hasard entre 0 et 1 compris
	return a + (b - a)*x;
}

/**
Repr�sente une mise en oeuvre de l'algorithme heuristique "recuit simul�"
le but est de trouver le minimum de la fonction cout()
S est l'ensemble des solutions ou encore le domaine d'exploration
@param tInitiale : temp�rature initiale
@param tFinale : temp�rature finale telle que tFinale <= tInitiale
@param nombreTentativesMax : nombre maximal de tentatives par palier de temp�rature
@param nombreSuccesMax : nombre maximal de succ�s par palier de temp�rature
@param solutionInitiale : solution initiale du probl�me
@param fonction cout1(...) : permet d'�valuer la qualit� d'une solution, plus le co�t est faible, meilleure est la solution
@param fonction changementAleatoire(...) : construit une nouvelle solution par perturbation al�atoire de la solution courante
@param fonction succ(...) : calcule la temp�rature suivante de la temp�rature courante. Doit v�rifier succ(t) < t, quelque soit t
@return bestSolution : la meilleure solution trouv�e
retourne aussi le co�t de la meilleure soution gr�ce au param�tre coutBestSolution
*/
template <class S>
const SolutionCout<S> recuitSimule(const double & tInitiale, const double & tFinale, const int nombreTentativesMax, const int nombreSuccesMax, const S & solutionInitiale,
	double(*cout1)(const S & solution), const S(*changementAleatoire)(const S & solution), double(*succ)(const double & temperature))
{
	SolutionCout<S>  solutionCourante(solutionInitiale, cout1);
	SolutionCout<S> bestSolution(solutionCourante);
	double t; // temp�rature courante
	for (t = tInitiale; t > tFinale; t = succ(t))
	{	int nombreTentatives, nombreSucces;
		for (nombreTentatives = nombreSucces = 0; nombreTentatives < nombreTentativesMax && nombreSucces < nombreSuccesMax; ++nombreTentatives)
		{
			SolutionCout<S> solutionPrecedente(solutionCourante);
			solutionCourante = solutionCourante.change(changementAleatoire, cout1);
			//cout<< "solution courante = " << solutionCourante << endl;
			if (solutionCourante.cout < solutionPrecedente.cout)  // la solution courante est meilleure que la solution pr�c�dente
			{	++nombreSucces;
				if (solutionCourante.cout < bestSolution.cout)	// la solution courante est meilleure que la meilleure solution trouv�e jusqu'� pr�sent
					bestSolution = solutionCourante;
			}
			else	// co�tCourant >= co�tPr�c�dent. La solution courante n'est pas meilleure que la solution pr�c�dente
			{	double v = tirageAleatoire(0, 1);
				double deltaCout = solutionCourante.cout - solutionPrecedente.cout; // on a deltaCout >= 0
				double metropolis = exp(-K*deltaCout / t);

				if (v < metropolis) ++nombreSucces;		// la solution courante est accept�e bien que moins bonne que la pr�c�dente
				else
					solutionCourante = solutionPrecedente;	// la solution courante est refus�e
			}	// co�tCourant >= co�tPr�c�dent.
		}	 // for, boucle tentatives d'am�liorations
		if (nombreSucces == 0) return bestSolution;		// l'algorithme est stationnaire : il a atteint un minimum, on arr�te tout et on retourne la meilleure solution trouv�e
	}	// for, boucle temp�rature
	return bestSolution;
}




//@param fonction succ(...) : calcule la temp�rature suivante de la temp�rature courante.Doit v�rifier succ(t) < t, quelque soit t
//Fonction succ(t)
// renvoie toujours succ(t) <t

inline double succ(double t)
{
	return 0.99*t;
}

inline double cout_solution(const Graphe<InfoAreteCarte, InfoSommetCarte> & are_sol)
{
	double cout_sol = 0;
	int compteur = 0;
	PElement<Arete<InfoAreteCarte, InfoSommetCarte> > * cout_init = are_sol.lAretes;
	for (compteur = 0; compteur < are_sol.nombreSommets(); compteur++)
	{	// calcul du cout en fonction de la lsie des arr�tes
		cout_sol += cout_init->v->v.cout;
		cout_init = cout_init->s;
	}
	cout << cout_sol << endl;
	return cout_sol;
}


int main()
//int main()
{
	char ch;
	{			//--------------- 1er exemple de graphe ------------------------------

		cout << "construction d'un 1er exemple de graphe complet � 6 sommets" << endl;

		Graphe<InfoAreteCarte, InfoSommetCarte> g1;	// cr�ation du graphe g1 vide

	
		//----------------------- on cr�e les sommets dans g1 -------------------------------------

		Sommet<InfoSommetCarte> * s[S1];
		s[0] = g1.creeSommet(InfoSommetCarte("s0", Vecteur2D(1, 2)));
		s[1] = g1.creeSommet(InfoSommetCarte("s1", Vecteur2D(3, 1)));
		s[2] = g1.creeSommet(InfoSommetCarte("s2", Vecteur2D(5, 2)));
		s[3] = g1.creeSommet(InfoSommetCarte("s3", Vecteur2D(5, 3)));
		s[4] = g1.creeSommet(InfoSommetCarte("s4", Vecteur2D(3, 4)));
		s[5] = g1.creeSommet(InfoSommetCarte("s5", Vecteur2D(1, 3)));
		// cette r�p�tition de 6 instructions pourrait �tre avantageusement remplac�e par une boucle
		// elle a �t� uniquement �t� laiss�e pour am�liorer la lisibilit�



		//----------------------- on cr�e les ar�tes dans g1 --------------------------------------

		Arete<InfoAreteCarte, InfoSommetCarte> * a[A1];

		int i, j;	// indices des sommets
		int k;		// indice de l'ar�te courante

		for (i = 0, k = 0; i < S1; ++i)
		for (j =i+ 1; j < S1; ++j)
		{	double d = OutilsCarteRecuitSimule::distance(s[i], s[j]);  // calcul de la distance du sommet s[i] � s[j]
			a[k++] = g1.creeArete(s[i], s[j], InfoAreteCarte(d));
					// on peut remplacer les 2 lignes pr�c�dentes par l'unique ligne suivante :
			// a[k++] = OutilsCarteRecuitSimule.creeArete(s[i],s[j],g1);
		}
		//--------------- ca y est, g1 est cr�� et complet ----------------------------------
		/*
		ICi � a faire construire la solution initiale
		definir la fonction cout: renvoie le cout d'un chemin eul�rien d'une solutions (liste de sommets)
		definir la fonction changement ale�atoire
		On repr�sente une solution S par une liste des sommets
		dans l'ordre de passage du chemin hamiltonien
		SOlutioncout(listede sommet ... ... ...) on la solution initiale de cette fa�on
		**/

		Arete<InfoAreteCarte, InfoSommetCarte> * Arete_Solution[A1];
		Arete_Solution[0] = g1.getAreteParSommets(s[0], s[1]);// on recupere une arete de cette fa�on

		// Solution initiale
		for (int i = 0; i < g1.nombreSommets() - 1; i++)
		{	Arete_Solution[i]=g1.getAreteParSommets(s[i], s[i + 1]);
		}

		Graphe<InfoAreteCarte, InfoSommetCarte> sol_initiale;
			Sommet<InfoSommetCarte> * sommets[S1];
			sommets[0] = sol_initiale.creeSommet(InfoSommetCarte("s0", Vecteur2D(1, 2)));
			sommets[1] = sol_initiale.creeSommet(InfoSommetCarte("s1", Vecteur2D(3, 1)));
			sommets[2] = sol_initiale.creeSommet(InfoSommetCarte("s2", Vecteur2D(5, 2)));
			sommets[3] = sol_initiale.creeSommet(InfoSommetCarte("s3", Vecteur2D(5, 3)));
			sommets[4] = sol_initiale.creeSommet(InfoSommetCarte("s4", Vecteur2D(3, 4)));
			sommets[5] = sol_initiale.creeSommet(InfoSommetCarte("s5", Vecteur2D(1, 3)));

			int S_C = 0;//Sommet_Courant
			int S_S=0;//Sommet_Suivant
			double d = 0;
			for (i = 0; i < 6; i++)
			{
				S_C = i;
				if (i != 5)
					S_S = S_C + 1;
				else
					S_S = 0;

				d = OutilsCarteRecuitSimule::distance(s[S_C], s[S_S]);
				sol_initiale.creeArete(sommets[S_C], sommets[S_S], InfoAreteCarte(d));
			}
			sol_initiale.lAretes;

			double	cout_final = cout_solution(sol_initiale);
			cout << cout_final << endl;

			SolutionCout< Graphe <InfoAreteCarte, InfoSommetCarte>> meilleur_solution(sol_initiale,cout_solution);
				/*
		list < Arete<InfoAreteCarte, InfoSommetCarte> *> solution_initiale;
		list < Arete<InfoAreteCarte, InfoSommetCarte> *>::const_iterator compteur;
		*/

		
		
		 /*SolutionCout<Graphe<InfoAreteCarte, InfoSommetCarte>> meilleursolution(g1,cout) ;*/
		
	
		// essayer de faire avec lsommets plut�t que liste d'arr�te
		// appeler double d = OutilsCarteRecuitSimule::distance(s[i], s[j]); dans cout
		// pour voir quelque chose du style
		// SolutionCout<tab de sommet>res_init(solution_initiale,cout_solution);


		
		/*
		SolutionCout < list < Arete <InfoAreteCarte, InfoSommetCarte> *>> res(solution_initiale);*/

		//	// ----------------- on affiche sur la console toutes les informations contenues dans g1
		//
		//	cout << "g1 = " << endl << g1 << endl;
		//
		//	cout << "tapez un caract�re, puis ENTER\n"; cin >> ch;

		//	//----------------- on cr�e le fichier texte pour dessiner g1 ------------------------------

		//	string nomFichierDessin = "grapheHexagonalComplet.txt";
		//	ofstream f(nomFichierDessin);							
		//	// ouverture de f en �criture, en mode texte (cf. doc cplusplus.com)
		//	Vecteur2D coinBG(-1, -1), coinHD(5, 5);					
		//	// limites de la fen�tre � visualiser. calcul�es � partir des coordonn�es des sommets
		//	string couleurRepere = "blue";
		//	int rayonSommet = 5;									// unit� :  pixel
		//	string couleurSommets = "red";
		//	string couleurAretes = "blue";

		//	DessinGrapheRecuitSimule::ecritGraphe(f, g1, coinBG, coinHD, couleurRepere, rayonSommet, couleurSommets, couleurAretes);

		//	cout << "le fichier texte de  dessin " << nomFichierDessin << " a �t� cr��" << endl;

		//}	//--------------- fin 1er exemple de graphe ------------------------------

		//cin >> ch;

		system("pause");
		return 0;

	}
	
}
template class SolutionCout<Graphe <InfoAreteCarte, InfoSommetCarte>>;