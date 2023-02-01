#pragma once
#include "WilczaJagoda.h"
using namespace std;

WilczaJagoda::WilczaJagoda(Swiat* swiat, int x, int y) : Roslina(swiat, x, y, WJAG_SILA) {}

bool WilczaJagoda::Koliduj(Organizm* somsiad, bool czyAtakuje) {
	if (somsiad->getTyp() == TYP_ZWIERZE) {
		if (czyAtakuje == true) {
			swiat->usunOrganizm(somsiad);
			Wsp n_wsp = somsiad->getWsp();
			this->dajPotomka(n_wsp);
			swiat->DodajLogWalki(new LogWalki(somsiad->getX(), somsiad->getY(), this->getNazwa(), somsiad->getNazwa(), "zabil"));
		}
		else {
			swiat->usunOrganizm(somsiad);
			swiat->DodajLogWalki(new LogWalki(somsiad->getX(), somsiad->getY(), this->getNazwa(), somsiad->getNazwa(), "zabil"));
		}
		return true;
	}
	return false;
}

Organizm* WilczaJagoda::dajPotomka(Wsp n_wsp) {
	Organizm* tmp = new WilczaJagoda(swiat, n_wsp.x, n_wsp.y);
	swiat->DodajOrganizm(tmp);
	return tmp;
}
bool WilczaJagoda::czyTenSamGatunek(Organizm* o) { if (o->getChar() == WJAG_CHAR) { return true; } else return false; }

char WilczaJagoda::getChar() { return WJAG_CHAR; }
string WilczaJagoda::getNazwa() { return WJAG_NAZWA; }
