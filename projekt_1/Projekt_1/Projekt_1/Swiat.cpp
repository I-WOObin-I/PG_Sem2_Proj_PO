#pragma once
#include "Swiat.h"

using namespace std;

Swiat::Swiat(int szerokosc, int wysokosc) {
	plansza = new Plansza(szerokosc, wysokosc);
	srand(time(NULL));
}

void Swiat::przejdzTure() {
	AktualizujOrganizmy();
	usunMartwe();
	UrodzNoworodki();
	RysujSwiat();
	RysujLogi();
}
void Swiat::AktualizujOrganizmy() {
	list<Organizm*>::iterator it;
	for (it = organizmy.begin(); it != organizmy.end(); ++it) {
		Organizm* tmp = *it;
		if (tmp->getZ() == false) { continue; }
		tmp->AktualizujBuffyDebuffy();
		tmp->Akcja();
	}
}

void Swiat::DodajOrganizm(Organizm* o) {
	organizmyNoworodki.push(o);
}
void Swiat::UrodzNoworodki() {
	while (true) {
		if (!organizmyNoworodki.empty()) {
			if (organizmy.empty() == true) { organizmy.push_front(organizmyNoworodki.top()); }
			else {
				list<Organizm*>::iterator it;
				for (it = organizmy.begin(); it != organizmy.end(); ++it) {
					Organizm* tmp = *it;
					if (tmp->getI() < organizmyNoworodki.top()->getI()) { organizmy.insert(it, organizmyNoworodki.top()); break; }
				}
				if (it == organizmy.end()) { organizmy.push_back(organizmyNoworodki.top()); }
			}
			plansza->WstawOrganizm(organizmyNoworodki.top(), organizmyNoworodki.top()->getWsp());
			organizmyNoworodki.pop();
		}
		else { break; }
	}
}
void Swiat::usunOrganizm(Organizm* o) {
	plansza->UsunOrganizm(o->getWsp());
	o->Zabij();
	organizmyMartwe.push(o);
}
void Swiat::usunMartwe() {
	while (true) {
		if (!organizmyMartwe.empty()) {
			organizmy.remove(organizmyMartwe.top());
			Organizm* tmp =  organizmyMartwe.top();
			organizmyMartwe.pop();
			delete tmp;
		}
		else { break; }
	}
}
void Swiat::wstawDoPlanszy(Organizm* o, Wsp wsp) {
	plansza->WstawOrganizm(o, wsp);
}
void Swiat::usunZPlanszy(Wsp wsp) {
	plansza->UsunOrganizm(wsp);
}
void Swiat::Zeznik() {
	UrodzNoworodki();
	list<Organizm*>::iterator it;
	for (it = organizmy.begin(); it != organizmy.end(); ++it) {
		Organizm* tmp = *it;
		usunOrganizm(tmp);
	}
	usunMartwe();
}

void Swiat::RysujSwiat() {
	system("CLS");
	cout << endl << "Michal Lubinski, 184603" << endl;
	plansza->RysujPlansze();
}
void Swiat::RysujLogi() {
	LogWalki* log;
	int i = 0;
	while (logiWalki.empty() != true) {
		log = logiWalki.top();
		if (i < LICZBA_LOGOW) {
			cout << "na polu " << log->getX() << ", " << log->getY() << " " << log->getOrg1() << " " << log->getCoZrobil() << " " << log->getOrg2() << endl;
		}
		logiWalki.pop();
		i++;
	}
}
void Swiat::DodajLogWalki(LogWalki* log) {
	logiWalki.push(log);
}

bool Swiat::czyWPlanszy(Wsp wsp) {
	if (wsp.x >= 0 && wsp.x < plansza->getSzerokosc() && wsp.y >= 0 && wsp.y < plansza->getWysokosc()) { return true; }
	else { return false; }
}
Wsp Swiat::losujSasiada(Wsp wsp) { return plansza->losujSasiada(wsp); }
Wsp Swiat::znajdzWolnePole(Wsp wsp) { return plansza->znajdzWolnePole(wsp); }
Wsp Swiat::rotacjaSasiadow(Wsp wsp, Wsp n_wsp) { return plansza->rotacjaSasiadow(wsp, n_wsp); }

int Swiat::getSzerokosc() { return plansza->getSzerokosc(); }
int Swiat::getWysokosc()  { return plansza->getWysokosc();  }
Organizm* Swiat::getOrg(Wsp wsp) { return plansza->getOrg(wsp); }
int Swiat::getLiczbeSasiadow() { return plansza->getLiczbeSasiadow(); }

void Swiat::Zapisz() {
	fstream plik;
	plik.open("zapis_sym.txt", fstream::out);
	if (plik.is_open() == false) { cout << "blad_otwarcia pliku" << endl; return; }

	list<Organizm*>::iterator it;
	for (it = organizmy.begin(); it != organizmy.end(); ++it) {
		Organizm* tmp = *it;
		if (tmp->getZ() == false) { continue; }
		plik << tmp->getChar() << endl << tmp->getX() << endl << tmp->getY() << endl << tmp->getBuff() << endl;
	}
	plik.close();
	cout << "ZAPISANO" << endl;
}

Swiat::~Swiat() {
	Zeznik();
	delete plansza;
	while (logiWalki.empty() != true) { logiWalki.pop(); }
}