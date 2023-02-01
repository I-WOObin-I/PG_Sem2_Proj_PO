#include "Plansza.h"






void Plansza::ZarezerwujPamiec(int szerokosc, int wysokosc)
{
	plansza = new Organizm[szerokosc];
}

void Plansza::ZwolnijPamiec()
{
}

Plansza::Plansza(int szerokosc, int wysokosc)
	:plansza(nullptr)
{
}

Plansza::~Plansza()
{
}
