#pragma once
#include "Zwierze.h"
#define WILK_SILA 9
#define WILK_INIC 5
#define WILK_CHAR 'W'
#define WILK_POLOG 5
#define WILK_PELNOLETNOSC 10
#define WILK_NAZWA "Wilk"

using namespace std;

class Wilk : public Zwierze {
public:
	Wilk(Swiat* swiat, int x, int y);

	bool Koliduj(Organizm* somsiad, bool czyAtakuje) override;

	void dodajPolog() override;
	Organizm* dajPotomka(Wsp wsp) override;
	bool czyTenSamGatunek(Organizm* o);

	char getChar();
	string getNazwa() override;

};