#ifndef DESSINGRAPHE_HPP_INCLUDED
#define DESSINGGRAPHE_HPP_INCLUDED

#include <fstream>
#include "Vecteur2D.hpp"
#include "Graphe.hpp"
#include "InfoAreteCarte.hpp"
#include "InfoSommetCarte.hpp"

using namespace std;
/**

m�thodes n�cessaires pour �crire un graphe-carte routi�re dans un fichier texte de dessin avec visualisation d'un chemin

On suppose toujours que of est d�j� ouvert en �criture seule
*/
class DessinGraphe
{
public:

	static void ecrireEntete(ofstream & of, const string & titre, const string & legende, const string & resume, const Vecteur2D & coinBG, const Vecteur2D & coinHD);
	static void ecritNombrePointsRemarquables(ofstream & of, int nombrePoints);
	static void ecritRepere(ofstream & of, const string & couleur);

	static void ecritNombreCourbes(ofstream & of, int nombreCourbes);
};
#endif