#pragma once
#include <string>
#include <time.h>
#include <iostream>

#include "Wsp.h"
#include "Organizm.h"
//#include "KontrolerOrganizmow.h"

#define PUSTE_POLE ' '
#define LICZBA_SASIADOW 8

using namespace std;

class Organizm;
//class KontrolerOrganizmow;

class Plansza {
private:
	int szerokosc;
	int wysokosc;
	Organizm*** koord;
public:
	Plansza(int szerokosc, int wysokosc);

	void WstawOrganizm(Organizm *, Wsp wsp);
	void UsunOrganizm(Wsp wsp);

	void RysujPlansze();
	void WyczyscPlansze();
	
	bool czyWPlanszy(Wsp wsp);
	Wsp losujSasiada(Wsp wsp);
	Wsp znajdzWolnePole(Wsp wsp);

	int getSzerokosc();
	int getWysokosc();
	Organizm* getOrg(Wsp wsp);
	int getLiczbeSasiadow();

	Wsp rotacjaSasiadow(Wsp wsp, Wsp n_wsp);

	~Plansza();
};