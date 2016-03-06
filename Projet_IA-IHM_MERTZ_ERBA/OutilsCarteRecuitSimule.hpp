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
définit quelques outils utiles à la gestion d'un graphe représentant une carte routière.
Application à la résolution du problème du voyageur de commerce par l'algorithme du recuit simulé
*/
class OutilsCarteRecuitSimule
{
public:
	static double distance(const Sommet<InfoSommetCarte> * s1, const Sommet<InfoSommetCarte> * s2);
	static Arete<InfoAreteCarte, InfoSommetCarte> *  creeArete(Sommet<InfoSommetCarte> * sA, Sommet<InfoSommetCarte> * sB, Graphe<InfoAreteCarte, InfoSommetCarte> & graphe);
};

#endif
