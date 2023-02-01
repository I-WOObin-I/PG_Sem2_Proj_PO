#pragma once
#include "Wsp.h"
#include "Organizm.h"
#include "Plansza.h"
#include "LogWalki.h"

#include <list>
#include <time.h>
#include <stack>
#include <iostream>
#include <fstream>

#define LICZBA_LOGOW 10

using namespace std;

class Organizm;
class Plansza;

class Swiat {
private:
	Plansza* plansza;
	list<Organizm*> organizmy;
	stack<Organizm*> organizmyMartwe;
	stack<Organizm*> organizmyNoworodki;
	stack<LogWalki*> logiWalki;

	void AktualizujOrganizmy();
	void UrodzNoworodki();
	void usunMartwe();

public:
	Swiat(int szerokosc, int wysokosc);

	void przejdzTure();
	
	void DodajOrganizm(Organizm* o);
	void usunOrganizm(Organizm* o);
	void wstawDoPlanszy(Organizm* o, Wsp wsp);
	void usunZPlanszy(Wsp wsp);
	void Zeznik();

	void RysujSwiat();
	void RysujLogi();
	void DodajLogWalki(LogWalki* log);

	bool czyWPlanszy(Wsp wsp);
	Wsp losujSasiada(Wsp wsp);
	Wsp znajdzWolnePole(Wsp wsp);
	Wsp rotacjaSasiadow(Wsp wsp, Wsp n_wsp);

	int getSzerokosc();
	int getWysokosc();
	Organizm* getOrg(Wsp wsp);
	int getLiczbeSasiadow();

	void Zapisz();

	~Swiat();
	
};