#pragma once
#include "Roslina.h"

using namespace std;

Roslina::Roslina(Swiat* swiat, int x, int y, int sila) : Organizm(swiat, x, y, sila, 0, TYP_ROSLINA, 0) {}

void Roslina::Akcja() {
	int tmp2 = rand() % 100;
	if (tmp2 <= SZANSA_ROZMN) {
		Wsp n_wsp = swiat->losujSasiada(this->wsp);
		this->inicjujKolizje(n_wsp);
	}
}
void Roslina::inicjujKolizje(Wsp n_wsp) { // nie zachodzi zadna kolizja miedzy roslinami tego samego gatunku //
	if (swiat->getOrg(n_wsp) != NULL) {
		Organizm* somsiad = swiat->getOrg(n_wsp);
		if (this->Koliduj(somsiad, true) == false && somsiad->Koliduj(this, false) == false && this->czyTenSamGatunek(somsiad) == false) {
			this->kolidujDomyslnie(somsiad);
		}
	}
	else { this->dajPotomka(n_wsp); }
}
void Roslina::kolidujDomyslnie(Organizm* somsiad) { // domsylna kolizja jest wywolywana tylko dla atakujacego //
	if (this->getS() >= somsiad->getS()) {
		swiat->usunOrganizm(somsiad);
		Wsp n_wsp = somsiad->getWsp();
		this->dajPotomka(n_wsp);
		swiat->DodajLogWalki(new LogWalki(somsiad->getX(), somsiad->getY(), this->getNazwa(), somsiad->getNazwa(), "zabil"));
	}
	else {
		string s;
		if (somsiad->getTyp() == TYP_ZWIERZE) { s = "zjadl"; }
		else { s = "zabil"; }
		swiat->DodajLogWalki(new LogWalki(somsiad->getX(), somsiad->getY(), somsiad->getNazwa(), this->getNazwa(), s));
	}
}
void Roslina::AktualizujBuffyDebuffy() {}
