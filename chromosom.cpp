#include "chromosom.h"

Chromosom::Chromosom(int kod)
{
	this->ocena = 0;
	this->kod = kod;
	//cout<<"Stworzono chromosom o kodzie: "<<kod<<endl;
}

Chromosom::Chromosom()
{
	this->ocena = 0;
	this->kod = 0;
}

Chromosom ::~Chromosom()
{
	
}

string Chromosom::toString() {
	ostringstream ss;
	ss << "ocena :"<<this->ocena<<" kod:"<<this->kod;
	return ss.str();
}

// poniżej metody dostępu do zmiennych 0biektu

void Chromosom ::set_ocena(float o) {
	this->ocena = o;
}

void Chromosom ::set_kod(int o) {
	this->kod = o;
}

float Chromosom ::get_ocena() {
	return this->ocena;
}

int Chromosom ::get_kod() {
	return this->kod;
}
