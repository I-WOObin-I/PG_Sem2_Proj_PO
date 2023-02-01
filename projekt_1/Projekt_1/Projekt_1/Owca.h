#pragma once
#include "Zwierze.h"

#define OWCA_SILA 4
#define OWCA_INIC 4
#define OWCA_CHAR 'O'
#define OWCA_POLOG 3
#define OWCA_PELNOLETNOSC 3
#define OWCA_NAZWA "Owca"

using namespace std;

class Owca : public Zwierze {
public:
	Owca(Swiat* swiat, int x, int y);

	bool Koliduj(Organizm* somsiad, bool czyAtakuje) override;

	void dodajPolog() override;
	Organizm* dajPotomka(Wsp wsp) override;
	bool czyTenSamGatunek(Organizm* o);

	char getChar();
	string getNazwa() override;
};