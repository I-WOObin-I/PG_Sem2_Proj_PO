#pragma once
#include "Mlecz.h"
using namespace std;

Mlecz::Mlecz(Swiat* swiat, int x, int y) : Roslina(swiat, x, y, MLECZ_SILA) {}

void Mlecz::Akcja() {
	Wsp n1_wsp = this->wsp;
	Wsp n2_wsp = this->wsp;
	Wsp n3_wsp = this->wsp;

	int tmp2 = rand() % 100;
	if (tmp2 <= SZANSA_ROZMN) {
		n1_wsp = swiat->losujSasiada(this->wsp);
	}
	tmp2 = rand() % 100;
	if (tmp2 <= SZANSA_ROZMN) {
		n2_wsp = swiat->rotacjaSasiadow(this->wsp, n1_wsp);
		n2_wsp = swiat->rotacjaSasiadow(this->wsp, n2_wsp);
		n2_wsp = swiat->rotacjaSasiadow(this->wsp, n2_wsp);
	}
	tmp2 = rand() % 100;
	if (tmp2 <= SZANSA_ROZMN) {
		n3_wsp = swiat->rotacjaSasiadow(this->wsp, n2_wsp);
		n3_wsp = swiat->rotacjaSasiadow(this->wsp, n3_wsp);
		n3_wsp = swiat->rotacjaSasiadow(this->wsp, n3_wsp);
	}
	this->inicjujKolizje(n1_wsp);
	this->inicjujKolizje(n2_wsp);
	this->inicjujKolizje(n3_wsp);
}
bool Mlecz::Koliduj(Organizm* somsiad, bool czyAtakuje) {
	return false;
}

Organizm* Mlecz::dajPotomka(Wsp n_wsp) {
	Organizm* tmp = new Mlecz(swiat, n_wsp.x, n_wsp.y);
	swiat->DodajOrganizm(tmp);
	return tmp;
}
bool Mlecz::czyTenSamGatunek(Organizm* o) { if (o->getChar() == MLECZ_CHAR) { return true; } else return false; }

char Mlecz::getChar() { return MLECZ_CHAR; }
string Mlecz::getNazwa() { return MLECZ_NAZWA; }
