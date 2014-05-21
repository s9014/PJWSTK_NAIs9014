#ifndef POPULACJA_H
#define POPULACJA_H

#define METODA_TURNIEJOWA 1
#define METODA_RULETKI 2
#define METODA_POCZATKOWA 3

#define WIELKOSC_TURNIEJU 3

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <math.h>
#include "chromosom.h"
using namespace std;

/*
 *	Klasa definuję populację złożona
 *  z osobników (Chromosomów) oraz
 *  zapewnia metody obsługujące algorytm
 *  genetyczny (losowanie, krzyżowanie,
 *  mutowanie)
 */

class Populacja
{
	vector< Chromosom * > * osobniki;
	int rozmiar_populacji;
	public:
		Populacja(int rozmiar);
		virtual ~Populacja();
		string toString();
		void ocen( float (*funk)(Chromosom*) );
		void losuj_nowa_populacje(int metoda);
		void krzyzowanie(int prawd);
		void mutowanie(int prawd);
		Chromosom * get_wynik();
};

#endif /* POPULACJA_H */ 
