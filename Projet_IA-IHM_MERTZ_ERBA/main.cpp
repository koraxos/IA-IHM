/**
Test des fonctionnalités de PElement : la classe template représentant des listes linéaires récursives
*/
#include <iostream>
#include <string>
#include <stdlib.h>
#include "Pelement.hpp"
#include "Graphe.hpp"
#include "Arete.hpp"
#include "GElement.h"
#include "Sommet.hpp"

using namespace std;
int main()
{
	GElement e(5);

	cout << "e = " << e << endl << endl;

	Sommet<double> s1(13, 3.1416);
	Sommet<string> s2(25, "aubergine");

	cout << "s1 = " << s1 << endl;
	cout << "s2 = " << s2 << endl << endl;

	Sommet<double> * debut = new Sommet<double>(23, 2.71);
	Sommet<double> * fin = new Sommet<double>(47, 1.41);

	Arete<string, double> a1(18, debut, fin, "melon");

	cout << "a1 = " << a1 << endl << endl;

	Graphe<string, char> g;
	Sommet<char> * so1 = g.creeSommet('A');
	Sommet<char> * so2 = g.creeSommet('B');
	Sommet<char> * so3 = g.creeSommet('C');

	g.creeArete(so1, so2, "myrtille");
	g.creeArete(so2, so3, "champignon");

	cout << "g = " << g << endl;


	char ch; cin >> ch;
	return 0;
}
