#pragma once

#include "Zwierze.h"

#define LIS_SILA 3
#define LIS_INIC 7
#define LIS_CHAR 'L'
#define LIS_POLOG 5
#define LIS_PELNOLETNOSC 10
#define LIS_NAZWA "Lis"

using namespace std;

class Lis : public Zwierze {
public:
	Lis(Swiat* swiat, int x, int y);

	void Akcja() override;
	bool Koliduj(Organizm* somsiad, bool czyAtakuje) override;

	void dodajPolog() override;
	Organizm* dajPotomka(Wsp wsp) override;
	bool czyTenSamGatunek(Organizm* o);

	char getChar();
	string getNazwa() override;

};
