#pragma once
#include "Roslina.h"
#define TRAWA_SILA 0
#define TRAWA_CHAR '"'
#define TRAWA_NAZWA "Trawa"

using namespace std;

class Trawa : public Roslina {
private:
public:
	Trawa(Swiat* swiat, int x, int y);

	bool Koliduj(Organizm* somsiad, bool czyAtakuje) override;

	Organizm* dajPotomka(Wsp wsp) override;
	bool czyTenSamGatunek(Organizm* o);

	char getChar();
	string getNazwa();

};

