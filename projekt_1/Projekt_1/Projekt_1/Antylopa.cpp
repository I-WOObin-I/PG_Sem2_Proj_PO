#pragma once
#include "Antylopa.h"
using namespace std;

Antylopa::Antylopa(Swiat* swiat, int x, int y) : Zwierze(swiat, x, y, ANTYLOPA_SILA, ANTYLOPA_INIC, ANTYLOPA_PELNOLETNOSC) {}

void Antylopa::Akcja() {
	Wsp n_wsp = swiat->losujSasiada(this->wsp);
	n_wsp = swiat->losujSasiada(n_wsp);
	if(n_wsp.x == this->wsp.x && n_wsp.y == this->wsp.y) { n_wsp = swiat->losujSasiada(this->wsp); }

	this->inicjujKolizje(n_wsp);
}
bool Antylopa::Koliduj(Organizm* somsiad, bool czyAtakuje) {
	if (somsiad->getTyp() == TYP_ZWIERZE) {
		Wsp n_wsp = this->wsp;									// okreslenie		//
		if (czyAtakuje == true) { n_wsp = somsiad->getWsp(); }	// miejsca walki	//
		int tmp = rand() % 100;
		if (tmp < SZANSA_NA_UCIECZKE) {
			Wsp nn_wsp = swiat->znajdzWolnePole(n_wsp);
			if (nn_wsp.x != n_wsp.x || nn_wsp.y != n_wsp.y) {
				swiat->usunZPlanszy(this->wsp);
				this->wsp = nn_wsp;
				swiat->wstawDoPlanszy(this, this->wsp);
				swiat->usunZPlanszy(somsiad->getWsp());
				somsiad->Przesun(n_wsp);
				swiat->wstawDoPlanszy(somsiad, somsiad->getWsp());
				return true;
			}
		}
	}
	return false;
}

void Antylopa::dodajPolog() { this->polog = ANTYLOPA_POLOG; }
Organizm* Antylopa::dajPotomka(Wsp n_wsp) {
	Organizm* tmp = new Antylopa(swiat, n_wsp.x, n_wsp.y);
	swiat->DodajOrganizm(tmp);
	return tmp;
}
bool Antylopa::czyTenSamGatunek(Organizm* o) { if (o->getChar() == ANTYLOPA_CHAR) { return true; } else return false; }

char Antylopa::getChar() { return ANTYLOPA_CHAR; }
string Antylopa::getNazwa() { return ANTYLOPA_NAZWA; }
