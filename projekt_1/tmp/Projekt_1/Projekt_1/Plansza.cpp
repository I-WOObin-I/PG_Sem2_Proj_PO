#pragma once
#include <Windows.h>

#include "Plansza.h"

using namespace std;

Plansza::Plansza(int szerokosc, int wysokosc) : szerokosc(szerokosc), wysokosc(wysokosc) {
	this->koord = new Organizm** [wysokosc];
	for (int i = 0; i < wysokosc; i++) {
		koord[i] = new Organizm* [szerokosc];
		for (int j = 0; j < szerokosc; j++) {
			koord[i][j] = NULL;
		}
	}
}

void Plansza::WstawOrganizm(Organizm* o, Wsp wsp) {
	if (wsp.x < 0 || wsp.x >= this->szerokosc || wsp.y < 0 || wsp.y >= this->wysokosc) { cout << endl << "koordy x/y wyszly poza plansze: " << wsp.x << ", " << wsp.y << endl; return; }
	else {
		this->koord[wsp.x][wsp.y] = o;
	}
}
void Plansza::UsunOrganizm(Wsp wsp) {
	if (wsp.x < 0 || wsp.x >= this->szerokosc || wsp.y < 0 || wsp.y >= this->wysokosc) { cout << endl << "koordy x/y wyszly poza plansze: " << wsp.x << ", " << wsp.y << endl; return; }
	else {
		this->koord[wsp.x][wsp.y] = NULL;
	}
}

void Plansza::RysujPlansze() {
	cout << " O=";
	for (int j = 0; j < this->szerokosc; j++) {
		cout << "==";
	}
	cout << "O" << endl;
	for (int i = this->wysokosc - 1; i >= 0; i--) {
		//if (i >= 10) { cout << i << " "; }
		//else { cout << " " << i << " "; }
		cout << " | ";
		for (int j = 0; j < this->szerokosc; j++) {
			if (koord[j][i] == NULL) { cout << PUSTE_POLE << " "; }
			else { cout << this->koord[j][i]->getChar() << " "; }
		}
		cout << "| ";
		cout << endl;
	}
	//cout << "   ";
	//for (int j = 0; j < this->szerokosc; j++) {
	//	if (j >= 10) { cout << j; }
	//	else { cout << j << " "; }
	//}
	cout << " O=";
	for (int j = 0; j < this->szerokosc; j++) {
		cout << "==";
	}
	cout << "O";
	cout << "\n\n";
	//cout << "  ";
	//for (int j = 0; j < this->width; j++) { cout << j << " "; }
	//cout << endl;
}
void Plansza::WyczyscPlansze() {
	for (int i = 0; i < szerokosc; i++) {
		for (int j = 0; j < wysokosc; j++) {
			koord[i][j] = NULL;
		}
	}
}

bool Plansza::czyWPlanszy(Wsp wsp) {
	if (wsp.x >= 0 && wsp.x < this->szerokosc && wsp.y >= 0 && wsp.y < this->wysokosc) { return true; }
	else { return false; }
}
Wsp Plansza::losujSasiada(Wsp wsp) {
	int tmp = rand() % LICZBA_SASIADOW;
	Wsp n_wsp = wsp;
	n_wsp = rotacjaSasiadow(wsp, n_wsp);

	for (int i = 0; i < tmp; i++) {
		n_wsp = rotacjaSasiadow(wsp, n_wsp);
	}
	return n_wsp;
}
Wsp Plansza::znajdzWolnePole(Wsp wsp) {
	Wsp tmp = losujSasiada(wsp);
	bool czyZnalazl = false;
	for (int i = 0; i < LICZBA_SASIADOW; i++) {
		if (getOrg(tmp) == NULL) { czyZnalazl = true; break; }
		tmp = rotacjaSasiadow(wsp, tmp);
	}
	if (czyZnalazl == true) { return tmp; }
	return wsp;
}

int Plansza::getSzerokosc() { return szerokosc; }
int Plansza::getWysokosc()  { return wysokosc;  }
Organizm* Plansza::getOrg(Wsp wsp) { return this->koord[wsp.x][wsp.y]; }
int Plansza::getLiczbeSasiadow() { return LICZBA_SASIADOW; }

Wsp Plansza::rotacjaSasiadow(Wsp wsp, Wsp n_wsp) {
	if (n_wsp.x == wsp.x && n_wsp.y == wsp.y) { n_wsp.y++; }				// 5 //
	else if (n_wsp.x == wsp.x && n_wsp.y == wsp.y + 1) { n_wsp.x++; }		// 8 //
	else if (n_wsp.x == wsp.x + 1 && n_wsp.y == wsp.y + 1) { n_wsp.y--; }	// 9 //
	else if (n_wsp.x == wsp.x + 1 && n_wsp.y == wsp.y) { n_wsp.y--; }		// 6 //
	else if (n_wsp.x == wsp.x + 1 && n_wsp.y == wsp.y - 1) { n_wsp.x--; }	// 3 //
	else if (n_wsp.x == wsp.x && n_wsp.y == wsp.y - 1) { n_wsp.x--; }		// 2 //
	else if (n_wsp.x == wsp.x - 1 && n_wsp.y == wsp.y - 1) { n_wsp.y++; }	// 1 //
	else if (n_wsp.x == wsp.x - 1 && n_wsp.y == wsp.y) { n_wsp.y++; }		// 4 //
	else if (n_wsp.x == wsp.x - 1 && n_wsp.y == wsp.y + 1) { n_wsp.x++; }	// 7 //

	if (czyWPlanszy(n_wsp) == false) { n_wsp = rotacjaSasiadow(wsp, n_wsp); }
	return n_wsp;
}

Plansza::~Plansza() {
	for (int i = 0; i < wysokosc; i++) {
		delete[] koord[i];
	}
	delete[] koord;
}
