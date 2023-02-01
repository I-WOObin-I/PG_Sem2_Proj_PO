#pragma once
#include "Organizm.h"
class Plansza
{
private:
	Organizm** plansza;
	void ZarezerwujPamiec(int szerokosc, int wysokosc);
	void ZwolnijPamiec();
public:
	Plansza(int szerokosc, int wysokosc);
	~Plansza();
};

