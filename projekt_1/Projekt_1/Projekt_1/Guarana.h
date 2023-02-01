#pragma once
#include "Roslina.h"
#define GUARANA_SILA 0
#define GUARANA_CHAR '@'
#define GUARANA_NAZWA "Guarana"
#define BUFF 3

using namespace std;

class Guarana : public Roslina {
public:
	Guarana(Swiat* swiat, int x, int y);

	bool Koliduj(Organizm* somsiad, bool czyAtakuje) override;

	Organizm* dajPotomka(Wsp wsp) override;
	bool czyTenSamGatunek(Organizm* o);

	char getChar();
	string getNazwa();

};

