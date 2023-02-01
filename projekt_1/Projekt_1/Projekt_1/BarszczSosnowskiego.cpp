#pragma once
#include "BarszczSosnowskiego.h"
using namespace std;

BarszczSosnowskiego::BarszczSosnowskiego(Swiat* swiat, int x, int y) : Roslina(swiat, x, y, BARSZCZ_SILA) {}

void BarszczSosnowskiego::Akcja() {
	Wsp tmp = this->wsp;		// zabicie wszystkich sasiadujacych zwierzat //
	for (int i = 0; i < swiat->getLiczbeSasiadow() + 1; i++) {
		tmp = swiat->rotacjaSasiadow(this->wsp, tmp);
		if (swiat->getOrg(tmp) != NULL && swiat->getOrg(tmp)->getTyp() == TYP_ZWIERZE && swiat->getOrg(tmp)->getChar() != 'C') { swiat->usunOrganizm(swiat->getOrg(tmp)); }
	}
	
	int tmp2 = rand() % 100;
	if (tmp2 <= SZANSA_ROZMN) {
		Wsp n_wsp = swiat->losujSasiada(this->wsp);
		this->inicjujKolizje(n_wsp);
	}
}
bool BarszczSosnowskiego::Koliduj(Organizm* somsiad, bool czyAtakuje) {
	if (somsiad->getTyp() == TYP_ZWIERZE && somsiad->getChar() != 'C') {
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

Organizm* BarszczSosnowskiego::dajPotomka(Wsp n_wsp) {
	Organizm* tmp = new BarszczSosnowskiego(swiat, n_wsp.x, n_wsp.y);
	swiat->DodajOrganizm(tmp);
	return tmp;
}
bool BarszczSosnowskiego::czyTenSamGatunek(Organizm* o) { if (o->getChar() == BARSZCZ_CHAR) { return true; } else return false; }

char BarszczSosnowskiego::getChar() { return BARSZCZ_CHAR; }
string BarszczSosnowskiego::getNazwa() { return BARSZCZ_NAZWA; }
