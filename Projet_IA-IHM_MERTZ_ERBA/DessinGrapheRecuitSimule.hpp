#pragma once

#include <fstream>
#include <string>

#include "Graphe.hpp"
#include "InfoSommetCarte.hpp"
#include "InfoAreteCarte.hpp"

using namespace std;
/**
d�finit les outils n�cessaires pour dessiner un graphe repr�sentant une carte routi�re.
But : Application de l'algorithme du recuit simul� � la recherche du probl�me du voyageur de commerce

cette classe d�finit les outils qui ne sont pas d�j� dans DessinGraphe (cf. classe DessinGraphe)
*/
class DessinGrapheRecuitSimule
{
public:
	/**
	rayonSommet est le rayon des sommets sur l'�cran
	*/
	static void ecritSommets(ofstream & of, const Graphe<InfoAreteCarte, InfoSommetCarte> & graphe, const double & rayonSommet, const string & couleur);
	static void ecritAretes(ofstream & of, const Graphe<InfoAreteCarte, InfoSommetCarte> & graphe, const string & couleur);


	/**
	�crit le graphe-carte routi�re sur le fichier texte de dessin of.
	suppose of d�j� ouvert en �criture seule
	rayonSommet est le rayon des sommets sur l'�cran
	*/
	static void ecritGraphe(ofstream & of, Graphe<InfoAreteCarte, InfoSommetCarte> & graphe,
		const Vecteur2D & coinBG, const Vecteur2D & coinHD,
		const string & couleurRepere,
		const double & rayonSommet,
		const string & couleurSommets,
		const string & couleurAretes);
};


