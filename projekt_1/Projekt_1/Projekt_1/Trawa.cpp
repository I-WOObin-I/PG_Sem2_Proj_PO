#pragma once
#include "Trawa.h"
using namespace std;

Trawa::Trawa(Swiat* swiat, int x, int y) : Roslina(swiat, x, y, TRAWA_SILA) {}

bool Trawa::Koliduj(Organizm* somsiad, bool czyAtakuje) {
	return false;
}

Organizm* Trawa::dajPotomka(Wsp n_wsp) {
	Organizm* tmp = new Trawa(swiat, n_wsp.x, n_wsp.y);
	swiat->DodajOrganizm(tmp);
	return tmp;
}
bool Trawa::czyTenSamGatunek(Organizm* o) { if (o->getChar() == TRAWA_CHAR) { return true; } else return false; }

char Trawa::getChar() { return TRAWA_CHAR; }
string Trawa::getNazwa() { return TRAWA_NAZWA; }
