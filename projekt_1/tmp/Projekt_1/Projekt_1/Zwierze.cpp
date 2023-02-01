#pragma once
#include "Zwierze.h"

using namespace std;

Zwierze::Zwierze(Swiat* swiat, int x, int y, int sila, int inicjatywa, int pelnoletnsoc) :
	Organizm(swiat, x, y, sila, inicjatywa, TYP_ZWIERZE, pelnoletnsoc)
{}

void Zwierze::Akcja() {
	Wsp n_wsp = swiat->losujSasiada(this->wsp);
	this->inicjujKolizje(n_wsp);
}
void Zwierze::inicjujKolizje(Wsp n_wsp) {
	if (swiat->getOrg(n_wsp) != NULL) {
		Organizm* somsiad = swiat->getOrg(n_wsp);
		if (this->czyTenSamGatunek(somsiad) == true) {
			this->Kopulacja(somsiad);
			n_wsp = this->wsp;
		}
		else {
			if (this->Koliduj(somsiad, true) == false && somsiad->Koliduj(this, false) == false) {
				this->kolidujDomyslnie(somsiad);
			}
		}
	}
	else {
		swiat->usunZPlanszy(this->wsp);
		this->wsp = n_wsp;
		swiat->wstawDoPlanszy(this, this->wsp);
	}
}
void Zwierze::kolidujDomyslnie(Organizm* somsiad) { // domsylna kolizja jest wywolywana tylko dla atakujacego //
	if (this->getS() >= somsiad->getS()) {
		string s;
		if (somsiad->getTyp() == TYP_ROSLINA) { s = "zjadl"; }
		else { s = "zabil"; }

		swiat->usunOrganizm(somsiad);
		swiat->usunZPlanszy(this->wsp);
		this->wsp = somsiad->getWsp();
		swiat->wstawDoPlanszy(this, this->wsp);
		swiat->DodajLogWalki(new LogWalki(somsiad->getX(), somsiad->getY(), this->getNazwa(), somsiad->getNazwa(), s));
	}
	else {
		swiat->usunOrganizm(this);
		swiat->DodajLogWalki(new LogWalki(somsiad->getX(), somsiad->getY(), somsiad->getNazwa(), this->getNazwa(), "zabil"));
	}
}
void Zwierze::AktualizujBuffyDebuffy() {
	if (this->polog > 0) { this->polog--; }
}
void Zwierze::Kopulacja(Organizm* somsiad) {		// nowy organizm nie rodzi sie jesli zaden z rodzicow nie ma wolnego miejsca obok siebie //
	if (this->czyGotowyDoRozmnazania() && somsiad->czyGotowyDoRozmnazania()) {
		Wsp n_wsp = somsiad->getWsp();
		Wsp nn_wsp = swiat->znajdzWolnePole(this->wsp);
		if (nn_wsp.x == this->wsp.x && nn_wsp.y == this->wsp.y) {
			nn_wsp = swiat->znajdzWolnePole(n_wsp);
			if (nn_wsp.x != n_wsp.x || nn_wsp.y != n_wsp.y) {
				this->dajPotomka(nn_wsp);
				this->dodajPolog();
				somsiad->dodajPolog();
			}
		}
		else {
			this->dajPotomka(nn_wsp);
			this->dodajPolog();
			somsiad->dodajPolog();
		}
	}
}

bool Zwierze::czyGotowyDoRozmnazania() { if (polog == 0) { return true; } else return false; }


