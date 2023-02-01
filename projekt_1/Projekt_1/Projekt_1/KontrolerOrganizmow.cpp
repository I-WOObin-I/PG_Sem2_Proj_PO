#include "KontrolerOrganizmow.h"

using namespace std;

KontrolerOrganizmow::KontrolerOrganizmow(Swiat* swiat) : swiat(swiat) {
	gatunki.push_back(new Czlowiek(swiat, 0, 0));
	gatunki.push_back(new Wilk(swiat, 0, 0));
	gatunki.push_back(new Owca(swiat, 0, 0));
	gatunki.push_back(new Lis(swiat, 0, 0));
	gatunki.push_back(new Zolw(swiat, 0, 0));
	gatunki.push_back(new Antylopa(swiat, 0, 0));
	gatunki.push_back(new Trawa(swiat, 0, 0));
	gatunki.push_back(new Mlecz(swiat, 0, 0));
	gatunki.push_back(new Guarana(swiat, 0, 0));
	gatunki.push_back(new WilczaJagoda(swiat, 0, 0));
	gatunki.push_back(new BarszczSosnowskiego(swiat, 0, 0));
}

void KontrolerOrganizmow::Zaladuj() {
	swiat->Zeznik();
	fstream plik;
	plik.open("zapis_sym.txt", fstream::in);
	if (plik.is_open() == false) { cout << "blad_otwarcia pliku" << endl; return; }

	char c;
	Wsp wsp = { 0,0 };
	int b;
	while (plik.peek() != EOF) {
		plik >> c;
		cout << c << " ";
		list<Organizm*>::iterator it;
		for (it = gatunki.begin(); it != gatunki.end(); ++it) {
			Organizm* tmp = *it;
			if (tmp->getChar() == c) {
				plik >> wsp.x;
				plik >> wsp.y;
				plik >> b;
				cout << wsp.x << " " << wsp.y << " ";
				Organizm* tmp2;
				tmp2 = tmp->dajPotomka(wsp);
				tmp2->dodajBuff(b);
				cout << "dodano: " << tmp2->getNazwa() << endl;
			}
		}
	}
	plik.close();
	swiat->DodajLogWalki(new LogWalki(0, 0, "ZALADOWANO", "", ""));
}

KontrolerOrganizmow::~KontrolerOrganizmow() {
	list<Organizm*>::iterator it;
	for (it = gatunki.begin(); it != gatunki.end(); ++it) {
		Organizm* tmp = *it;
		gatunki.remove(tmp);
		delete tmp;
	}
}