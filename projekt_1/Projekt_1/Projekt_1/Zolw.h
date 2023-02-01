#pragma once
#include <time.h>
#include "Zwierze.h"

#define ZOLW_SILA 2
#define ZOLW_INIC 1
#define ZOLW_CHAR 'Z'
#define ZOLW_POLOG 3
#define ZOLW_PELNOLETNOSC 3
#define ZOLW_NAZWA "Zolw"
#define SZANSA_NA_RUCH 25
#define SILA_ODBICIA 5

using namespace std;

class Zolw : public Zwierze {
public:
	Zolw(Swiat* swiat, int x, int y);

	void Akcja() override;
	bool Koliduj(Organizm* somsiad, bool czyAtakuje) override;

	void dodajPolog() override;
	Organizm* dajPotomka(Wsp wsp) override;
	bool czyTenSamGatunek(Organizm* o);

	char getChar();
	string getNazwa() override;
};