#ifndef CHROMOSOM_H
#define CHROMOSOM_H

#define ROZMIAR_CHROMOSOMU_BITOWO 21
// dostępny rozmiar chromosomu, max = rozmiar int bitowo
#include <sstream>
#include <iostream>
using namespace std;

/*
 * Klasa reprezentuje Chromosom składający sie
 * z jego zapisu w systemie binarnym oraz
 * oceny z funkcji przystosowania. Udostępnia też
 * metody dostępu do danych prywatnych. 
 */
class Chromosom
{
	int kod;
	float ocena;
	public:
		Chromosom(int kod);
		Chromosom();
		virtual ~Chromosom();
		string toString();
		void set_ocena(float o);
		void set_kod(int o);
		float get_ocena();
		int get_kod();
	private:
		
};

#endif /* CHROMOSOM_H */ 
