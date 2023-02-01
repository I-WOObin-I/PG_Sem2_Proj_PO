#pragma once
#include "Owca.h"
#include <iostream>
using namespace std;

Owca::Owca(Swiat* swiat, int x, int y) : Zwierze(swiat, x, y, OWCA_SILA, OWCA_INIC, OWCA_PELNOLETNOSC) {}

bool Owca::Koliduj(Organizm* somsiad, bool czyAtakuje) {
	return false;
}

void Owca::dodajPolog() { this->polog = OWCA_POLOG; }
Organizm* Owca::dajPotomka(Wsp n_wsp) {
	Organizm* tmp = new Owca(swiat, n_wsp.x, n_wsp.y);
	swiat->DodajOrganizm(tmp);
	return tmp;
}
bool Owca::czyTenSamGatunek(Organizm* o) { if (o->getChar() == OWCA_CHAR) { return true; } else return false; }

char Owca::getChar() { return OWCA_CHAR; }
string Owca::getNazwa() { return OWCA_NAZWA; }
