#pragma once
#include "Czlowiek.h"
using namespace std;

Czlowiek::Czlowiek(Swiat* swiat, int x, int y) : Zwierze(swiat, x, y, CZLOWIEK_SILA, CZLOWIEK_INIC, CZLOWIEK_PELNOLETNOSC) {}

void Czlowiek::Akcja() {
	char in;
	Wsp n_wsp = this->wsp;
	while (true) {
		in = _getch();
		if (in == KEY_UP) { n_wsp.y++; }
		else if (in == KEY_DOWN) { n_wsp.y--; }
		else if (in == KEY_LEFT) { n_wsp.x--; }
		else if (in == KEY_RIGHT) { n_wsp.x++; }
		else if (in == PRZYCISK_TARCZY) {
			if (this->czasTarczy == 0) {
				swiat->DodajLogWalki(new LogWalki(this->getX(), this->getY(), TARCZA_NAPIS, "AKTYWOWANA", "")); 
				this->czasTarczy = CZAS_DZIALANIA_TARCZY + COOLDOWN_TARCZY;
			}
			return;
		}
		else { continue; }

		if (n_wsp.x < 0 || n_wsp.y < 0 || n_wsp.x >= swiat->getSzerokosc() || n_wsp.y >= swiat->getWysokosc()) { fflush(stdin); n_wsp = this->wsp; continue; }
		fflush(stdin);
		break;
	}

	this->inicjujKolizje(n_wsp);
}
bool Czlowiek::Koliduj(Organizm* somsiad, bool czyAtakuje) {
	if (this->czasTarczy > COOLDOWN_TARCZY && somsiad->getTyp() == TYP_ZWIERZE) {
		Wsp n_wsp = this->wsp;
		Wsp nn_wsp = this->wsp;
		if (czyAtakuje == true) { n_wsp = somsiad->getWsp(); }	// n_wsp - miejsce walki //
		nn_wsp = swiat->losujSasiada(n_wsp);
		somsiad->inicjujKolizje(nn_wsp);
		swiat->usunZPlanszy(wsp);
		this->wsp = n_wsp;
		swiat->wstawDoPlanszy(this, this->wsp);
		return true;
	}
	return false;
}

void Czlowiek::dodajPolog() {}
Organizm* Czlowiek::dajPotomka(Wsp n_wsp) {
	Organizm* tmp = new Czlowiek(swiat, n_wsp.x, n_wsp.y);
	swiat->DodajOrganizm(tmp);
	return tmp;
}
bool Czlowiek::czyTenSamGatunek(Organizm* o) { return false; }
void Czlowiek::AktualizujBuffyDebuffy() {
	if (this->czasTarczy > 0) {
		czasTarczy--;
		if(this->czasTarczy == COOLDOWN_TARCZY) {
			swiat->DodajLogWalki(new LogWalki(this->getX(), this->getY(), TARCZA_NAPIS, "DEZAKTYWOWANA", ""));
		}
		if(this->czasTarczy == 0) {
			swiat->DodajLogWalki(new LogWalki(this->getX(), this->getY(), TARCZA_NAPIS, "ZREGENEROWANA", ""));
		}
	}
}

char Czlowiek::getChar() { return CZLOWIEK_CHAR; }
string Czlowiek::getNazwa() { return CZLOWIEK_NAZWA; }

