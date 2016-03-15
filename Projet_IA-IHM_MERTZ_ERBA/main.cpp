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

#define K 1	// constante pour le test de Métropolis, telle que K > 0


#define S1 6				// nombre de sommets du graphe g1
#define A1 (S1*(S1-1)/2)	// nombre d'arêtes du graphe g1 car g1 est complet


/**
réalise un tirage pseudo-aléatoire dans l'intervalle [a,b]
ATTENTION : Il faut appeler srand() au préalable !
*/
inline double tirageAleatoire(const double & a, const double &b)
{
	const static int MAX(100);
	const static double MAX1(99);

	int n = rand() % MAX;	// n est tiré au hasard tel que 0 <= n <= MAX-1
	double x = n / MAX1; // x est un nombre réel au hasard entre 0 et 1 compris
	return a + (b - a)*x;
}

/**
Représente une mise en oeuvre de l'algorithme heuristique "recuit simulé"
le but est de trouver le minimum de la fonction cout()
S est l'ensemble des solutions ou encore le domaine d'exploration
@param tInitiale : température initiale
@param tFinale : température finale telle que tFinale <= tInitiale
@param nombreTentativesMax : nombre maximal de tentatives par palier de température
@param nombreSuccesMax : nombre maximal de succès par palier de température
@param solutionInitiale : solution initiale du problème
@param fonction cout1(...) : permet d'évaluer la qualité d'une solution, plus le coût est faible, meilleure est la solution
@param fonction changementAleatoire(...) : construit une nouvelle solution par perturbation aléatoire de la solution courante
@param fonction succ(...) : calcule la température suivante de la température courante. Doit vérifier succ(t) < t, quelque soit t
@return bestSolution : la meilleure solution trouvée
retourne aussi le coût de la meilleure soution grâce au paramètre coutBestSolution
*/

template <class S>
const SolutionCout<S> recuitSimule(const double & tInitiale, const double & tFinale, const int nombreTentativesMax, const int nombreSuccesMax, const S & solutionInitiale,
	double(*cout1)(const S & solution), const S(*changementAleatoire)(const S & solution), double(*succ)(const double & temperature))
{
	SolutionCout<S>  solutionCourante(solutionInitiale, cout1);
	SolutionCout<S> bestSolution(solutionCourante);
	double t; // température courante
	for (t = tInitiale; t > tFinale; t = succ(t))
	{	int nombreTentatives, nombreSucces;
		for (nombreTentatives = nombreSucces = 0; nombreTentatives < nombreTentativesMax && nombreSucces < nombreSuccesMax; ++nombreTentatives)
		{
			SolutionCout<S> solutionPrecedente(solutionCourante);
			solutionCourante = solutionCourante.change(changementAleatoire, cout1);
			//cout<< "solution courante = " << solutionCourante << endl;
			if (solutionCourante.cout < solutionPrecedente.cout)  // la solution courante est meilleure que la solution précédente
			{	++nombreSucces;
				if (solutionCourante.cout < bestSolution.cout)	// la solution courante est meilleure que la meilleure solution trouvée jusqu'à présent
					bestSolution = solutionCourante;
			}
			else	// coûtCourant >= coûtPrécédent. La solution courante n'est pas meilleure que la solution précédente
			{	double v = tirageAleatoire(0, 1);
				double deltaCout = solutionCourante.cout - solutionPrecedente.cout; // on a deltaCout >= 0
				double metropolis = exp(-K*deltaCout / t);

				if (v < metropolis) ++nombreSucces;		// la solution courante est acceptée bien que moins bonne que la précédente
				else
					solutionCourante = solutionPrecedente;	// la solution courante est refusée
			}	// coûtCourant >= coûtPrécédent.
		}	 // for, boucle tentatives d'améliorations
		if (nombreSucces == 0) return bestSolution;		// l'algorithme est stationnaire : il a atteint un minimum, on arrête tout et on retourne la meilleure solution trouvée
	}	// for, boucle température
	return bestSolution;
}




/* Fonction succ(t)
*	Doit vérifier succ(t) < t, quelque soit t
* renvoie toujours succ(t) <t
* @param t la température courante
* @return la température refroidie
*/
inline double succ(double t)
{
	return 0.99*t;
}
/**
	Renvoie un entier aléatoire entre deb et fin 
	@param deb:début de l'intervalle
	@param fin:fin de l'intervalle
**/
int randomizer(int deb, int end)
{	return rand() % (end - deb) + deb;
}
/*
=======================================
		CETTE FONCTION NE MARCHE PAS ET EST PROBABLEMENT FAUSSE
		BEAUCOUP DE CODE DE TEST DIVERSE SUBSISTE MAIS NE FONT PAS PARTIE DE LA VERSION FINALE
		QUI SERA PRÊTE POUR LA SOUTENANCE
========================================
La fonction changement aléatoire sert à changer la nature d'une solution pour la rendre différentre mais restants dans l'ensemble général des solutions
c'est grâce aux critères aléatoires de cette fonction que l'algorithme de recuit simulé peut fonctionner(stochastiquement) dans son choix de meilleur solution
@param solution: la solution à changer aléatoirement
@return la nouvelle solution changer aléatoirement
*/
inline const Graphe <InfoAreteCarte, InfoSommetCarte> changementAleatoire(const  Graphe <InfoAreteCarte, InfoSommetCarte> &solution)
{	Graphe <InfoAreteCarte, InfoSommetCarte> solution_to_return;
	PElement<Arete<InfoAreteCarte, InfoSommetCarte> > * list_init_ar = solution.lAretes;
	PElement<Arete<InfoAreteCarte, InfoSommetCarte> > * list_temp_ar;
	PElement<Sommet<InfoSommetCarte>> * liste_init_sommet = solution.lSommets;

	bool trouve = true;
	/*Ldeb, temp_suivant_deb, fin, tem_suivant_fin
	on besoin d'être initalisé car ils sont utilisés dans des instructions imbriqués*/
	int set_size = liste_init_sommet->taille(liste_init_sommet);
	double rand1 = randomizer(0, set_size);
	double rand2 = randomizer(0, set_size);

	while( (rand1 == rand2) || (rand2 == rand1 + 1) || (rand1 == rand2 + 1))
	{	rand2 = randomizer(0, set_size);
	}	
	return solution_to_return;
}
/*
 cout_solution : Permet de calculer le cout d'une solution selon la somme du poids de ses arrêtes
@param Graphe_are_sol : Représente Le graphe d'arrête - solution 
@return la somme du poids des arrêtes , qui représente bien le cout
*/
inline double cout_solution(const Graphe<InfoAreteCarte, InfoSommetCarte> & Graphe_are_solare_sol)
{
	double cout_sol = 0;
	int compteur = 0;
	PElement<Arete<InfoAreteCarte, InfoSommetCarte> > * aretes_sol = Graphe_are_solare_sol.lAretes;
	for (compteur = 0; compteur <Graphe_are_solare_sol.nombreSommets(); compteur++)
	{	// calcul du cout en fonction de la liste des arrêtes
		cout_sol += aretes_sol->v->v.cout;
		aretes_sol = aretes_sol->s;
	}
	return cout_sol;
}

int main()
//int main()
{
	char ch;
	{			//--------------- 1er exemple de graphe ------------------------------

		cout << "construction d'un 1er exemple de graphe complet à 6 sommets" << endl;

		Graphe<InfoAreteCarte, InfoSommetCarte> g1;	// création du graphe g1 vide
			
		//----------------------- on crée les sommets dans g1 -------------------------------------

		Sommet<InfoSommetCarte> * s[S1];
		s[0] = g1.creeSommet(InfoSommetCarte("s0", Vecteur2D(1, 2)));
		s[1] = g1.creeSommet(InfoSommetCarte("s1", Vecteur2D(3, 1)));
		s[2] = g1.creeSommet(InfoSommetCarte("s2", Vecteur2D(5, 2)));
		s[3] = g1.creeSommet(InfoSommetCarte("s3", Vecteur2D(5, 3)));
		s[4] = g1.creeSommet(InfoSommetCarte("s4", Vecteur2D(3, 4)));
		s[5] = g1.creeSommet(InfoSommetCarte("s5", Vecteur2D(1, 3)));
		// cette répétition de 6 instructions pourrait être avantageusement remplacée par une boucle
		// elle a été uniquement été laissée pour améliorer la lisibilité
		
		//----------------------- on crée les arêtes dans g1 --------------------------------------

		Arete<InfoAreteCarte, InfoSommetCarte> * a[A1];

		int i, j;	// indices des sommets
		int k;		// indice de l'arête courante

		for (i = 0, k = 0; i < S1; ++i)
		for (j =i+ 1; j < S1; ++j)
		{	double d = OutilsCarteRecuitSimule::distance(s[i], s[j]);  // calcul de la distance du sommet s[i] à s[j]
			a[k++] = g1.creeArete(s[i], s[j], InfoAreteCarte(d));
					// on peut remplacer les 2 lignes précédentes par l'unique ligne suivante :
			// a[k++] = OutilsCarteRecuitSimule.creeArete(s[i],s[j],g1);
		}
		//--------------- ca y est, g1 est créé et complet ----------------------------------

		/**
		Creation de la solution Initiale
		*/
		Graphe<InfoAreteCarte, InfoSommetCarte> sol_initiale;
			Sommet<InfoSommetCarte> * sommets[S1];
			sommets[0] = sol_initiale.creeSommet(InfoSommetCarte("s0", Vecteur2D(1, 2)));
			sommets[1] = sol_initiale.creeSommet(InfoSommetCarte("s1", Vecteur2D(3, 1)));
			sommets[2] = sol_initiale.creeSommet(InfoSommetCarte("s2", Vecteur2D(5, 2)));
			sommets[3] = sol_initiale.creeSommet(InfoSommetCarte("s3", Vecteur2D(5, 3)));
			sommets[4] = sol_initiale.creeSommet(InfoSommetCarte("s4", Vecteur2D(3, 4)));
			sommets[5] = sol_initiale.creeSommet(InfoSommetCarte("s5", Vecteur2D(1, 3)));

			/*creation du chemin eulérien 0-1-2-3-4-5-0*/
			int S_C = 0;//Sommet_Courant
			int S_S=0;//Sommet_Suivant
			double d = 0;
			for (i = 0; i < 6; i++)
			{	S_C = i;
				if (i != 5)
					S_S = S_C + 1;
				else
					S_S = 0;

				d = OutilsCarteRecuitSimule::distance(s[S_C], s[S_S]);
				sol_initiale.creeArete(sommets[S_C], sommets[S_S], InfoAreteCarte(d));
			}
			/**
			test fonction cout
			*/
			double	cout_final = cout_solution(sol_initiale);
			cout << cout_final << endl;
			/*test avec l'objet SolutionCout*/
	SolutionCout< Graphe <InfoAreteCarte, InfoSommetCarte>> meilleur_solution(sol_initiale,cout_solution);
	meilleur_solution.change(changementAleatoire, cout_solution);
	/*
	changementAleatoire, à priori ne fonctionne pas , il est possible qu'une boucle infinie y soit présente
	ce problème sera réglé pour la soutenance normalement
	*/

		system("pause");
	}
	
}