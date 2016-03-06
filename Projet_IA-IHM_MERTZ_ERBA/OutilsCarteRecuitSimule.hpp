#ifndef OUTILSCARTERECUITSIMULE_HPP_INCLUDED
#define OUTILSCARTERECUITSIMULE_HPP_INCLUDED

#pragma once
#include "Sommet.hpp"
#include "InfoSommetCarte.hpp"
#include "Arete.hpp"
#include "InfoAreteCarte.hpp"
#include "Graphe.hpp"
#include "algebreLineaire.hpp"

/**
d�finit quelques outils utiles � la gestion d'un graphe repr�sentant une carte routi�re.
Application � la r�solution du probl�me du voyageur de commerce par l'algorithme du recuit simul�
*/
class OutilsCarteRecuitSimule
{
public:
	static double distance(const Sommet<InfoSommetCarte> * s1, const Sommet<InfoSommetCarte> * s2);
	static Arete<InfoAreteCarte, InfoSommetCarte> *  creeArete(Sommet<InfoSommetCarte> * sA, Sommet<InfoSommetCarte> * sB, Graphe<InfoAreteCarte, InfoSommetCarte> & graphe);
};

#endif
