#pragma once
#include "Zolw.h"
using namespace std;

Zolw::Zolw(Swiat* swiat, int x, int y) : Zwierze(swiat, x, y, ZOLW_SILA, ZOLW_INIC, ZOLW_PELNOLETNOSC) {}

void Zolw::Akcja() {
	int tmp = rand() % 100;
	if (tmp < SZANSA_NA_RUCH) {
		Wsp n_wsp = swiat->losujSasiada(this->wsp);
		this->inicjujKolizje(n_wsp);
	}
}
bool Zolw::Koliduj(Organizm* somsiad, bool czyAtakuje) {
	if (czyAtakuje == false && this->getS() < somsiad->getS() && somsiad->getS() < SILA_ODBICIA) { return true; }
	else { return false; }
}

void Zolw::dodajPolog() { polog = ZOLW_POLOG; }
Organizm* Zolw::dajPotomka(Wsp n_wsp) {
	Organizm* tmp = new Zolw(swiat, n_wsp.x, n_wsp.y);
	swiat->DodajOrganizm(tmp);
	return tmp;
}
bool Zolw::czyTenSamGatunek(Organizm* o) { if (o->getChar() == ZOLW_CHAR) { return true; } else return false; }

char Zolw::getChar() { return ZOLW_CHAR; }
string Zolw::getNazwa() { return ZOLW_NAZWA; }
