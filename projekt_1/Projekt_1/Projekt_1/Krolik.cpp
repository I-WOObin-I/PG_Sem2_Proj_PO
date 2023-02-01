#pragma once
#include "Krolik.h"
#include <iostream>
using namespace std;

Krolik::Krolik(Swiat* swiat, int x, int y) : Zwierze(swiat, x, y, KROLIK_SILA, KROLIK_INIC, KROLIK_PELNOLETNOSC) {}

bool Krolik::Koliduj(Organizm* somsiad, bool czyAtakuje) {
	return false;
}

void Krolik::dodajPolog() { this->polog = KROLIK_POLOG; }
Organizm* Krolik::dajPotomka(Wsp n_wsp) {
	Organizm* tmp = new Krolik(swiat, n_wsp.x, n_wsp.y);
	swiat->DodajOrganizm(tmp);
	return tmp;
}
bool Krolik::czyTenSamGatunek(Organizm* o) { if (o->getChar() == KROLIK_CHAR) { return true; } else return false; }

char Krolik::getChar() { return KROLIK_CHAR; }
string Krolik::getNazwa() { return KROLIK_NAZWA; }
