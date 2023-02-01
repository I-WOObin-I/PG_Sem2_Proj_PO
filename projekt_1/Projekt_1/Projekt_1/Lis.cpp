#pragma once
#include "Lis.h"
using namespace std;

Lis::Lis(Swiat* swiat, int x, int y) : Zwierze(swiat, x, y, LIS_SILA, LIS_INIC, LIS_PELNOLETNOSC) {}

void Lis::Akcja() {

	Wsp n_wsp = swiat->losujSasiada(this->wsp);
	for (int i = 0; i < swiat->getLiczbeSasiadow(); i++) {
		if (swiat->getOrg(n_wsp) == NULL || swiat->getOrg(n_wsp)->getS() <= this->sila) { break; }
		n_wsp = swiat->rotacjaSasiadow(this->wsp, n_wsp);
	}

	this->inicjujKolizje(n_wsp);
}
bool Lis::Koliduj(Organizm* somsiad, bool czyAtakuje) {
	return false;
}

void Lis::dodajPolog() { this->polog = LIS_POLOG; }
Organizm* Lis::dajPotomka(Wsp n_wsp) {
	Organizm* tmp = new Lis(swiat, n_wsp.x, n_wsp.y);
	swiat->DodajOrganizm(tmp);
	return tmp;
}
bool Lis::czyTenSamGatunek(Organizm* o) { if (o->getChar() == LIS_CHAR) { return true; } else return false; }

char Lis::getChar() { return LIS_CHAR; }
string Lis::getNazwa() { return LIS_NAZWA; }
