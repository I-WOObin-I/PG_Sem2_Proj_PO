#pragma once
#include "Zwierze.h"

#define KROLIK_SILA 2
#define KROLIK_INIC 7
#define KROLIK_CHAR 'K'
#define KROLIK_POLOG 2
#define KROLIK_PELNOLETNOSC 3
#define KROLIK_NAZWA "Krolik"

using namespace std;

class Krolik : public Zwierze {
public:
	Krolik(Swiat* swiat, int x, int y);

	bool Koliduj(Organizm* somsiad, bool czyAtakuje) override;

	void dodajPolog() override;
	Organizm* dajPotomka(Wsp wsp) override;
	bool czyTenSamGatunek(Organizm* o);

	char getChar();
	string getNazwa() override;
};
