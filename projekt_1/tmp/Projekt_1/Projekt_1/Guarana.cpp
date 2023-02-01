#pragma once
#include "Guarana.h"
using namespace std;

Guarana::Guarana(Swiat* swiat, int x, int y) : Roslina(swiat, x, y, GUARANA_SILA) {}

bool Guarana::Koliduj(Organizm* somsiad, bool czyAtakuje) {
	if (somsiad->getTyp() == TYP_ZWIERZE) {
		somsiad->dodajBuff(BUFF);
		if (czyAtakuje == false) {
			swiat->usunOrganizm(this);
			swiat->usunZPlanszy(somsiad->getWsp());
			somsiad->Przesun(this->wsp);
			swiat->wstawDoPlanszy(somsiad, somsiad->getWsp());
		}
		swiat->DodajLogWalki(new LogWalki(somsiad->getX(), somsiad->getY(), somsiad->getNazwa(), this->getNazwa(), "zjadl"));
		return true;
	}
	return false;
}

Organizm* Guarana::dajPotomka(Wsp n_wsp) {
	Organizm* tmp = new Guarana(swiat, n_wsp.x, n_wsp.y);
	swiat->DodajOrganizm(tmp);
	return tmp;
}
bool Guarana::czyTenSamGatunek(Organizm* o) { if (o->getChar() == GUARANA_CHAR) { return true; } else return false; }

char Guarana::getChar() { return GUARANA_CHAR; }
string Guarana::getNazwa() { return GUARANA_NAZWA; }
