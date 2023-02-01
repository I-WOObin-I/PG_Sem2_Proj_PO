#pragma once
#include "Zwierze.h"
#define ANTYLOPA_SILA 4
#define ANTYLOPA_INIC 4
#define ANTYLOPA_CHAR 'A'
#define ANTYLOPA_POLOG 5
#define ANTYLOPA_PELNOLETNOSC 10
#define ANTYLOPA_NAZWA "Antylopa"
#define SZANSA_NA_UCIECZKE 50

using namespace std;

class Antylopa : public Zwierze {
public:
	Antylopa(Swiat* swiat, int x, int y);

	void Akcja() override;
	bool Koliduj(Organizm* somsiad, bool czyAtakuje) override;

	void dodajPolog() override;
	Organizm* dajPotomka(Wsp wsp) override;
	bool czyTenSamGatunek(Organizm* o);

	char getChar();
	string getNazwa() override;

};
