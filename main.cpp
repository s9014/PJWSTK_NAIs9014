#include <iostream>
using namespace std;
#include "chromosom.h"
#include "populacja.h"
#include <math.h>
#include <limits.h>

// prototyp funkcji

void genetyczny(float (*funk)(Chromosom *), int prawd_krzyz, int prawd_mut, string nazwa_funkcji);
float func_ocen_onemax(Chromosom * c);
float func_ocen2(Chromosom * c);
float func_ocen(Chromosom * c);
float licz_wartosc(int kod);

int main() {
	genetyczny(func_ocen,80,10,"y=exp(-(8*x)^2/2)+(0.1*x)^2");
	genetyczny(func_ocen2,80,10,"y=-100 * (x^2 - x) ^2 - (1 - x)^2");
	genetyczny(func_ocen_onemax,80,10,"OneMax");
	return 0;
}

/* Funkcja realizująca algorytm genetyczny
 * przyjmuje na wejście wskaźnik do funkcij
 * oceniającej, prawdopodibieństwa krzyżowania
 * i mutowania oraz nazwę/wzór funkcji w
 * celu poprawnego jej identyfikowania
 */

void genetyczny(float (*funk)(Chromosom *), int prawd_krzyz, int prawd_mut, string nazwa_funkcji) {
	cout<<"----------------------- "<<nazwa_funkcji<<" -------------------------\n";
	int rozmiar_populacji;
	int ilosc_iteracji;
	cout<<"Rozmiar populacji : ";
	cin>>rozmiar_populacji;
	cout<<"Ilość iteracji : ";
	cin>>ilosc_iteracji;
	Populacja * populacja = new Populacja(rozmiar_populacji);
	int wynik_posredni=-RAND_MAX;
	int numer_iteracji_wyniku;
	populacja->losuj_nowa_populacje(METODA_POCZATKOWA);
	populacja->ocen(funk);
	for (int i = 0; i < ilosc_iteracji; i++){
		populacja->losuj_nowa_populacje(METODA_TURNIEJOWA);
		populacja->krzyzowanie(prawd_krzyz);
		populacja->mutowanie(prawd_mut);
		populacja->ocen(funk);
		// sprawdzanie w której iteracji po raz pierwszy pojawił się końcowy wynik
		if (funk(populacja->get_wynik()) != wynik_posredni){
			wynik_posredni=funk(populacja->get_wynik());
			numer_iteracji_wyniku=i;
		}
	}
	cout<<"obliczone maksimum: "<<(int)funk(populacja->get_wynik())<<endl;
	cout<<"Wynik osiągnięto po "<<numer_iteracji_wyniku<<" iteracjach\n";
}


/*
 *	Wzór chromosomu (21 bitów): 
 *	0 0000 00000000 00000000
 * 	czlon 0 - znak +/-
 * 	człon 1 - pozycja przecinka
 *	czlon 2	- wartość licznika
 * 	człon 3 - wartość mianownika
 *	Przykład :
 * 	1 0101  10101110110 10110
 * 	przecinek - 5 poz
 * 	czlon_1 = 1398
 * 	człon_2 = 22
 * 	wynik = + 1398 / 22
 */

 /* Funkcja generuje wartość na podstawie
  * powyższego wzoru chromosomów.
  * Wykorzystywana do przetwarzania chromosomów
  * reprezentujących liczby rzeczywiste.
  */
float licz_wartosc(int kod) {
	float x;
	int poz_przecinka = (kod>>16) & (int)(pow(2,4)-1);
	float licznik = (float)((kod>>poz_przecinka) & ((int)pow(2,16-poz_przecinka)-1));
	float mianownik = (float)(kod & (int)(pow(2,(poz_przecinka))-1));
	if (mianownik==0){
		return 0;
	}
	else{
		if (kod & (1<<(ROZMIAR_CHROMOSOMU_BITOWO-1))){
			return licznik/mianownik;
		}
		else{
			return -licznik/mianownik;
		}
	}
	return x;
}

// poniżej funkcję oceniające dla każdej z wymienionych funkcji
// można oczywiście dodawać kolejne i dalej testować algorytm

float func_ocen(Chromosom * c) {
	float x = licz_wartosc(c->get_kod());
	if (x>8 || x< -8){ // przedział funkcji od -8 do 8
		return INT_MIN;
	}
	float wyn = exp(-powf((8*x),2)/2)+powf((0.1*x),2);
	return wyn;
}

float func_ocen2(Chromosom * c) {
	float x = licz_wartosc(c->get_kod());
	float wyn = -100.0 * powf((powf(x,2.0) - x),2.0) - powf((1.0 - x),2.0);
	return wyn;
}

float func_ocen_onemax(Chromosom * c) {
	int x = c->get_kod();
	return (x & ((int)(pow(2,ROZMIAR_CHROMOSOMU_BITOWO))-1));
}
