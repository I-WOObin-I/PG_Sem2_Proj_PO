#pragma once
#include "Wilk.h"
using namespace std;

Wilk::Wilk(Swiat* swiat, int x, int y) : Zwierze(swiat, x, y, WILK_SILA, WILK_INIC, WILK_PELNOLETNOSC) {}

bool Wilk::Koliduj(Organizm* somsiad, bool czyAtakuje) {
	return false;
}

void Wilk::dodajPolog() { this->polog = WILK_POLOG; }
Organizm* Wilk::dajPotomka(Wsp n_wsp) {
	Organizm* tmp = new Wilk(swiat, n_wsp.x, n_wsp.y);
	swiat->DodajOrganizm(tmp);
	return tmp;
}
bool Wilk::czyTenSamGatunek(Organizm* o) { if (o->getChar() == WILK_CHAR) { return true; } else return false; }

char Wilk::getChar() { return WILK_CHAR; }
string Wilk::getNazwa() { return WILK_NAZWA; }
